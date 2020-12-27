#include "carrotdb/adapters/kv_service.h"

namespace adapters
{

    key_value::key_value() {}

    key_value::key_value(std::shared_ptr<ports::key> key_port, std::shared_ptr<ports::value> value_port) : key_port(key_port)
    {
    }

    key_value::~key_value()
    {
    }

    void key_value::handle(get_request &&request)
    {
        request.process(key_port.get());
    }
} // namespace adapters