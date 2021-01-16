#include "carrotdb/adapters/request.h"

namespace adapters
{
    get_request_handle::get_request_handle(std::shared_ptr<ports::interfaces::key_get_service> keys) : keys(keys)
    {
    }

    void get_request_handle::handle(web::http::http_request request)
    {
        try
        {
            reply_for_request(request);
        }
        catch (ports::interfaces::not_found e)
        {
            request.reply(web::http::status_codes::NotFound);
        }
    }

    void get_request_handle::reply_for_request(const web::http::http_request &request) const
    {
        auto path = request.request_uri().path();
        auto [key, value] = keys->get(path);
        request.reply(web::http::status_codes::OK, value.get_content());
    }

    web::http::method get_request_handle::method()
    {
        return web::http::methods::GET;
    }

    post_request_handle::post_request_handle(std::shared_ptr<ports::interfaces::key_create_service> keys) : keys(keys)
    {
    }

    bool post_request_handle::valid(const web::http::http_request &request) const
    {
        auto path = request.request_uri().path();
        if (path.compare("/") == 0)
        {
            return false;
        }

        return true;
    }

    void post_request_handle::handle(web::http::http_request request)
    {
        if (!valid(request))
        {
            request.reply(web::http::status_codes::BadRequest);
            return;
        }
        auto path = request.request_uri().path();
        auto content = retrive_request_body(request);
        model::value value(content);

        keys->create(model::key(path, value), std::move(value));
        request.reply(web::http::status_codes::Created);
    }

    std::string post_request_handle::retrive_request_body(const web::http::http_request &request) const
    {
        concurrency::streams::container_buffer<std::string> stream_buffer;
        if (!request.body().is_valid())
        {
            return std::string();
        }
        request.body().read_to_end(stream_buffer).wait();
        return stream_buffer.collection();
    }

    web::http::method post_request_handle::method()
    {
        return web::http::methods::POST;
    }

} // namespace adapters