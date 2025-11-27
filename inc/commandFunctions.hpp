#pragma once
#include "Client.hpp"
#include <vector>
#include <string>
#include <sstream>

// Commands

void handlePass(Client &client, const IrcMsg &msg);
void handleNick(Client &client, const IrcMsg &msg);
void handleClient(Client &client, const IrcMsg &msg);
void handleOper(Client &client, const IrcMsg &msg);
void handleMode(Client &client, const IrcMsg &msg);
void handleQuit(Client &client, const IrcMsg &msg);
void handleJoin(Client &client, const IrcMsg &msg);
void handleTopic(Client &client, const IrcMsg &msg);
void handleKick(Client &client, const IrcMsg &msg);
void privMsg(Client &client, const IrcMsg &msg);
