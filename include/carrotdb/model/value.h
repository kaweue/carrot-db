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
        value(const value &) = default;
        value &operator=(const value &value) = default;

        value() : _id(boost::uuids::random_generator()()) {}

        explicit value(std::string &&content) : _id(boost::uuids::random_generator()()), _content(std::move(content)) {}

        value &operator=(value &&other)
        {
            _id = other._id;
            _content = std::move(other._content);
            return *this;
        }

        std::string id() const;

        const std::string &get_content() const
        {
            return _content;
        }

        bool empty() const
        {
            return _content.empty();
        }

    private:
        boost::uuids::uuid _id;
        std::string _content;
    };
} // namespace model