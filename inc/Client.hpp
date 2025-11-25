
#pragma once

#include "IrcMsg.hpp"
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

    int get_fd() const;
    std::string get_nickname() const;
    bool get_registered() const;

    void set_nickname(const std::string &nickname);

    void sendMessage(const IrcMsg &msg);
};
