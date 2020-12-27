#include <memory>

#include "carrotdb/adapters/request.h"

#include "gtest/gtest.h"

namespace
{

    class keys_port_mock : public ports::keys
    {
    public:
        void set(model::key key) override { this->key = key; };
        model::key get(std::string id) override { return key; };
        void del() override { this->key = model::key(); };

    private:
        model::key key;
    };

    class post_request_test : public testing::Test
    {
    protected:
        void SetUp() override
        {
            keys_port = std::make_shared<keys_port_mock>();
            handle = adapters::post_request_handle(keys_port);
            request = web::http::http_request();
        }
        std::shared_ptr<keys_port_mock> keys_port;
        adapters::post_request_handle handle;
        web::http::http_request request;
    };

    TEST_F(post_request_test, with_path)
    {
        request.set_request_uri("my-key");
        handle.handle(request);
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::Created);
        EXPECT_EQ(keys_port->get("my-key").id(), "my-key");
    }

    TEST_F(post_request_test, without_path)
    {
        handle.handle(request);
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::BadRequest);
    }

} // namespace