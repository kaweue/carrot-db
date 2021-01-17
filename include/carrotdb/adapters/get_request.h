#pragma once

#include "carrotdb/adapters/request.h"

#include "carrotdb/ports/repository.h"
#include "carrotdb/ports/key_get_service.h"
#include "carrotdb/adapters/api_service.h"

#include <memory>
#include <string>

namespace adapters
{
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
} // namespace adapters