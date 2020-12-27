#include "carrotdb/carrot_db.h"
#include "carrotdb/adapters/request.h"

namespace app
{
    using namespace web;
    carrot_db::carrot_db(std::string uri) : m_listner(web::http::uri(uri))
    {
        auto get_handle = std::make_shared<adapters::get_request_handle>();
        auto handlers = std::map<web::http::method, std::shared_ptr<adapters::request_handle>>{
            {web::http::methods::GET, get_handle}};
        m_api = adapters::api(handlers);
    }

    int carrot_db::start()
    {
        m_listner.support(std::bind(&adapters::api::rest_handle, m_api, std::placeholders::_1));
        m_listner.open().wait();
        return 0;
    }

    int carrot_db::stop()
    {
        m_listner.close().wait();
        return 0;
    }
} // namespace app