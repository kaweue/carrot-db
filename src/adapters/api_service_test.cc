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

    TEST(ObjectLiveCycle, SimpleCreate)
    {
        auto ns = std::make_shared<next_service_mock>();
        auto api = std::make_shared<adapters::api>(ns);
    }

    TEST(REST, Post)
    {
        auto ns = std::make_shared<next_service_mock>();
        auto api = std::make_shared<adapters::api>(ns);
        api->rest_post(web::http::http_request());
        EXPECT_EQ(ns->post_cnt, 1);
    }

    TEST(REST, Get)
    {
        auto ns = std::make_shared<next_service_mock>();
        auto api = std::make_shared<adapters::api>(ns);
        api->rest_get(web::http::http_request());
        EXPECT_EQ(ns->get_cnt, 1);
    }

    TEST(REST, Delete)
    {
        auto ns = std::make_shared<next_service_mock>();
        auto api = std::make_shared<adapters::api>(ns);
        api->rest_delete(web::http::http_request());
        EXPECT_EQ(ns->delete_cnt, 1);
    }

    TEST(REST, Put)
    {
        auto ns = std::make_shared<next_service_mock>();
        auto api = std::make_shared<adapters::api>(ns);
        api->rest_put(web::http::http_request());
        EXPECT_EQ(ns->put_cnt, 1);
    }

} // namespace
