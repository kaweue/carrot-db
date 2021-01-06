#pragma once

#include <carrotdb/model/key.h>

#include <string>
#include <shared_mutex>
#include <map>

namespace ports
{
    class key_repository
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

    class values
    {
    };

} // namespace ports