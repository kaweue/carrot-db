#pragma once

#include "carrotdb/ports/key_value.h"
#include "cpprest/http_msg.h"

#include <string>

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

    class get_request
    {
    public:
        explicit get_request(web::http::http_request request);
        void process(ports::key *key_port);

    private:
        web::http::http_request request;
    };
} // namespace adapters