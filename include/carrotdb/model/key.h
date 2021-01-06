#pragma once

#include "carrotdb/model/value.h"

#include <string>

namespace model
{
    class key
    {
    public:
        key(){};
        key(const std::string &path) : _path(path){};
        key(const std::string &path, const value &value) : _path(path), _value(value){};

        std::string path() const
        {
            return _path;
        };

        value get_value() const
        {
            return _value;
        };

    private:
        std::string _path;
        std::string _id;
        value _value;
    };
} // namespace model