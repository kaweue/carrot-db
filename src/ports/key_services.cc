#include "carrotdb/ports/key_services.h"

namespace ports
{
    namespace impl
    {
        key_create_service::key_create_service(std::shared_ptr<ports::interfaces::repository<model::key>> key_repository,
                                               std::shared_ptr<ports::interfaces::repository<model::value>> value_repository)
            : key_repository(key_repository), value_repository(value_repository){};

        void key_create_service::key_create_service::create(const model::key &key)
        {
            store_key_and_value(key);
            notify_observer(key);
        }

        void key_create_service::store_key_and_value(const model::key &key)
        {
            key_repository->set(key);
            auto value = key.get_value();
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

        model::key key_get_service::get(const std::string &path)
        {
            auto id = path_to_key_id->get_key_id(path);
            auto key = key_repository->get(id);
            auto value = value_repository->get(key.get_value().id());
            return model::key(key.path(), key.get_value());
        }

    } // namespace impl
} // namespace ports