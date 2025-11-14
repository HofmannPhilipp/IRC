#include "commandFunctions.hpp"

// /NICK Chris
void commandHandler(Client &client, std::string msg) //+ welcher client/client
{
    std::stringstream ss(msg);
    std::vector<std::string> arg;
    std::string word;
    while (ss >> word)
    {
        arg.push_back(word); //["NICK", "Chris", "xyz"]
    }

    if (arg[0] == "CAP LS")
    {
        // macht Philipp
    }
    else if (arg[0] == "PASS")
    {
        handlePass(client, arg);
    }
    else if (arg[0] == "NICK")
    {
        handleNick(client, arg);
    }
    else if (arg[0] == "USER")
    {
        handleClient(client, arg);
    }
    else if (arg[0] == "OPER")
    {
        handleOper(client, arg);
    }
    else if (arg[0] == "MODE")
    {
        handleMode(client, arg);
    }
    else if (arg[0] == "QUIT")
    {
        handleQuit(client, arg);
    }
    else if (arg[0] == "JOIN")
    {
        handleJoin(client, arg);
    }
    else if (arg[0] == "TOPIC")
    {
        handleTopic(client, arg);
    }
    else if (arg[0] == "KICK")
    {
        handleKick(client, arg);
    }
    else if (arg[0] == "PRIVMSG")
    {
        privMsg(client, arg);
    }
    else if (arg[0] == "NOTICE")
    {
    }
    else
    {
        // philipp sagen, dass falscher cmd
    }
}