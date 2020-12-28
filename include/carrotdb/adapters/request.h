#pragma once

#include "carrotdb/ports/key_value.h"
#include "carrotdb/adapters/api_service.h"
#include "cpprest/http_msg.h"

#include <string>
#include <memory>

namespace adapters
{
    class post_request_handle : public request_handle
    {
    public:
        post_request_handle();
        explicit post_request_handle(std::shared_ptr<ports::keys> keys);
        void handle(web::http::http_request request) override;
        web::http::method method() override;

    private:
        bool valid(const web::http::http_request &request) const;
        std::shared_ptr<ports::keys> keys;
    };

    class get_request_handle : public request_handle
    {
    public:
        get_request_handle();
        explicit get_request_handle(std::shared_ptr<ports::keys> keys);
        void handle(web::http::http_request request) override;
        web::http::method method() override;

    private:
        std::shared_ptr<ports::keys> keys;
    };

    class delete_request
    {
    };

    class put_request
    {
    };

} // namespace adapters