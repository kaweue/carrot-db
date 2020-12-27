#include "carrotdb/carrot_db.h"
#include "carrotdb/adapters/request.h"

namespace app
{
    using namespace web;
    carrot_db::carrot_db(std::string uri) : m_listner(web::http::uri(uri))
    {
        m_api = adapters::api({
            std::make_shared<adapters::get_request_handle>(),
            std::make_shared<adapters::post_request_handle>(),
        });
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