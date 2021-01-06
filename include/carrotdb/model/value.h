#pragma once

#include <string>

namespace model
{
    class value
    {
    public:
        value(){};
        value(const std::string &id, const std::string &value) : _id(id), _value(value){};

        std::string id() const
        {
            return _id;
        };

    private:
        std::string _id;
        std::string _value;
    };
} // namespace model