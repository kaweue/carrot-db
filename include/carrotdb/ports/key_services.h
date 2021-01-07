#include "carrotdb/model/key.h"
#include "carrotdb/ports/key_repository.h"

#include <string>
#include <memory>

namespace ports
{

    namespace interfaces
    {
        class key_create_service
        {
        public:
            virtual void create(const model::key &key) = 0;
            virtual ~key_create_service() = default;
        };

        class key_get_service
        {
        public:
            virtual model::key get(const std::string &id) = 0;
            virtual ~key_get_service() = default;
        };
    } // namespace interfaces

    namespace impl
    {
        class key_create_service : public interfaces::key_create_service
        {
        public:
            explicit key_create_service(std::shared_ptr<ports::key_repository> key_repository);
            void create(const model::key &key) override;

        private:
            std::shared_ptr<ports::key_repository> key_repository;
        };

        class key_get_service : public interfaces::key_get_service
        {
        public:
            explicit key_get_service(std::shared_ptr<ports::key_repository> key_repository);
            model::key get(const std::string &path) override;

        private:
            std::shared_ptr<ports::key_repository> key_repository;
        };

    } // namespace impl

} // namespace ports