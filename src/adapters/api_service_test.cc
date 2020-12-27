#include <memory>

#include "carrotdb/adapters/api_service.h"

#include "gtest/gtest.h"

namespace
{
    class request_handle_mock : public adapters::request_handle
    {
    public:
        void handle(web::http::http_request request) override
        {
            request_cnt++;
        };

        web::http::method method() override
        {
            return web::http::methods::POST;
        }

        int request_cnt;
    };

    class api_service_test : public testing::Test
    {
    protected:
        void SetUp() override
        {
            request_handle = std::make_shared<request_handle_mock>();
            api = adapters::api({request_handle});
        }

        void TearDown() override
        {
            request_handle.reset();
        }
        std::shared_ptr<request_handle_mock> request_handle;
        adapters::api api;
    };

    TEST_F(api_service_test, implemented)
    {
        api.rest_handle(web::http::http_request(web::http::methods::POST));
        EXPECT_EQ(request_handle->request_cnt, 1);
    }

    TEST_F(api_service_test, not_implemented)
    {
        api.rest_handle(web::http::http_request(web::http::methods::GET));
        EXPECT_EQ(request_handle->request_cnt, 0);
    }

} // namespace
