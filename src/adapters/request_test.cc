#include <memory>

#include "carrotdb/adapters/request.h"

#include "gtest/gtest.h"

namespace
{

    class keys_port_mock : public ports::keys
    {
    public:
        void set(const model::key &key) override { keys[key.id()] = key; };
        model::key get(const std::string &id) override
        {
            if (keys.find(id) == keys.end())
            {
                throw ports::keys::not_found_exception();
            }
            return keys[id];
        };
        void del(const std::string &id) override { keys.erase(keys.find(id)); };

    private:
        std::map<std::string, model::key> keys;
    };

    class request_test : public testing::Test
    {
    protected:
        void SetUp() override
        {
            keys_port = std::make_shared<keys_port_mock>();
            request = web::http::http_request();
        }
        std::shared_ptr<keys_port_mock> keys_port;
        web::http::http_request request;
    };

    TEST_F(request_test, post_with_path)
    {
        request.set_request_uri("my-key");
        adapters::post_request_handle(keys_port).handle(request);
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::Created);
        EXPECT_EQ(keys_port->get("my-key").id(), "my-key");
    }

    TEST_F(request_test, post_without_path)
    {
        adapters::post_request_handle(keys_port).handle(request);
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::BadRequest);
    }

    TEST_F(request_test, get_for_existing_key)
    {
        // given a key with id exists
        keys_port->set(model::key("my-key"));
        // when get request is issues
        request.set_request_uri("my-key");
        adapters::get_request_handle(keys_port).handle(request);
        // then get response status is ok
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::OK);
    }

    TEST_F(request_test, get_for_nonexisting_key)
    {
        // given a key with id doesn't exist
        // when get request is issues
        request.set_request_uri("my-key");
        adapters::get_request_handle(keys_port).handle(request);
        // then get response status is ok
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::NotFound);
    }
} // namespace