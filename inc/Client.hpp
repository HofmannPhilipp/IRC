
#pragma once

#include <poll.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

class Client
{
private:
    int _fd;
    std::string _nickname;
    bool _registered;
    bool _is_op;

public:
    Client();
    Client(int fd, std::string nickname, bool registered, bool is_op);
    Client(const Client &other);
    Client &operator=(const Client &other);
    ~Client();

    bool get_registered();
    void sendMessage(const std::string &msg);
};
