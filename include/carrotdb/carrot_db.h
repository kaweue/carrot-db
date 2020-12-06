#pragma once

#include "carrotdb/api_service.h"

#include "cpprest/http_listener.h"
#include "cpprest/http_client.h"

#include <memory>
#include <string>

namespace app
{
    class carrot_db
    {
    public:
        explicit carrot_db(std::string uri);
        int start();
        int stop();

    private:
        web::http::experimental::listener::http_listener m_listner;
        service::api m_api;
    };

} // namespace app