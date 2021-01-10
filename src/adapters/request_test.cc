#include "carrotdb/adapters/request.h"

#include "gtest/gtest.h"

#include <memory>

namespace
{
    class key_srv_mock : public ports::interfaces::key_create_service, public ports::interfaces::key_get_service
    {
    public:
        void create(const model::key &key) override { keys[key.path()] = key; };
        model::key get(const std::string &id) override
        {
            if (keys.find(id) == keys.end())
            {
                throw ports::interfaces::not_found();
            }
            return keys[id];
        };

        std::map<std::string, model::key> keys;
    };

    class request_test : public testing::Test
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

    TEST_F(request_test, post_with_path)
    {
        request.set_request_uri("my-key");
        adapters::post_request_handle(service).handle(request);
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::Created);
        ASSERT_TRUE(service->keys.find("my-key") != service->keys.end());
        EXPECT_EQ(service->keys["my-key"].path(), "my-key");
    }

    TEST_F(request_test, post_with_path_and_body)
    {
        // given request with path and body
        request.set_request_uri("my-key");
        request.set_body("request body");
        // when post handle is invoked
        adapters::post_request_handle(service).handle(request);
        // then key with value is stored in the repository
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::Created);
        ASSERT_TRUE(service->keys.find("my-key") != service->keys.end());
        EXPECT_EQ(service->keys["my-key"].get_value().get_content(), "request body");
    }

    TEST_F(request_test, post_without_path)
    {
        adapters::post_request_handle(service).handle(request);
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::BadRequest);
    }

    TEST_F(request_test, get_for_existing_key)
    {
        // given a key with id exists
        service->create(model::key("my-key"));
        // when get request is issues
        request.set_request_uri("my-key");
        adapters::get_request_handle(service).handle(request);
        // then get response status is ok
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::OK);
    }

    TEST_F(request_test, get_for_existing_key_with_body)
    {
        // given a key with value exists
        service->create(model::key("my-key", model::value("stored value")));
        // when get request is issues
        request.set_request_uri("my-key");
        adapters::get_request_handle(service).handle(request);
        // then get response body has "stored value"
        ASSERT_EQ(request.get_response().get().body().is_valid(), true);
        EXPECT_EQ(request.get_response().get().extract_string().get(), "stored value");
    }

    TEST_F(request_test, get_for_nonexisting_key)
    {
        // given a key with id doesn't exist
        // when get request is issues
        request.set_request_uri("my-key");
        adapters::get_request_handle(service).handle(request);
        // then get response status is ok
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::NotFound);
    }
} // namespace