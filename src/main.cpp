
#include "Server.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Error: Wrong number of arguments." << std::endl;
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);
    std::string password = argv[2];

    try
    {
        Server local("bucks34", port, password);
        local.init(INADDR_LOOPBACK);
        local.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Server Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}