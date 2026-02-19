
#pragma once

#include "IrcMsg.hpp"
#include <poll.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <exception>
#include <unistd.h>
#include <functional>
#include <algorithm>

#define MAX_READBUF 8192
#define MAX_WRITEBUF 1024 * 1024 // 1 MB

class Channel;

class Client
{
private:
    int _fd;
    std::string _nickname;
    std::string _username;
    std::string _realName;
    std::string _hostname;

    bool _hasNick;
    bool _hasUser;
    bool _hasPass;
    bool _isRegistered;

    std::vector<Channel *> _joinedChannels;

    std::string _readBuffer;
    std::string _writeBuffer;

public:
    Client();
    Client(int fd);
    Client(int fd, const std::string &hostname);
    Client(const Client &other);
    Client &operator=(const Client &other);
    // Client(Client &&other) noexcept;
    // Client &operator=(Client &&other) noexcept;
    ~Client();

    int getFd() const;
    std::string getNickname() const;
    std::string getUsername() const;
    std::string getRealname() const;
    std::string getHostname() const;
    bool getIsRegistered() const;
    std::vector<Channel *> &getChannels();
    std::string getPrefix() const;

    std::string getReadBuffer();
    std::string &getWriteBuffer();
    bool hasNick() const;
    bool hasUser() const;
    bool hasPass() const;

    void joinChannel(Channel *channel);

    void setNickname(const std::string &nick);
    void setUsername(const std::string &name);
    void setRealname(const std::string &name);
    void setHasPass(bool flag);
    void setHasNick(bool flag);
    void setHasUser(bool flag);

    void setReadBuffer(const std::string &buffer);
    void appendToReadBuffer(const std::string &data);
    void setWriteBuffer(const std::string &buffer);
    void appendToWriteBuffer(const std::string &data);

    bool canRegister();
    // void sendMessage(const std::string &msg) const;
};

std::ostream &operator<<(std::ostream &os, const Client &client);