#pragma once

#include "carrotdb/app/carrot_db.h"

namespace app
{
    class app
    {
    public:
        app();
        void run();

    private:
        carrot_db _carrot_db;
    };
} // namespace app