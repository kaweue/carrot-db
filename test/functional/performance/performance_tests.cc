#include "cpprest/http_client.h"
#include "carrotdb/carrot_db.h"

#include "gtest/gtest.h"

#include <memory>
#include <thread>
#include <chrono>

namespace
{
    using namespace web;
    class rest_test : public testing::Test
    {
    protected:
        void SetUp() override
        {
            auto uri = "http://0.0.0.0:34567/";
            carrot_db = std::make_unique<app::carrot_db>(uri);
            carrot_db->start();
            client = std::make_unique<http::client::http_client>(http::uri(uri));
        }

        void TearDown() override
        {
            carrot_db->stop();
            carrot_db.release();
            client.release();
        }
        std::unique_ptr<http::client::http_client> client;
        std::unique_ptr<app::carrot_db> carrot_db;
    };

    TEST_F(rest_test, posts_and_gets)
    {
        auto is_status_valid = [](web::http::status_code code) {
            if (code == web::http::status_codes::NotFound || code == web::http::status_codes::OK)
                return testing::AssertionSuccess();
            else
                return testing::AssertionFailure() << "unexpected status code = " << code;
        };

        auto test_start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10; i++)
        {
            std::vector<pplx::task<web::http::http_response>> tasks;
            for (int j = 0; j < 100; j++)
            {
                auto post_response = client->request(http::methods::POST, "my-key-" + std::to_string(i) + "-" + std::to_string(j));
                post_response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::Created);
                    return response.body().close();
                });
                tasks.push_back(post_response);
                auto get_response = client->request(http::methods::GET, "my-key-" + std::to_string(i) + "-" + std::to_string(j));
                //then not found response is issued
                get_response.then([&](http::http_response response) {
                    EXPECT_TRUE(is_status_valid(response.status_code()));
                    return response.body().close();
                });
                tasks.push_back(get_response);
            }
            for (auto task : tasks)
            {
                task.wait();
            }
        }

        auto test_end = std::chrono::high_resolution_clock::now();
        auto test_duration = std::chrono::duration_cast<std::chrono::seconds>(test_end - test_start).count();
        EXPECT_LE(test_duration, 10);

    } // namespace

} // namespace
