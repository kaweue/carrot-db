#include "carrotdb/app/app.h"

int main(int argc, char *argv[])
{
    auto app = app::app();
    std::cout << "running..." << std::endl;
    app.run();

    std::cout << "bye bye" << std::endl;
    return 0;
}