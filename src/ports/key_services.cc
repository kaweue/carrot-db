#include "carrotdb/ports/key_create_service.h"
#include "carrotdb/ports/key_get_service.h"

namespace ports
{
    namespace impl
    {
        key_create_service::key_create_service(std::shared_ptr<ports::interfaces::repository<model::key>> key_repository,
                                               std::shared_ptr<ports::interfaces::repository<model::value>> value_repository)
            : key_repository(key_repository), value_repository(value_repository){};

        void key_create_service::key_create_service::create(model::key &&key, model::value &&value)
        {
            store_key_and_value(key, value);
            notify_observer(key);
        }

        void key_create_service::store_key_and_value(const model::key &key, const model::value & value)
        {
            key_repository->set(key);
            value_repository->set(value);
        }

        void key_create_service::notify_observer(const model::key &key)
        {
            if (auto obs = observer.lock())
            {
                obs->created(key);
            }
        }

        void key_create_service::set_observer(std::weak_ptr<ports::impl::key_create_service::create_observer> observer)
        {
            this->observer = observer;
        }

        key_get_service::key_get_service(std::shared_ptr<ports::interfaces::repository<model::key>> key_repository,
                                         std::shared_ptr<ports::interfaces::repository<model::value>> value_repository,
                                         std::shared_ptr<ports::interfaces::path_to_key_id> path_to_key_id)
            : key_repository(key_repository), value_repository(value_repository), path_to_key_id(path_to_key_id){};

        std::pair<model::key, model::value> key_get_service::get(const std::string &path)
        {
            auto id = path_to_key_id->get_key_id(path);
            auto key = key_repository->get(id);
            auto value = value_repository->get(key.value_id());
            return std::pair(model::key(key.path(), std::move(value)), std::move(value));
        }

    } // namespace impl
} // namespace ports