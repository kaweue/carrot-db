#pragma once

#include "carrotdb/ports/key_services.h"
#include "carrotdb/ports/path_to_key_id.h"

#include <string>
#include <memory>

namespace adapters
{

    class path_to_key_id_service
        : public ports::impl::key_create_service::create_observer,
          public ports::interfaces::path_to_key_id
    {
    public:
        std::string get_key_id(const std::string &path) override
        {
            std::shared_lock lock(mutex);
            if (entries.find(path) == entries.end())
            {
                throw ports::interfaces::not_found();
            }
            return entries[path];
        };
        void created(const model::key &key) override
        {
            std::unique_lock lock(mutex);
            entries[key.path()] = key.id();
        }

    private:
        std::map<std::string, std::string> entries;
        std::shared_mutex mutex;
    };
} // namespace adapters