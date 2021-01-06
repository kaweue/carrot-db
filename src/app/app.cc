#include "carrotdb/app/app.h"
#include "pplx/threadpool.h"
#include <memory>

namespace app
{
    app::app() : _carrot_db("http://0.0.0.0:5800/")
    {
    }

    void app::run()
    {
        _carrot_db.start();
        auto &io_service = crossplat::threadpool::shared_instance().service();
        boost::asio::signal_set signals(io_service, SIGINT);
        signals.async_wait([&](const boost::system::error_code &error, int signal_number) {
            std::cout << "received interuption signal " << std::endl;
            _carrot_db.stop();
            io_service.stop();
        });

        io_service.run();
    }
} // namespace app