#pragma once

#include <carrotdb/model/key.h>

#include <string>
#include <shared_mutex>
#include <map>

namespace ports
{
    class keys
    {
    public:
        class not_found_exception : public std::exception
        {
        public:
            const char *what() const noexcept { return "key not found"; }
        };

        virtual void set(const model::key &key) = 0;
        virtual model::key get(const std::string &id) = 0;
        virtual void del(const std::string &id) = 0;
    };

    class keys_impl : public keys
    {
    public:
        void set(const model::key &key);
        model::key get(const std::string &id);
        void del(const std::string &id);

    private:
        std::map<std::string, model::key> keys;
        std::shared_mutex mutex;
    };

    class values
    {
    };

} // namespace ports