#include "Server.hpp"

bool Server::channelExists(std::string channelName)
{
    for (auto it = _channelList.begin(); it != _channelList.end(); it++)
    {
        if (it->getName() == channelName)
        {
            return true;
        }
    }
    return false;
}

Channel &Server::getChannel(const std::string &name)
{
    for (auto it = _channelList.begin(); it != _channelList.end(); it++)
    {
        if (it->getName() == name)
        {
            return (*it);
        }
    }
    throw ServerException("Channel does not exist");
}

std::string Server::getPassword() const
{
    return _password;
}

void Server::setPassword(std::string pass)
{
    _password = pass;
}

bool Server::isNickUsed(const std::string &nick)
{
    for (auto it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->getNickname() == nick)
            return true;
    }
    return false;
}

const std::string Server::getOperatorPassword() const
{
    return _operatorPassword;
}

bool Server::isUsernameUsed(const std::string &username)
{
    for (auto it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->getUsername() == username)
            return true;
    }
    return false;
}

std::string Server::getOperatorName() const
{
    return _operatorName;
}

Client &Server::getClientByNick(const std::string nick)
{
    for (auto it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->getNickname() == nick)
        {
            return *it;
        }
    }
    throw ServerException("");
}