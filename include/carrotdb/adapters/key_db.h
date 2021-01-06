#pragma once

#include <carrotdb/model/key.h>
#include <carrotdb/ports/key_repository.h>

#include <string>
#include <shared_mutex>
#include <map>

namespace adapters
{
    class key_db : public ports::key_repository
    {
    public:
        void set(const model::key &key);
        model::key get(const std::string &id);
        void del(const std::string &id);

    private:
        std::map<std::string, model::key> keys;
        std::shared_mutex mutex;
    };
} // namespace adapters