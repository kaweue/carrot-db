#include "carrotdb/adapters/request.h"

namespace adapters
{
    get_request_handle::get_request_handle()
    {
    }

    get_request_handle::get_request_handle(std::shared_ptr<ports::key> key_port) : key_port(key_port)
    {
    }

    void get_request_handle::handle(web::http::http_request request)
    {
        request.reply(web::http::status_codes::OK);
    }

} // namespace adapters