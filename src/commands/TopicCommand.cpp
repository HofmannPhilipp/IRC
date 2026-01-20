#include "TopicCommand.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void TopicCommand::execute(Client &client,
                           Server &server,
                           const IrcMsg &msg)
{
    const std::vector<std::string> &params = msg.get_params();

    if (params.size() < 1)
    {
        server.sendResponse(client, ":" + server.getServerName() + " 461 " + client.getNickname() + " TOPIC :Not enough parameters\r\n");
        return;
    }

    const std::string &channelName = params[0];
    if (server.getChannels().find(channelName) == server.getChannels().end())
    {
        server.sendResponse(client, ":" + server.getServerName() + " 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }

    Channel &channel = server.getChannels()[channelName];
    if (!channel.isMember(client.getNickname()))
    {
        server.sendResponse(client, ":" + server.getServerName() + " 442 " + client.getNickname() + " " + channelName + " :You're not on that channel\r\n");
        return;
    }

    if (params.size() == 1)
    {
        if (channel.getTopic().empty())
        {
            server.sendResponse(client, ":" + server.getServerName() + " 331 " + client.getNickname() + " " + channelName + " :No topic is set\r\n");
        }
        else
        {
            server.sendResponse(client, ":" + server.getServerName() + " 332 " + client.getNickname() + " " + channelName + " :" + channel.getTopic() + "\r\n");
            // std::string setter = client.getNickname(); // Oder wer es wirklich gesetzt hat
            // std::string timestamp = "1705416000";      // Beispiel-Timestamp (oder nutze time(0))

            // std::string reply333 = ":" + server.getServerName() + " 333 " + client.getNickname() + " " + channelName + " " + setter + " " + timestamp + "\r\n";
            // server.sendResponse(client, reply333);
        }
        return;
    }

    if (channel.isTopicProtected() && !channel.isOperator(client))
    {
        server.sendResponse(client, ":" + server.getServerName() + " 482 " + client.getNickname() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }

    std::string newTopic = params[1];

    channel.setTopic(newTopic);
    std::string response = ":" + client.getPrefix() + " TOPIC " + channelName + " :" + newTopic + "\r\n";

    server.broadcastToChannel(client, channel, response);
    server.sendResponse(client, response);
}