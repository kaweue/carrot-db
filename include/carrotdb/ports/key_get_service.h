#pragma once

#include "carrotdb/model/key.h"
#include "carrotdb/ports/repository.h"
#include "carrotdb/ports/path_to_key_id.h"

#include <string>
#include <memory>
#include <utility>

namespace ports
{

    namespace interfaces
    {
        class key_get_service
        {
        public:
            virtual std::pair<model::key, model::value> get(const std::string &id) = 0;
            virtual ~key_get_service() = default;
        };
    } // namespace interfaces

    namespace impl
    {
        class key_get_service : public interfaces::key_get_service
        {
        public:
            explicit key_get_service(std::shared_ptr<ports::interfaces::repository<model::key>> key_repository,
                                     std::shared_ptr<ports::interfaces::repository<model::value>> value_repository,
                                     std::shared_ptr<ports::interfaces::path_to_key_id> path_to_key_id);
            std::pair<model::key, model::value> get(const std::string &path) override;

        private:
            std::shared_ptr<ports::interfaces::repository<model::key>> key_repository;
            std::shared_ptr<ports::interfaces::repository<model::value>> value_repository;
            std::shared_ptr<ports::interfaces::path_to_key_id> path_to_key_id;
        };

    } // namespace impl

} // namespace ports