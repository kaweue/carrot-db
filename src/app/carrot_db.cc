#include "carrotdb/app/carrot_db.h"
#include "carrotdb/adapters/get_request.h"
#include "carrotdb/adapters/post_request.h"
#include "carrotdb/adapters/repository.h"
#include "carrotdb/adapters/path_to_key_id_service.h"

namespace app
{
    using namespace web;
    carrot_db::carrot_db(const std::string &uri) : m_listner(web::http::uri(uri))
    {
        auto value_db = std::make_shared<adapters::repository<model::value>>();
        auto keys_db = std::make_shared<adapters::repository<model::key>>();
        auto path_to_key_id_service = std::make_shared<adapters::path_to_key_id_service>();
        auto key_get = std::make_shared<ports::impl::key_get_service>(keys_db, value_db, path_to_key_id_service);
        auto key_create = std::make_shared<ports::impl::key_create_service>(keys_db, value_db);
        key_create->set_observer(path_to_key_id_service);
        m_api = adapters::api({
            std::make_shared<adapters::get_request_handle>(key_get),
            std::make_shared<adapters::post_request_handle>(key_create),
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