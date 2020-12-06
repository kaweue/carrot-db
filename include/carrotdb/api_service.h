#pragma once

#include <memory>

#include "cpprest/http_msg.h"
#include "carrotdb/service.h"

namespace service
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

} // namespace service