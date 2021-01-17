#pragma once

#include "carrotdb/adapters/request.h"
#include "carrotdb/ports/repository.h"
#include "carrotdb/ports/key_create_service.h"
#include "carrotdb/adapters/api_service.h"

#include <memory>
#include <string>

namespace adapters
{
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

} // namespace adapters