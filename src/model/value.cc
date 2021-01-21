#include "carrotdb/model/value.h"

namespace model
{
    std::string value::id() const
    {
        return boost::uuids::to_string(_id);
    }
} // namespace model