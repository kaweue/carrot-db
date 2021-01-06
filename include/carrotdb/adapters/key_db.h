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
        void set(const model::key &key) override;
        model::key get(const std::string &path) override;
        void del(const std::string &path) override;

    private:
        std::map<std::string, model::key> keys;
        std::shared_mutex mutex;
    };
} // namespace adapters