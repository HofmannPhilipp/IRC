#include "commandFunctions.hpp"

// /NICK Chris
void commandHandler(User &user, std::string msg) //+ welcher user/client
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
        //macht Philipp
    }
    else if (arg[0] == "PASS")
    {
        handlePass(user, arg);
    }
    else if (arg[0] == "NICK")
    {
        handleNick(user, arg);
    }
    else if (arg[0] == "USER")
    {
        handleUser(user, arg);          
    }
    else if (arg[0] == "OPER")
    {
        handleOper(user, arg);
    }
    else if (arg[0] == "MODE")
    {
        handleMode(user, arg);
    }
    else if (arg[0] == "QUIT")
    {
        handleQuit(user, arg);
    }
    else if (arg[0] == "JOIN")
    {
        handleJoin(user, arg);
    }
    else if (arg[0] == "TOPIC")
    {

    }
    else if (arg[0] == "KICK")
    {

    }
    else if (arg[0] == "PRIVMSG")
    {

    }
    else if (arg[0] == "NOTICE")
    {

    }
    else
    {
        //philipp sagen, dass falscher cmd 
    }
}