#include "PrivMsgCommand.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void PrivMsgCommand::execute(Client &client,
                             Server &server,
                             const IrcMsg &msg)
{
    // Command: PRIVMSG
    // Parameters: <receiver>{,<receiver>} <text to be sent>
    // receiver should be nick name of client
    std::vector<std::string> privMsgParams = msg.get_params();

    // 411 ERR_NORECIPIENT
    if (privMsgParams.empty())
    {
        return;
    }

    // 412 ERR_NOTEXTTOSEND
    if (privMsgParams.size() == 1)
    {
        std::string reply = ":" + server.getServerName() + " 412 " + client.getNickname() + " :No text to send\r\n";
        server.sendResponse(client, reply);
        return;
    }

    std::string text = privMsgParams.back();
    std::set<std::string> targets;
    std::string segment;

    // splitting the channels from params
    std::stringstream ss(msg.get_params()[0]);
    while (std::getline(ss, segment, ','))
    {
        if (!segment.empty())
            targets.insert(segment);
    }
    for (const std::string &currTarget : targets)
    {
        if ((currTarget[0] == '#' || currTarget[0] == '&'))
        {
            // 403 ERR_NOSUCHCHANNEL
            std::map<std::string, Channel>::iterator it = server.getChannels().find(currTarget);
            if (it == server.getChannels().end())
            {
                std::string reply = ":" + server.getServerName() + " 403 " + client.getNickname() + " " + currTarget + " :No such channel\r\n";
                server.sendResponse(client, reply);
                continue;
            }
            // 404 ERR_CANNOTSENDTOCHAN client has to be member
            if (!it->second.isMember(client.getNickname()))
            {
                std::string reply = ":" + server.getServerName() + " 404 " + client.getNickname() + " " + currTarget + " :Cannot send to channel\r\n";
                server.sendResponse(client, reply);
                continue;
            }
            std::string reply = ":" + client.getPrefix() + " PRIVMSG " + currTarget + " " + text + "\r\n";
            server.broadcastToChannel(client, it->second, reply);
            continue;
        }
        // 401 ERR_NOSUCHNICK
        if (!server.isNickUsed(currTarget))
        {
            std::string reply = ":" + server.getServerName() + " 401 " + client.getNickname() + " " + currTarget + " :No such nick/channel\r\n";
            server.sendResponse(client, reply);
            continue;
        }

        try
        {
            const Client &receiver = server.getClientByNick(currTarget);
            std::string reply = ":" + client.getPrefix() + " PRIVMSG " + currTarget + " " + text + "\r\n";
            server.sendResponse(receiver, reply);
            continue;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            std::string reply = ":" + server.getServerName() + " 401 " + client.getNickname() + " " + currTarget + " :No such nick/channel\r\n";
            server.sendResponse(client, reply);
            continue;
        }
    }
}