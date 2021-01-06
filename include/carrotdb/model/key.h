#pragma once

#include <string>
#include "carrotdb/model/value.h"
namespace model
{
    class key
    {
    public:
        key(){};
        key(const std::string &id) : _id(id){};
        key(const std::string &id, const value &value) : _id(id), _value(value){};

        std::string id() const
        {
            return _id;
        };

    private:
        std::string _id;
        value _value;
    };
} // namespace model