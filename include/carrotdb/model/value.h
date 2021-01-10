#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string>

namespace model
{
    class value
    {
    public:
        value(){};
        value(const std::string &content) : _id(boost::uuids::random_generator()()), _content(content){};

        std::string id() const
        {
            return boost::uuids::to_string(_id);
        };

        std::string get_content() const
        {
            return _content;
        };

    private:
        boost::uuids::uuid _id;
        std::string _content;
    };
} // namespace model