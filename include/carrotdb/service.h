#pragma once
#include <memory>
#include <iostream>

#include "carrotdb/request.h"

namespace service
{
    class service
    {
    public:
        service(){};
        explicit service(std::shared_ptr<service> next_service) : m_next_service(next_service){};
        virtual ~service(){};

        template <typename T>
        void proces_next(T &&request)
        {
            if (m_next_service)
            {
                m_next_service->handle(std::move(request));
            };
        }

        virtual void handle(get_request &&request)
        {
            proces_next(std::move(request));
        };

        virtual void handle(put_request &&request)
        {
            proces_next(std::move(request));
        };

        virtual void handle(post_request &&request)
        {
            proces_next(std::move(request));
        };

        virtual void handle(delete_request &&request)
        {
            proces_next(std::move(request));
        };

    private:
        std::shared_ptr<service> m_next_service;
    };
} // namespace service