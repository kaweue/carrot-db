#include <memory>

#include "carrotdb/adapters/api_service.h"

namespace adapters
{

    api::api() {}

    api::api(std::initializer_list<std::shared_ptr<adapters::request_handle>> handlers)
    {
        for (auto handler : handlers)
        {
            this->handlers[handler->method()] = handler;
        }
    }

    api::~api()
    {
    }

    void api::rest_handle(web::http::http_request http_request)
    {
        auto handler = handlers.find(http_request.method());
        if (handler == handlers.end())
        {
            http_request.reply(web::http::status_codes::NotImplemented);
            return;
        }
        handler->second->handle(http_request);
    }

} // namespace adapters