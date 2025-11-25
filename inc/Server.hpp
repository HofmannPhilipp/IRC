
#pragma once

#include "Client.hpp"
#include "IrcMsg.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <exception>

class Server
{
private:
    int _port;
    std::string _password;
    int _server_fd;
    std::vector<Client> _clients;
    std::vector<pollfd> _poll_fds;

public:
    class ServerException : public std::exception
    {
    private:
        std::string _message;

    public:
        ServerException(const std::string &msg) : _message(msg) {}
        const char *what() const noexcept override { return _message.c_str(); }
    };

    Server(int _port, std::string _password);
    Server(const Server &other);
    Server &operator=(const Server &other);
    ~Server();

    void init(int domain);
    void run();
    // void handle_msg(std::string msg);
    void handle_request(const Client &client, const IrcMsg &request);
    void send_response(const Client &client, const IrcMsg &response);
};