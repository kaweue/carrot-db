#pragma once

#include <carrotdb/model/key.h>

#include <string>

namespace ports
{
    class keys
    {
    public:
        virtual void set(model::key key) = 0;
        virtual model::key get(std::string id) = 0;
        virtual void del() = 0;
    };
    class keys_impl : public keys
    {
        void set(model::key key);
        model::key get(std::string id);
        void del();
    };

    class values
    {
    };

} // namespace ports