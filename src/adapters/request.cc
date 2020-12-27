#include "carrotdb/adapters/request.h"

namespace adapters
{
    get_request::get_request(web::http::http_request request) : request(request)
    {
    }

    void get_request::process(ports::key *key_port)
    {
        request.reply(web::http::status_codes::OK);
    }

} // namespace adapters