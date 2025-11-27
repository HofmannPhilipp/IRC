#include "commandFunctions.hpp"
#include "Client.hpp"

void handlePass(Client &client, const IrcMsg &msg)
{
    if (client.get_registered())
    {
        client.sendMessage("462 :You may not reregister");
        return;
    }
    if (msg.get_params().size() < 2)
    {
        client.sendMessage("461 PASS :Not enough parameters");
        return;
    }
    std::string pass = msg.get_params()[0];

    // if (pass != server.getPass())
    //{
    //   client.sendMessage("464 :Password incorrect");
    //   return;
    // }

    // noch nicht registriert, da Nick noch nicht gesetzt
}

void handleNick(Client &client, const IrcMsg &msg)
{
    if (args.size() < 2)
    {
        client.sendMessage("431 :No nickname given");
        return;
    }
    // if (!checkNickname(args[1]))
    // {
    //     client.sendMessage("432 :Erroneous nickname");
    //     return;
    // }
    // checken ob Name bereits vergeben ist bei allen Usern in Server
    // wenn ok, nickname setten fuer client
}

void handleUser(Client &client, const IrcMsg &msg)
{
    // USER <username> <hostname> <servername> :<realname>
    // check ich nciht
}

void handleOper(Client &client, const IrcMsg &msg)
{
    // OPER <username> <password>
    // checken ob 3 in arg
    // checken ob Client uebrhaupt exestiert
    // checken ob Operator PW uebereinstimmt
    // Client zu Operator setten
    // msg senden
}

void handleMode(Client &client, const IrcMsg &msg)
{
    // MODE <channel> <modes> [parameters]
    // kein plan
}

void handleQuit(Client &client, const IrcMsg &msg)
{
    // braodcast to channel
    // remove Client from channel
    // disconnect Client
}

void handleJoin(Client &client, const IrcMsg &msg)
{
    // check ob arg groesser als 2
    // channle name muss mit # anfangen?
    // get Channel class falls nein erstelle neuen Channel als class
    // add client to channel
    // boradcast join
}

void handleTopic(Client &client, const IrcMsg &msg)
{
    // arg muss groeser gleich 2 sein
    //  arg[1] = channel name
    // get channel object if not available return
    // if arg == 2
    //-> braodcast channel name or no channel topic if nothing set yet
    // if arg == 3 topic setzen (in channel struct) ((setter und getter func benutzen))
}

void handleKick(Client &client, const IrcMsg &msg)
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

void privMsg(Client &client, const IrcMsg &msg)
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