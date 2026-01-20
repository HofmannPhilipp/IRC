
#pragma once
#include "Command.hpp"

class TopicCommand : public Command
{
public:
    void execute(Client &client, Server &server, const IrcMsg &msg) override;
};