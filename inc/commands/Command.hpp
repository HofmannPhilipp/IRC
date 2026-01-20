#pragma once
#include "Client.hpp"
#include "IrcMsg.hpp"

class Server;

class Command
{
public:
    virtual ~Command() {}
    virtual void execute(Client &client, Server &server, const IrcMsg &msg) = 0;
};