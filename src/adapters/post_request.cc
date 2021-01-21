#include "carrotdb/adapters/post_request.h"

namespace adapters
{
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
        model::value value(std::move(content));

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