#pragma once

#include <string>

namespace model
{
    class value
    {
    public:
        value(){};
        value(const std::string &id, const std::string &content) : _id(id), _content(content){};

        std::string id() const
        {
            return _id;
        };

        std::string get_content() const
        {
            return _content;
        };

    private:
        std::string _id;
        std::string _content;
    };
} // namespace model