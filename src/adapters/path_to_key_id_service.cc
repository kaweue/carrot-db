#include "carrotdb/adapters/path_to_key_id_service.h"

namespace adapters
{

    std::string path_to_key_id_service::get_key_id(const std::string &path) const
    {
        std::shared_lock lock(mutex);
        if (entries.find(path) == entries.end())
        {
            throw ports::interfaces::not_found();
        }
        return entries.at(path);
    }

    void path_to_key_id_service::created(const model::key &key)
    {
        std::unique_lock lock(mutex);
        entries[key.path()] = key.id();
    }

} // namespace adapters