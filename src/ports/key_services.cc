#include "carrotdb/ports/key_services.h"

namespace ports
{
    namespace impl
    {
        key_create_service::key_create_service(std::shared_ptr<ports::key_repository> key_repository) : key_repository(key_repository){};

        void key_create_service::key_create_service::create(const model::key &key)
        {
            key_repository->set(key);
        }

        key_get_service::key_get_service(std::shared_ptr<ports::key_repository> key_repository) : key_repository(key_repository){};

        model::key key_get_service::get(const std::string &id)
        {
            return key_repository->get(id);
        }

    } // namespace impl
} // namespace ports