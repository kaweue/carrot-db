#include "carrotdb/adapters/post_request.h"

#include "gtest/gtest.h"

#include <memory>
#include <utility>

namespace
{
    class key_srv_mock : public ports::interfaces::key_create_service
    {
    public:
        void create(model::key &&key, model::value &&value) override { kvs[key.path()] = std::pair(key, value); };

        std::map<std::string, std::pair<model::key, model::value>> kvs;
    };

    class post_request_test : public testing::Test
    {
    protected:
        void SetUp() override
        {
            service = std::make_shared<key_srv_mock>();
            request = web::http::http_request();
        }
        std::shared_ptr<key_srv_mock> service;
        web::http::http_request request;
    };

    TEST_F(post_request_test, post_with_path)
    {
        request.set_request_uri("my-key");
        adapters::post_request_handle(service).handle(request);
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::Created);
        ASSERT_TRUE(service->kvs.find("my-key") != service->kvs.end());
        EXPECT_EQ(service->kvs["my-key"].first.path(), "my-key");
    }

    TEST_F(post_request_test, post_with_path_and_body)
    {
        // given request with path and body
        request.set_request_uri("my-key");
        request.set_body("request body");
        // when post handle is invoked
        adapters::post_request_handle(service).handle(request);
        // then key with value is stored in the repository
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::Created);
        ASSERT_TRUE(service->kvs.find("my-key") != service->kvs.end());
        EXPECT_EQ(service->kvs["my-key"].second.get_content(), "request body");
    }

    TEST_F(post_request_test, post_without_path)
    {
        adapters::post_request_handle(service).handle(request);
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::BadRequest);
    }
} // namespace