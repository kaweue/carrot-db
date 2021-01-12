#pragma once

#include "carrotdb/ports/repository.h"
#include "carrotdb/ports/key_services.h"
#include "carrotdb/adapters/api_service.h"
#include "cpprest/http_msg.h"

#include <string>
#include <memory>

namespace adapters
{

    class request_handle
    {
    public:
        virtual web::http::method method() = 0;
        virtual void handle(web::http::http_request request) = 0;
        virtual ~request_handle() = default;
    };

    class post_request_handle : public request_handle
    {
    public:
        explicit post_request_handle(std::shared_ptr<ports::interfaces::key_create_service> keys);
        void handle(web::http::http_request request) override;
        web::http::method method() override;

    private:
        bool valid(const web::http::http_request &request) const;
        std::shared_ptr<ports::interfaces::key_create_service> keys;
        std::string retrive_request_body(const web::http::http_request &request) const;
    };

    class get_request_handle : public request_handle
    {
    public:
        explicit get_request_handle(std::shared_ptr<ports::interfaces::key_get_service> keys);
        void handle(web::http::http_request request) override;
        web::http::method method() override;

    private:
        std::shared_ptr<ports::interfaces::key_get_service> keys;
        void reply_for_request(const web::http::http_request &request) const;
    };

    class delete_request
    {
    };

    class put_request
    {
    };

} // namespace adapters