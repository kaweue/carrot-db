#include "carrotdb/adapters/get_request.h"

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
}