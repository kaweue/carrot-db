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
                throw ports::key_repository::not_found_exception();
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