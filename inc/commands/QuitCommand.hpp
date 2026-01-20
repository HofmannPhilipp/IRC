
#pragma once
#include "Command.hpp"

class QuitCommand : public Command
{
public:
    void execute(Client &client, Server &server, const IrcMsg &msg) override;
};