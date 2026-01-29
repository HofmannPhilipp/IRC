#include "Server.hpp"
#include "Channel.hpp"
#include "ServerState.hpp"

// Command: INVITE
// Parameters : <nickname> <channel>
void handleInvite(Client &client, Server &server, const IrcMsg &msg)
{
    std::vector<std::string> params = msg.get_params();

    if (params.size() < 2)
    {
        server.sendMsg(client, ":" + server.getServerName() + " 461 " + client.getNickname() + " INVITE :Not enough parameters\r\n");
        return;
    }

    ServerState &state = server.getServerState();
    const std::string &nickname = params[0];
    const std::string &channelName = params[1];

    Client *invitedClient = state.getClientByNick(nickname);
    // 401 ERR_NOSUCHNICK
    if (!invitedClient)
    {
        server.sendMsg(client, ":" + server.getServerName() + " 401 " + client.getNickname() + " " + nickname + " :No such nick/Name\r\n");
        return;
    }

    // 403 ERR_NOSUCHCHANNEL
    Channel *channel = state.getChannel(channelName);
    if (!channel)
    {
        server.sendMsg(client, ":" + server.getServerName() + " 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }
    // 442 ERR_NOTONCHANNEL
    if (!channel->isMember(client))
    {
        server.sendMsg(client, ":" + server.getServerName() + " 442 " + client.getNickname() + " " + channelName + " :You're not on that channel\r\n");
        return;
    }

    // 443 ERR_USERONCHANNEL
    if (channel->isMember(*invitedClient) || channel->isOperator(*invitedClient))
    {
        server.sendMsg(client, ":" + server.getServerName() + " 443 " + client.getNickname() + " " + nickname + " " + channelName + " :is already on channel\r\n");
        return;
    }

    // 482 ERR_CHANOPRIVSNEEDED
    if (channel->isInviteOnly() && !channel->isOperator(client))
    {
        server.sendMsg(client, ":" + server.getServerName() + " 482 " + client.getNickname() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }
    channel->invite(invitedClient);
    // 341 RPL_INVITING
    server.sendMsg(client, ":" + server.getServerName() + " 341 " + client.getNickname() + " " + nickname + " " + channelName + "\r\n");

    server.sendMsg(*invitedClient, ":" + client.getPrefix() + " INVITE " + nickname + " :" + channelName + "\r\n");
}