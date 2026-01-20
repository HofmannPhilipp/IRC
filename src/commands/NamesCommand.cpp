#include "NamesCommand.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void NamesCommand::execute(Client &client,
                           Server &server,
                           const IrcMsg &msg)
{
    const std::vector<std::string> &params = msg.get_params();
    if (params.empty())
        return;

    const std::string &channelName = params[0];

    if (server.getChannels().find(channelName) == server.getChannels().end())
    {
        // Optional: ERR_NOSUCHCHANNEL
        // sendResponse(client, ":" + _serverName + " 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }

    Channel &channel = server.getChannels()[channelName];

    std::string names;
    for (auto it = channel.getMembers().begin(); it != channel.getMembers().end(); ++it)
    {
        const Client *member = *it;

        if (channel.isOperator(*member))
            names += "@";
        // else if (channel.hasVoice(*member))
        //     names += "+";

        names += member->getNickname();
        names += " ";
    }

    // 3. 353 RPL_NAMREPLY senden
    std::string reply =
        ":" + server.getServerName() +
        " 353 " + client.getNickname() +
        " = " + channelName +
        " :" + names + "\r\n";

    server.sendResponse(client, reply);

    // 4. 366 RPL_ENDOFNAMES senden
    std::string end =
        ":" + server.getServerName() +
        " 366 " + client.getNickname() +
        " " + channelName +
        " :End of /NAMES list.\r\n";

    server.sendResponse(client, end);
}