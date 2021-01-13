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
        class key_create_service
        {
        public:
            virtual void create(model::key &&key, model::value &&value) = 0;
            virtual ~key_create_service() = default;
        };

        class key_get_service
        {
        public:
            virtual std::pair<model::key, model::value> get(const std::string &id) = 0;
            virtual ~key_get_service() = default;
        };
    } // namespace interfaces

    namespace impl
    {
        class key_create_service : public interfaces::key_create_service
        {
        public:
            class create_observer
            {
            public:
                virtual void created(const model::key &key) = 0;
            };
            explicit key_create_service(std::shared_ptr<ports::interfaces::repository<model::key>> key_repository,
                                        std::shared_ptr<ports::interfaces::repository<model::value>> value_repository);
            void create(model::key &&key, model::value &&value) override;
            void set_observer(std::weak_ptr<ports::impl::key_create_service::create_observer> observer);

        private:
            std::shared_ptr<ports::interfaces::repository<model::key>> key_repository;
            std::shared_ptr<ports::interfaces::repository<model::value>> value_repository;
            std::weak_ptr<create_observer> observer;
            void store_key_and_value(const model::key &key, const model::value & value);
            void notify_observer(const model::key &key);
        };

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