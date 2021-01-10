#pragma once

#include "carrotdb/ports/repository.h"

#include <string>
#include <shared_mutex>
#include <map>

namespace adapters
{
    template <typename T>
    class repository : public ports::interfaces::repository<T>
    {
    public:
        void set(const T &entry) override
        {
            std::unique_lock lock(mutex);
            entries[entry.id()] = entry;
        }
        T get(const std::string &id) override
        {
            std::shared_lock lock(mutex);
            if (entries.find(id) == entries.end())
            {
                throw ports::interfaces::not_found();
            }
            return entries[id];
        }
        void del(const std::string &id) override
        {
            std::unique_lock lock(mutex);
            entries.erase(entries.find(id));
        }

    private:
        std::map<std::string, T> entries;
        std::shared_mutex mutex;
    }; // namespace adapters
} // namespace adapters