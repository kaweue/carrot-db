#pragma once

#include "carrotdb/ports/key_value.h"
#include "carrotdb/adapters/api_service.h"
#include "cpprest/http_msg.h"

#include <string>
#include <memory>

namespace adapters
{
    class put_request
    {
    };

    class post_request
    {
    };

    class delete_request
    {
    };

    class get_request_handle : public request_handle
    {
    public:
        get_request_handle();
        explicit get_request_handle(std::shared_ptr<ports::key> key_port);
        void handle(web::http::http_request request) override;

    private:
        std::shared_ptr<ports::key> key_port;
    };
} // namespace adapters