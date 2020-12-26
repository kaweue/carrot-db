#pragma once

#include <memory>

#include "cpprest/http_msg.h"
#include "carrotdb/adapters/service.h"

namespace adapters
{

    class api : public service
    {
    public:
        api();
        api(std::shared_ptr<service> next_service);
        ~api();

        void rest_get(web::http::http_request request);
        void rest_put(web::http::http_request request);
        void rest_post(web::http::http_request request);
        void rest_delete(web::http::http_request request);
    };

} // namespace adapters