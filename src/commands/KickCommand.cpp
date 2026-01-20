#include "KickCommand.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void KickCommand::execute(Client &client,
                          Server &server,
                          const IrcMsg &msg)
{
    // KICK <channel> <user> [comment]
    if (msg.get_params().size() < 2)
    {
        server.sendResponse(client,
                            ":" + server.getServerName() + " 461 " + client.getNickname() +
                                " KICK :Not enough parameters\r\n");
        return;
    }

    const std::string channelName = msg.get_params()[0];
    const std::string targetNick = msg.get_params()[1];

    std::string comment = client.getNickname();

    if (msg.get_params().size() >= 3)
    {
        comment.clear();
        for (size_t i = 2; i < msg.get_params().size(); i++)
        {
            comment += msg.get_params()[i];
            if (i + 1 < msg.get_params().size())
                comment += " ";
        }
    }

    if (server.getChannels().find(channelName) == server.getChannels().end())
    {
        server.sendResponse(client,
                            ":" + server.getServerName() + " 403 " + client.getNickname() +
                                " " + channelName + " :No such channel\r\n");
        return;
    }

    Channel &channel = server.getChannels()[channelName];

    if (!channel.isMember(client))
    {
        server.sendResponse(client,
                            ":" + server.getServerName() + " 442 " + client.getNickname() +
                                " " + channelName + " :You're not on that channel\r\n");
        return;
    }

    if (!channel.isOperator(client))
    {
        server.sendResponse(client,
                            ":" + server.getServerName() + " 482 " + client.getNickname() +
                                " " + channelName + " :You're not channel operator\r\n");
        return;
    }

    Client *target = NULL;

    // TODO: warum & ???????????
    try
    {
        target = &server.getClientByNick(targetNick);
    }
    catch (const Server::ServerException &)
    {
        // User existiert nicht ODER nicht gefunden → RFC 441
        server.sendResponse(client,
                            ":" + server.getServerName() + " 441 " + client.getNickname() +
                                " " + targetNick + " " + channelName +
                                " :They aren't on that channel\r\n");
        return;
    }

    // User existiert, aber ist nicht im Channel
    if (!channel.isMember(*target))
    {
        server.sendResponse(client,
                            ":" + server.getServerName() + " 441 " + client.getNickname() +
                                " " + targetNick + " " + channelName +
                                " :They aren't on that channel\r\n");
        return;
    }

    // was wenn keine comment
    std::string kickMsg = ":" + client.getPrefix() +
                          " KICK " + channelName + " " + targetNick +
                          " :" + comment + "\r\n";

    server.broadcastToChannel(client, channel, kickMsg);
    server.sendResponse(client, kickMsg);

    channel.removeMember(*target);

    if (channel.getMembers().empty())
        server.getChannels().erase(channelName);
}