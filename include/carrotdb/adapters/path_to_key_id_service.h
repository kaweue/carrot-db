#pragma once

#include "carrotdb/ports/key_create_service.h"
#include "carrotdb/ports/path_to_key_id.h"

#include <string>
#include <map>
#include <memory>
#include <shared_mutex>

namespace adapters
{

    class path_to_key_id_service
        : public ports::impl::key_create_service::create_observer,
          public ports::interfaces::path_to_key_id
    {
    public:
        std::string get_key_id(const std::string &path) const override;
        void created(const model::key &key) override;

    private:
        std::map<std::string, std::string> entries;
        mutable std::shared_mutex mutex;
    };
} // namespace adapters