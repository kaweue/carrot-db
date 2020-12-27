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
        key_value(std::shared_ptr<ports::key> key_port, std::shared_ptr<ports::value> value_port);
        ~key_value();
        void handle(get_request &&request) override;

    private:
        std::shared_ptr<ports::key> key_port;
    };

} // namespace adapters