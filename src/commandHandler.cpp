#include <string>
#include <sstream>
#include <vector>

// /NICK Chris xyz
void commandHandler(std::string msg) //+ welcher user/client
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
        //send.msg
    }
    else if (arg[0] == "PASS")
    {
        // handlepass(Client &client, const std::vector<std::string> &args);
    }
    else if (arg[0] == "NICK")
    {
        //handlenick
    }
    else if (arg[0] == "USER")
    {

    }
    else if (arg[0] == "OPER")
    {

    }
    else if (arg[0] == "MODE")
    {

    }
    else if (arg[0] == "NICK")
    {

    }
    else if (arg[0] == "QUIT")
    {

    }
    else if (arg[0] == "JOIN")
    {

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