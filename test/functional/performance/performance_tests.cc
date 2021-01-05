#include "cpprest/http_client.h"
#include "carrotdb/app/carrot_db.h"

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
            auto uri = "http://0.0.0.0:5800/";
            carrot_db = std::make_unique<app::carrot_db>(uri);
            carrot_db->start();
            client = std::make_unique<http::client::http_client>(http::uri(uri));
        }

        void TearDown() override
        {
            carrot_db->stop();
            carrot_db.release();
            client.release();
            tasks.clear();
        }

        void test_posts_and_gets_performance()
        {
            for (int i = 0; i < 10; i++)
            {
                send_post_and_gets_requests_batch(i);
                wait_for_all_requests();
            }
        }

        void send_post_and_gets_requests_batch(uint batch_number)
        {
            for (int request_number = 0; request_number < 100; request_number++)
            {
                sent_test_request(http::methods::POST, make_request_path(batch_number, request_number));
                sent_test_request(http::methods::GET, make_request_path(batch_number, request_number));
            }
        }

        std::string make_request_path(uint batch_number, uint request_number)
        {
            return "my-key-" + std::to_string(batch_number) + "-" + std::to_string(request_number);
        }

        void sent_test_request(http::method method, std::string key)
        {
            auto task = client->request(http::methods::GET, key);
            task.then([&](http::http_response response) {
                EXPECT_TRUE(assert_non_error_status_response(response));
                return response.body().close();
            });
            tasks.push_back(task);
        };

        void wait_for_all_requests()
        {
            for (auto task : tasks)
            {
                task.wait();
            }
        }

        testing::AssertionResult assert_non_error_status_response(http::http_response response)
        {
            auto status_code = response.status_code();
            switch (status_code)
            {
            case web::http::status_codes::NotFound:
            case web::http::status_codes::OK:
            case web::http::status_codes::Created:
                return testing::AssertionSuccess();
            default:
                return testing::AssertionFailure() << "unexpected status code = " << status_code;
            }
        }

        std::unique_ptr<http::client::http_client> client;
        std::unique_ptr<app::carrot_db> carrot_db;
        std::vector<pplx::task<web::http::http_response>> tasks;
    };

    TEST_F(rest_test, posts_and_gets_performance)
    {
        auto test_start = std::chrono::high_resolution_clock::now();
        test_posts_and_gets_performance();
        auto test_end = std::chrono::high_resolution_clock::now();
        auto test_duration = std::chrono::duration_cast<std::chrono::seconds>(test_end - test_start).count();
        EXPECT_LE(test_duration, 10);

    } // namespace

} // namespace
