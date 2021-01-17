#pragma once

#include "cpprest/http_msg.h"

namespace adapters
{
    class request_handle
    {
    public:
        virtual web::http::method method() = 0;
        virtual void handle(web::http::http_request request) = 0;
        virtual ~request_handle() = default;
    };

} // namespace adapters