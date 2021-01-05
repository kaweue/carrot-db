#include "carrotdb/carrot_db.h"
#include "pplx/threadpool.h"
#include <memory>

int main(int argc, char *argv[])
{
    auto uri = "http://0.0.0.0:34567/";
    auto carrot_db = std::make_unique<app::carrot_db>(uri);
    std::cout << "Starting server..." << std::endl;

    carrot_db->start();
    auto &io_service = crossplat::threadpool::shared_instance().service();
    boost::asio::signal_set signals(io_service, SIGINT);
    // Start an asynchronous wait for one of the signals to occur.
    signals.async_wait([&](const boost::system::error_code &error, int signal_number) {
        std::cout << "received interuption signal " << std::endl;
        carrot_db->stop();
        io_service.stop();
    });

    io_service.run();

    std::cout << "bye bye" << std::endl;
    return 0;
}