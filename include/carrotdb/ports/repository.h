#pragma once

#include <string>

namespace ports
{
    namespace interfaces
    {
        template <typename T>
        class repository
        {
        public:
            virtual void set(const T &key) = 0;
            virtual T get(const std::string &id) const = 0;
            virtual void del(const std::string &id) = 0;
        };

        class not_found : public std::exception
        {
        public:
            const char *what() const noexcept { return "entry not found"; }
        };

    } // namespace interfaces

} // namespace ports