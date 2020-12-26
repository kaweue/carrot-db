#include "carrotdb/carrot_db.h"
#include "carrotdb/adapters/kv_service.h"
namespace app
{
    using namespace web;
    carrot_db::carrot_db(std::string uri) : m_listner(web::http::uri(uri))
    {
        auto kv = std::make_shared<adapters::key_value>();
        m_api = adapters::api(kv);
    }

    int carrot_db::start()
    {
        m_listner.support(http::methods::POST, std::bind(&adapters::api::rest_post, m_api, std::placeholders::_1));
        m_listner.support(http::methods::PUT, std::bind(&adapters::api::rest_put, m_api, std::placeholders::_1));
        m_listner.support(http::methods::GET, std::bind(&adapters::api::rest_get, m_api, std::placeholders::_1));
        m_listner.support(http::methods::DEL, std::bind(&adapters::api::rest_delete, m_api, std::placeholders::_1));
        m_listner.open().wait();
        return 0;
    }

    int carrot_db::stop()
    {
        m_listner.close().wait();
        return 0;
    }
} // namespace app