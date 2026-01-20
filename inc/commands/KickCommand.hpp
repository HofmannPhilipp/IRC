
#pragma once
#include "Command.hpp"

class KickCommand : public Command
{
public:
    void execute(Client &client, Server &server, const IrcMsg &msg) override;
};