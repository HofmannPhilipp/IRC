
#pragma once
#include "Command.hpp"

class ModeCommand : public Command
{
public:
    void execute(Client &client, Server &server, const IrcMsg &msg) override;
};