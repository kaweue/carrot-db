#include <memory>

#include "carrotdb/adapters/api_service.h"
#include "carrotdb/adapters/service.h"
#include "carrotdb/adapters/request.h"

#include "gtest/gtest.h"

namespace
{
    class next_service_mock : public adapters::service
    {
    public:
        void handle(::adapters::post_request &&request) override
        {
            post_cnt++;
        };

        void handle(::adapters::get_request &&request) override
        {
            get_cnt++;
        };

        void handle(::adapters::put_request &&request) override
        {
            put_cnt++;
        };

        void handle(::adapters::delete_request &&request) override
        {
            delete_cnt++;
        };
        int post_cnt;
        int get_cnt;
        int put_cnt;
        int delete_cnt;
    };

    class api_service_test : public testing::Test
    {
    protected:
        void SetUp() override
        {
            next_service = std::make_shared<next_service_mock>();
            api = std::make_shared<adapters::api>(next_service);
        }

        void TearDown() override
        {
            next_service.reset();
            api.reset();
        }
        std::shared_ptr<next_service_mock> next_service;
        std::shared_ptr<adapters::api> api;
    };

    TEST_F(api_service_test, Post)
    {
        api->rest_post(web::http::http_request());
        EXPECT_EQ(next_service->post_cnt, 1);
    }

    TEST_F(api_service_test, Get)
    {
        api->rest_get(web::http::http_request());
        EXPECT_EQ(next_service->get_cnt, 1);
    }

    TEST_F(api_service_test, Delete)
    {
        api->rest_delete(web::http::http_request());
        EXPECT_EQ(next_service->delete_cnt, 1);
    }

    TEST_F(api_service_test, Put)
    {
        api->rest_put(web::http::http_request());
        EXPECT_EQ(next_service->put_cnt, 1);
    }
} // namespace
