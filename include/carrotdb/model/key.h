#pragma once

#include <string>

namespace model
{
    class key
    {
    public:
        key(){};
        key(std::string id) : _id(id){};

        std::string id() const
        {
            return _id;
        };

    private:
        std::string _id;
    };
} // namespace model