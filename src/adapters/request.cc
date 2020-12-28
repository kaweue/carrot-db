#include "carrotdb/adapters/request.h"

namespace adapters
{
    get_request_handle::get_request_handle()
    {
    }

    get_request_handle::get_request_handle(std::shared_ptr<ports::keys> keys) : keys(keys)
    {
    }

    void get_request_handle::handle(web::http::http_request request)
    {
        auto path = request.request_uri().path();
        if (!keys)
        {
            request.reply(web::http::status_codes::OK);
            return;
        }
        try
        {
            keys->get(path);
        }
        catch (ports::keys::not_found_exception e)
        {
            request.reply(web::http::status_codes::NotFound);
            return;
        }
        request.reply(web::http::status_codes::OK);
    }

    web::http::method get_request_handle::method()
    {
        return web::http::methods::GET;
    }

    post_request_handle::post_request_handle()
    {
    }

    post_request_handle::post_request_handle(std::shared_ptr<ports::keys> keys) : keys(keys)
    {
    }

    bool post_request_handle::valid(const web::http::http_request &request) const
    {
        auto path = request.request_uri().path();
        if (path.compare("/") == 0)
        {
            return false;
        }
        if (!keys)
        {
            return true;
        }
        keys->set(model::key(path));

        return true;
    }

    void post_request_handle::handle(web::http::http_request request)
    {
        if (!valid(request))
        {
            request.reply(web::http::status_codes::BadRequest);
            return;
        }
        request.reply(web::http::status_codes::Created);
    }

    web::http::method post_request_handle::method()
    {
        return web::http::methods::POST;
    }

} // namespace adapters