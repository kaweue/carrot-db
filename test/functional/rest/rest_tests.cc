#include "cpprest/http_client.h"
#include "carrotdb/carrot_db.h"

#include "gtest/gtest.h"

#include <memory>

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

    TEST_F(rest_test, get)
    {
        auto response = client->request(http::methods::GET, "/");
        response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::OK);
                    return response.body().close();
                })
            .wait();
    }

    TEST_F(rest_test, post)
    {
        auto response = client->request(http::methods::POST, "/");
        response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::NotImplemented);
                    return response.body().close();
                })
            .wait();
    }

    TEST_F(rest_test, delete_request)
    {
        auto response = client->request(http::methods::DEL, "/");
        response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::NotImplemented);
                    return response.body().close();
                })
            .wait();
    }

    TEST_F(rest_test, put)
    {
        auto response = client->request(http::methods::PUT, "/");
        response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::NotImplemented);
                    return response.body().close();
                })
            .wait();
    }

} // namespace
