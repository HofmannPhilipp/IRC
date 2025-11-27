#include "commandFunctions.hpp"

// /NICK Chris
void commandHandler(Client &client, const IrcMsg &msg) //+ welcher client/client
{
    const std::string cmd = msg.get_cmd();
    if (cmd == IRC_CAP)
    {
        // macht Philipp
    }
    else if (cmd == IRC_PASS)
    {
        handlePass(client, msg);
    }
    else if (cmd == IRC_NICK)
    {
        handleNick(client, msg);
    }
    else if (cmd == IRC_USER)
    {
        handleClient(client, msg);
    }
    else if (cmd == IRC_OPER)
    {
        handleOper(client, msg);
    }
    else if (cmd == IRC_MODE)
    {
        handleMode(client, msg);
    }
    else if (cmd == IRC_QUIT)
    {
        handleQuit(client, msg);
    }
    else if (cmd == IRC_JOIN)
    {
        handleJoin(client, msg);
    }
    else if (cmd == IRC_TOPIC)
    {
        handleTopic(client, msg);
    }
    else if (cmd == IRC_KICK)
    {
        handleKick(client, msg);
    }
    else if (cmd == IRC_PRIVMSG)
    {
        privMsg(client, msg);
    }
    else if (cmd == IRC_NOTICE)
    {
    }
    else
    {
        // philipp sagen, dass falscher cmd
    }
}