
#include "Server.hpp"

void Server::handleRequest(Client &client, const IrcMsg &msg)
{

    const std::string cmd = msg.get_cmd();

    using CommandFunction = void (Server::*)(Client &, const IrcMsg &);

    static const std::map<std::string, CommandFunction> functions{

        {"CAP", &Server::handleCap},
        {"PASS", &Server::handlePass},
        {"NICK", &Server::handleNick},
        {"USER", &Server::handleUser},

        // {"OPER", &Server::handleOper},
        {"MODE", &Server::handleMode},
        // {"QUIT", &Server::handleQuit},

        // {"JOIN", &Server::handleJoin},
        // {"TOPIC", &Server::handleTopic},
        // {"KICK", &Server::handleKick},

        // {"PRIVMSG", &Server::privMsg},
        // {"NOTICE", &Server::handleNotice}
        {"PING", &Server::handlePing}};

    auto it = functions.find(cmd);
    if (it != functions.end())
    {
        CommandFunction handler = it->second;
        (this->*handler)(client, msg);
    }
    else
        throw ServerException("Invalid Cmd");
}

void Server::checkRegistration(Client &client)
{
    // Falls der Client schon registriert ist oder noch nicht alles hat, tu nichts
    if (client.getIsRegistered() || !client.hasNick() || !client.hasUser())
        return;

    // Falls ein Passwort nötig ist, aber noch nicht kam, auch Abbruch
    if (_hasPassword && !client.hasPass())
        return;

    // JETZT ist der Client registriert!
    client.setIsRegistered(true);

    // Sende die obligatorischen Willkommens-Nachrichten

    sendResponse(client, _prefix + "001 " + client.getNickname() + " :Welcome to the IRC Network " + client.getPrefix() + "\r\n");
    sendResponse(client, _prefix + "002 " + client.getNickname() + " :Your host is " + _serverName + ", running version 1.0\r\n");
    // ... 003 und 004 sind optional, aber 001 ist Pflicht für Irssi!
}

void Server::handleCap(Client &client, const IrcMsg &msg)
{
    if (client.getIsRegistered())
    {
        std::cout << "Warning: Registered client sent CAP command. Ignoring." << std::endl;
        return;
    }

    if (msg.get_params().size() < 1)
    {

        // TODO: CAP needs params
        return;
    }

    if (msg.get_params()[0] == "LS")
    {
        sendResponse(client, "CAP * LS\r\n");
        return;
    }

    if (msg.get_params()[0] == "END")
    {
        if (!client.hasNick())
        {
            sendResponse(client, "451 * :You have not registered\r\n");
            throw ServerException("451 * :You have not registered\r\n");
        }
        if (!client.hasUser())
        {
            sendResponse(client, "451 * :You have not registered\r\n");
            throw ServerException("451 * :You have not registered\r\n");
        }
        if (!client.hasPass())
        {
            sendResponse(client, "451 * :You have not registered, Password required\r\n");
            throw ServerException("451 * :You have not registered, Password required\r\n");
        }
        if (client.canRegister())
            sendWelcomeMessage(client);

        return;
    }
}

void Server::handlePass(Client &client, const IrcMsg &msg)
{
    if (client.getIsRegistered())
    {
        sendResponse(client, ":" + _serverName + " 462 " + client.getNickname() + " :You may not reregister\r\n");
        return;
    }
    if (msg.get_params().size() < 1)
    {
        sendResponse(client, "461 PASS :Not enough parameters\r\n");
        return;
    }
    std::string pass = msg.get_params()[0];

    if (pass != getPassword())
    {
        sendResponse(client, _serverPrefix + "464 * :Password incorrect\r\n");
        sendResponse(client, "ERROR :Closing Link: [Access denied by password]\r\n");
        throw ServerException("Auth failed");
        return;
    }
    client.setHasPass(true);
    // if (client.canRegister())
    //     sendWelcomeMessage(client);
}

// void Server::handleNick(Client &client, const IrcMsg &msg)
// {
//     if (msg.get_params().size() < 1)
//     {
//         sendResponse(client, "431 :No nickname given\r\n");
//         throw ServerException("431 :No nickname given");
//     }
//     std::string newNickname = msg.get_params()[0];
//     if (isNickUsed(newNickname))
//     {
//         sendResponse(client, ":" + _serverName + " 433 * " + newNickname + " :Nickname is already in use\r\n");
//         throw ServerException("433 * " + newNickname + " :Nickname is already in use");
//     }
//     try
//     {
//         client.setNickname(newNickname);
//         if (client.getIsRegistered())
//         {
//             for (auto c : client.getChannels())
//             {
//                 broadcastToChannel(client, c, ":" + client.getPrefix() + " NICK :" + newNickname); // TODO: check if correct
//             }
//         }
//         client.setHasNick(true);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//         sendResponse(client, "432 :Erroneous nickname\r\n");
//         throw Server::ServerException("432 :Erroneous nickname");
//     }

//     // Nachricht an alle Clients ausser beim ersten setzen dbeim einloggen:
//     //: NICK <oldNick> <newNick>
// }

void Server::handleNick(Client &client, const IrcMsg &msg)
{
    if (msg.get_params().empty())
    {
        // Format: :<servername> 431 <current_nick> :No nickname given
        std::string reply = ":" + _serverName + " 431 " + client.getNickname() + " :No nickname given\r\n";
        sendResponse(client, reply);
        return;
    }

    std::string newNickname = msg.get_params()[0];

    if (isNickUsed(newNickname))
    {
        // Format: :<servername> 433 <current_nick> <target_nick> :Nickname is already in use

        std::string currentNick = client.hasNick() ? client.getNickname() : "*";
        std::string reply = ":" + _serverName + " 433 " + currentNick + " " + newNickname + " :Nickname is already in use\r\n";

        sendResponse(client, reply);
        return;
    }

    try
    {
        std::string oldPrefix = client.getPrefix();
        std::string oldNick = client.getNickname();

        client.setNickname(newNickname);
        client.setHasNick(true);

        if (client.getIsRegistered())
        {
            std::string notify = ":" + oldPrefix + " NICK :" + newNickname + "\r\n";
            // An den Client selbst senden
            sendResponse(client, notify);
            for (auto chan : client.getChannels())
            {
                broadcastToChannel(client, chan, notify);
            }
        }
    }
    catch (const std::exception &e)
    {
        // 432: Erroneous nickname
        std::string reply = ":" + _serverName + " 432 * " + newNickname + " :Erroneous nickname\r\n";
        sendResponse(client, reply);
    }
}

void Server::handleUser(Client &client, const IrcMsg &msg)
{
    // USER <username> <hostname> <servername> :<realname>
    // USER chris 0 * :Christopher Klein
    //-> hostname und serverbname ignoriert da eh schon bekannt
    std::vector<std::string> params = msg.get_params();
    if (params.size() < 4)
    {
        sendResponse(client, "432 :Erroneous nickname\r\n");
        throw Server::ServerException("432 :Erroneous nickname");
    }

    // if (client.hasUser())
    // {
    //     sendResponse(client, "462 :You may not reregister\r\n");
    //     return;
    // }

    std::cout << "username: " << params[1] << " realname: " << params[3] << std::endl;
    client.setUsername(params[1]); // TODO: Check for valid Username and real name
    client.setRealname(params[3]);
    client.setHasUser(true);
}

void Server::handleMode(Client &client, const IrcMsg &msg)
{
    std::cout << client << std::endl;
    std::cout << msg << std::endl;
}

void Server::handlePing(Client &client, const IrcMsg &msg)
{
    if (msg.get_params().empty())
    {
        sendResponse(client, "PONG :" + _serverName + "\r\n");
        return;
    }

    std::string pingParam = msg.get_params()[0];
    sendResponse(client, "PONG :" + pingParam + "\r\n");
}