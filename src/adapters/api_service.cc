#include <memory>

#include "carrotdb/adapters/api_service.h"

namespace adapters
{

    api::api() {}

    api::api(std::shared_ptr<service> next_service) : service(next_service)
    {
    }

    api::~api()
    {
    }

    void api::rest_get(web::http::http_request http_request)
    {
        auto request = get_request(http_request);
        proces_next(std::move(request));
    }

    void api::rest_put(web::http::http_request http_request)
    {
        auto request = put_request();
        proces_next(std::move(request));
        http_request.reply(web::http::status_codes::OK);
    }

    void api::rest_post(web::http::http_request http_request)
    {
        auto request = post_request();
        proces_next(std::move(request));
        http_request.reply(web::http::status_codes::OK);
    }

    void api::rest_delete(web::http::http_request http_request)
    {
        auto request = delete_request();
        proces_next(std::move(request));
        http_request.reply(web::http::status_codes::OK);
    }
} // namespace adapters