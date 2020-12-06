/***
 * Copyright (C) Microsoft. All rights reserved.
 * Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * bingrequest.cpp - Simple cmd line application that makes an HTTP GET request to bing searching and outputting
 *       the resulting HTML response body into a file.
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

#include <cpprest/filestream.h>
#include <cpprest/http_client.h>

using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

int main(int argc, char *args[])
{
    if (argc != 3)
    {
        printf("Usage: BingRequest.exe search_term output_file\n");
        return -1;
    }
    const string_t searchTerm = args[1];
    const string_t outputFileName = args[2];

    // Open a stream to the file to write the HTTP response body into.
    auto fileBuffer = std::make_shared<streambuf<uint8_t>>();
    file_buffer<uint8_t>::open(outputFileName, std::ios::out)
        .then([=](streambuf<uint8_t> outFile) -> pplx::task<http_response> {
            *fileBuffer = outFile;

            // Create an HTTP request.
            // Encode the URI query since it could contain special characters like spaces.
            http_client client(U("http://www.bing.com/"));
            return client.request(methods::GET, uri_builder(U("/search")).append_query(U("q"), searchTerm).to_string());
        })

        // Write the response body into the file buffer.
        .then([=](http_response response) -> pplx::task<size_t> {
            printf("Response status code %u returned.\n", response.status_code());

            return response.body().read_to_end(*fileBuffer);
        })

        // Close the file buffer.
        .then([=](size_t) { return fileBuffer->close(); })

        // Wait for the entire response body to be written into the file.
        .wait();

    return 0;
}
