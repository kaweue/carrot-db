#pragma once

#include <memory>

#include "carrotdb/adapters/service.h"
#include "carrotdb/ports/key_value.h"

namespace adapters
{
    class key_value : public service
    {
    public:
        key_value();
        key_value(std::shared_ptr<ports::key_value> port);
        ~key_value();
    };

} // namespace adapters