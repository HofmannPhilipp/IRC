#include "commandFunctions.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "commandUtils.hpp"

bool checkNickname(const std::string &nick);

void handlePass(Server &server, Client &client, const std::vector<std::string> &args)
{
    if (client.get_registered())
    {
        client.sendMessage("462 :You may not reregister");
        return;
    }
    if (args.size() < 2)
    {
        client.sendMessage("461 PASS :Not enough parameters");
        return;
    }
    std::string pass = args[1];

    if (pass != server.getPassword())
    {
      client.sendMessage("464 :Password incorrect");
      return;
    }
    client.setPasswordCorrect(true);
}

void handleNick(Server &server, Client &client, const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        client.sendMessage("431 :No nickname given");
        return;
    }
    if (!checkNickname(args[1]))
    {
        client.sendMessage("432 :Erroneous nickname");
        return;
    }
    
    std::string newNickname = args[1];

    if (!server.isNickAvailable(newNickname))
    {
        client.sendMessage("433 :Nickname is already in use");
        return;        
    }

    client.setNickname(newNickname);

    //Nachricht an alle Clients ausser beim ersten setzen dbeim einloggen:
    //:NICK <oldNick> <newNick>
}

void handleUser(Client &client, const std::vector<std::string> &args)
{
    // USER <username> <hostname> <servername> :<realname>
    //USER chris 0 * :Christopher Klein
    //-> hostna,e und serverbname ignoriert da eh schon bekannt
    
    // chekcen ob client bereits regestriert
    //chekcen ob genug paramenter
    //daten speichern (username etc)
    //client regestrien setRegistration(true)
}

void handleOper(Client &client, const std::vector<std::string> &args)
{
    // OPER <username> <password>
    // checken ob 3 in arg
    // checken ob Client uebrhaupt exestiert
    // checken ob Operator PW uebereinstimmt
    // Client zu Operator setten
    // msg senden
}

void handleMode(Client &client, const std::vector<std::string> &args)
{
    // MODE <channel> <modes> [parameters]
    // kein plan
}

void handleQuit(Client &client, const std::vector<std::string> &args)
{
    // braodcast to channel
    // remove Client from channel
    // disconnect Client
}

void handleJoin(Client &client, const std::vector<std::string> &args)
{
    // check ob arg groesser als 2
    // channle name muss mit # anfangen?
    // get Channel class falls nein erstelle neuen Channel als class
    // add client to channel
    // boradcast join
}

void handleTopic(Client &client, const std::vector<std::string> &args)
{
    // arg muss groeser gleich 2 sein
    //  arg[1] = channel name
    // get channel object if not available return
    // if arg == 2
    //-> braodcast channel name or no channel topic if nothing set yet
    // if arg == 3 topic setzen (in channel struct) ((setter und getter func benutzen))
}

void handleKick(Client &client, const std::vector<std::string> &args)
{
    // arg muss groesser gleich 3 sein
    // arg[1] channel name
    // arg[2] targetUser
    // get Channel if not return
    // check if client (which want to kick) in channel isMember()
    // check if Client is operaator in channel
    // getUser (target)
    // chekc if target is in channel
    // Grund zusammensetzen mit arg 3, etc falls mehr args
    // Target aus Channel entfernen
}

void privMsg(Client &client, const std::vector<std::string> &args)
{
    // arg muss groesser gleich 3 sein
    // arg[1] channel name
    // arg[2] targetUser
    // get Channel if not return
    // check if client (which want to kick) in channel isMember()
    // check if Client is operaator in channel
    // getUser (target)
    // chekc if target is in channel
    // Grund zusammensetzen mit arg 3, etc falls mehr args
    // Target aus Channel entfernen
}