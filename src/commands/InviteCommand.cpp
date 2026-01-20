#include "InviteCommand.hpp"
#include "Server.hpp"
#include "Channel.hpp"

// Command: INVITE
// Parameters : <nickname> <channel>
void InviteCommand::execute(Client &client,
                            Server &server,
                            const IrcMsg &msg)
{
    std::vector<std::string> inviteParams = msg.get_params();

    // if (inviteParams.size() != 2)
    // {
    //     return;
    // }
    std::cout << msg.get_msg() << std::endl;
    const std::string &nickname = inviteParams[0];
    const std::string &channelName = inviteParams[1];

    // 401 ERR_NOSUCHNICK
    if (!server.isNickUsed(nickname))
    {
        std::string reply = ":" + server.getServerName() + " 401 " + client.getNickname() + " " + nickname + " :No such nick/Name\r\n";
        server.sendResponse(client, reply);
        return;
    }

    Client &invitedClient = server.getClientByNick(nickname);

    // 403 ERR_NOSUCHCHANNEL
    std::map<std::string, Channel>::iterator it = server.getChannels().find(channelName);
    if (it == server.getChannels().end())
    {
        std::string reply = ":" + server.getServerName() + " 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n";
        server.sendResponse(client, reply);
        return;
    }

    Channel &channel = it->second;

    // 442 ERR_NOTONCHANNEL
    if (!channel.isMember(client))
    {
        std::string reply = ":" + server.getServerName() + " 442 " + client.getNickname() + " " + channelName + " :You're not on that channel\r\n";
        server.sendResponse(client, reply);
        return;
    }

    // 443 ERR_USERONCHANNEL
    // TODO: maybe check if invitedCLient is operator
    if (channel.isMember(invitedClient))
    {
        std::string reply = ":" + server.getServerName() + " 443 " + client.getNickname() + " " + nickname + " " + channelName + " :is already on channel\r\n";
        server.sendResponse(client, reply);
        return;
    }

    // 482 ERR_CHANOPRIVSNEEDED
    if (!channel.isOperator(client))
    {
        std::string reply = ":" + server.getServerName() + " 443 " + client.getNickname() + " " + channelName + " :You're not channel operator\r\n";
        server.sendResponse(client, reply);
        return;
    }
    channel.invite(&invitedClient);
    // 341 RPL_INVITING
    std::string reply = ":" + server.getServerName() + " 341 " + client.getNickname() + " " + nickname + " " + channelName + "\r\n";
    server.sendResponse(client, reply);

    reply = ":" + client.getPrefix() + " INVITE " + nickname + " :" + channelName + "\r\n";
    server.sendResponse(invitedClient, reply);
}