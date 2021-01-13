#pragma once

#include "carrotdb/model/value.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <string>

namespace model
{
    class key
    {
    public:
        key(){};
        key(const std::string &path)
            : _path(path), _id(boost::uuids::random_generator()()){};
        key(const std::string &path, const value & value)
            : _path(path), _id(boost::uuids::random_generator()()){
                _value_id = value.id();
            };

        std::string path() const
        {
            return _path;
        };

        std::string id() const
        {
            return boost::uuids::to_string(_id);
        };

        std::string value_id() const
        {
            return _value_id;
        };

    private:
        std::string _path;
        boost::uuids::uuid _id;
        std::string _value_id;
    };
} // namespace model