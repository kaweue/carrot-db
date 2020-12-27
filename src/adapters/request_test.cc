#include <memory>

#include "carrotdb/adapters/request.h"

#include "gtest/gtest.h"

namespace
{

    class post_request_test : public testing::Test
    {
    protected:
        void SetUp() override
        {
            handle = adapters::post_request_handle();
            request = web::http::http_request();
        }

        adapters::post_request_handle handle;
        web::http::http_request request;
    };

    TEST_F(post_request_test, with_path)
    {
        request.set_request_uri("my-key");
        handle.handle(request);
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::Created);
    }

    TEST_F(post_request_test, without_path)
    {
        handle.handle(request);
        EXPECT_EQ(request.get_response().get().status_code(), web::http::status_codes::BadRequest);
    }

} // namespace