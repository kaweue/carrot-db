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

        int request_cnt;
    };

    class api_service_test : public testing::Test
    {
    };

    TEST_F(api_service_test, Post)
    {
        auto request_handle = std::make_shared<request_handle_mock>();
        auto handlers = std::map<web::http::method, std::shared_ptr<adapters::request_handle>>{
            {web::http::methods::POST, request_handle}};

        auto api = adapters::api(handlers);
        api.rest_handle(web::http::http_request(web::http::methods::POST));
        EXPECT_EQ(request_handle->request_cnt, 1);
    }

} // namespace
