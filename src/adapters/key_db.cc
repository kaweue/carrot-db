#include "carrotdb/adapters/key_db.h"

namespace adapters
{
    void key_db::set(const model::key &key)
    {
        std::unique_lock lock(mutex);
        keys[key.id()] = key;
    }

    model::key key_db::get(const std::string &id)
    {
        std::shared_lock lock(mutex);
        if (keys.find(id) == keys.end())
        {
            throw ports::key_repository::not_found_exception();
        }
        return keys[id];
    }

    void key_db::del(const std::string &id)
    {
        std::unique_lock lock(mutex);
        keys.erase(keys.find(id));
    }
} // namespace adapters