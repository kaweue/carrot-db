#include "carrotdb/adapters/key_db.h"

namespace adapters
{
    void key_db::set(const model::key &key)
    {
        std::unique_lock lock(mutex);
        keys[key.path()] = key;
    }

    model::key key_db::get(const std::string &path)
    {
        std::shared_lock lock(mutex);
        if (keys.find(path) == keys.end())
        {
            throw ports::key_repository::not_found_exception();
        }
        return keys[path];
    }

    void key_db::del(const std::string &path)
    {
        std::unique_lock lock(mutex);
        keys.erase(keys.find(path));
    }
} // namespace adapters