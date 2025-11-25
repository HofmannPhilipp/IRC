
#include "Client.hpp"

Client::Client() : _fd(-1), _nickname(""), _registered(false), _is_op(false) {}

Client::Client(int fd, std::string nickname, bool is_registerd, bool is_op) : _fd(fd), _nickname(nickname), _registered(is_registerd), _is_op(is_op) {}

Client::Client(const Client &other) : _fd(other._fd), _nickname(other._nickname), _registered(other._registered), _is_op(other._is_op) {}

Client &Client::operator=(const Client &other)
{
    if (this == &other)
        return *this;

    _nickname = other._nickname;
    _is_op = other._is_op;
    _fd = other._fd;
    _registered = other._registered;
    return *this;
}

Client::~Client() {}

int Client::get_fd() const
{
    return _fd;
}

std::string Client::get_nickname() const
{
    return _nickname;
}

bool Client::get_registered() const
{
    return _registered;
}

void Client::set_nickname(const std::string &nickname)
{
    _nickname = nickname;
}

void Client::sendMessage(const IrcMsg &response)
{
    send(_fd, response.get_msg().c_str(), response.get_msg().size(), 0);
}