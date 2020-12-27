#pragma once

#include <memory>

#include "cpprest/http_msg.h"

namespace adapters
{

    class request_handle
    {
    public:
        virtual web::http::method method() = 0;
        virtual void handle(web::http::http_request request) = 0;
    };

    class api
    {
    public:
        api();
        api(std::initializer_list<std::shared_ptr<adapters::request_handle>> handlers);
        ~api();

        void rest_handle(web::http::http_request http_request);

    private:
        std::map<web::http::method, std::shared_ptr<adapters::request_handle>> handlers;
    };

} // namespace adapters