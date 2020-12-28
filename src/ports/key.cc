#include "carrotdb/ports/key_value.h"

namespace ports
{
    void keys_impl::set(const model::key &key)
    {
        std::unique_lock lock(mutex);
        keys[key.id()] = key;
    }

    model::key keys_impl::get(const std::string &id)
    {
        std::shared_lock lock(mutex);
        if (keys.find(id) == keys.end())
        {
            throw ports::keys::not_found_exception();
        }
        return keys[id];
    }

    void keys_impl::del(const std::string &id)
    {
        std::unique_lock lock(mutex);
        keys.erase(keys.find(id));
    }
} // namespace ports