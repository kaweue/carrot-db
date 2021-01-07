#include "cpprest/http_client.h"
#include "carrotdb/app/carrot_db.h"

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
        }
        std::unique_ptr<http::client::http_client> client;
        std::unique_ptr<app::carrot_db> carrot_db;
    };

    TEST_F(rest_test, get)
    {
        //given empty db
        //when get request is issued
        auto response = client->request(http::methods::GET, "my-key");
        //then not found response is issued
        response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::NotFound);
                    return response.body().close();
                })
            .wait();
    }

    TEST_F(rest_test, post)
    {
        auto response = client->request(http::methods::POST, "my-key");
        response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::Created);
                    return response.body().close();
                })
            .wait();
    }

    TEST_F(rest_test, post_with_body)
    {
        auto response = client->request(http::methods::POST, "my-key", "", "stored value");
        response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::Created);
                    return response.body().close();
                })
            .wait();
    }

    TEST_F(rest_test, delete_request)
    {
        auto response = client->request(http::methods::DEL);
        response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::NotImplemented);
                    return response.body().close();
                })
            .wait();
    }

    TEST_F(rest_test, put)
    {
        auto response = client->request(http::methods::PUT);
        response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::NotImplemented);
                    return response.body().close();
                })
            .wait();
    }

    TEST_F(rest_test, get_after_post)
    {
        //given my-key is created
        client->request(http::methods::POST, "my-key").wait();
        //when get request for existing key is issued
        auto response = client->request(http::methods::GET, "my-key");
        //then server answers that key exists
        response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::OK);
                    return response.body().close();
                })
            .wait();
    }

    TEST_F(rest_test, get_after_post_with_body)
    {
        //given my-key with content is created
        const std::string content("content");
        client->request(http::methods::POST, "my-key", content.c_str()).wait();
        //when get request for existing key is issued
        auto response = client->request(http::methods::GET, "my-key");
        //then server answers that key exists with correct value
        concurrency::streams::container_buffer<std::string> body;
        response.then([&](http::http_response response) {
                    EXPECT_EQ(response.status_code(), web::http::status_codes::OK);
                    return response.body().read_to_end(body);
                })
            .then([&](size_t response_length) {
                EXPECT_EQ(response_length, content.length());
                EXPECT_EQ(body.collection(), content);
            })
            .wait();
    }

} // namespace
