#include "Server.hpp"

Channel &Server::getChannelByName(const std::string &name)
{
    if (_channelMap.find(name) == _channelMap.end())
        throw ServerException("Channel does not exist");
    return _channelMap[name];
}

std::string Server::getPassword() const
{
    return _password;
}

void Server::setPassword(std::string pass)
{
    _password = pass; // TODO: password validation
}

bool Server::isNickUsed(const std::string &nick) const
{
    auto it = std::find_if(_clients.begin(), _clients.end(),
                           [nick](const Client &c)
                           {
                               return c.getNickname() == nick;
                           });

    if (it == _clients.end())
        return false;
    return true;
}

bool Server::isUsernameUsed(const std::string &username) const
{
    auto it = std::find_if(_clients.begin(), _clients.end(),
                           [username](const Client &c)
                           {
                               return c.getUsername() == username;
                           });

    if (it == _clients.end())
        return false;
    return true;
}
