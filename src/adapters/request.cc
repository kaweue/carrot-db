#include "carrotdb/adapters/request.h"

namespace adapters
{
    get_request_handle::get_request_handle()
    {
    }

    get_request_handle::get_request_handle(std::shared_ptr<ports::key> key_port) : key_port(key_port)
    {
    }

    void get_request_handle::handle(web::http::http_request request)
    {
        request.reply(web::http::status_codes::OK);
    }

    web::http::method get_request_handle::method()
    {
        return web::http::methods::GET;
    }

    post_request_handle::post_request_handle()
    {
    }

    post_request_handle::post_request_handle(std::shared_ptr<ports::key> key_port)
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
        request.reply(web::http::status_codes::Created);
    }

    web::http::method post_request_handle::method()
    {
        return web::http::methods::POST;
    }

} // namespace adapters