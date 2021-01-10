#pragma once

#include <string>

namespace ports
{
    namespace interfaces
    {
        class path_to_key_id
        {
        public:
            virtual std::string get_key_id(const std::string &path) = 0;
        };
    } // namespace interfaces
} // namespace ports