#include "ModeCommand.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void ModeCommand::execute(Client &client,
                          Server &server,
                          const IrcMsg &msg)
{
    // MODE #channel <modestring> [modeparams...] bswp: MODE #channelName +it
    // msg.get_cmd()      == "MODE"
    // msg.get_params()   == { "#test", "+i" }

    // 1. genug Parameter?

    const std::vector<std::string> &params = msg.get_params();

    if (params.size() < 2)
    {
        // sendResponse(client, ":" + _serverName + " 461 MODE :Not enough parameters\r\n");
        return;
    }

    // 2. Channel existiert?

    const std::string &channelName = params[0];

    if (server.getChannels().find(channelName) == server.getChannels().end())
    {
        // sendResponse(client, ":" + _serverName + " 403 " + channelName + " :No such channel\r\n");
        return; // ERR_NOSUCHCHANNEL
    }

    Channel &channel = server.getChannels()[channelName];

    // 3. Client ist Operator?

    if (!channel.isOperator(client))
    {
        // sendResponse(client, ":" + _serverName + " 482 " + channel.getName() + " :You're not channel operator\r\n");
        return; // ERR_CHANOPRIVSNEEDED
    }

    // 4. Modestring parsen (+ / -)

    const std::string modeStr = params[1];
    bool adding = true;
    size_t paramIndex = 2;

    // TO DO: WENN MINUS KEIN PARAMS > 2?

    for (size_t i = 0; i < modeStr.size(); ++i)
    {
        char c = modeStr[i];

        if (c == '+')
        {
            adding = true;
            continue;
        }
        if (c == '-')
        {
            adding = false;
            continue;
        }
        switch (c)
        {
        case 'i':
            channel.setInviteOnly(adding);
            break;

        case 't':
            channel.setTopicProtected(adding);
            break;

        case 'k':
            if (adding)
            {
                if (paramIndex >= params.size())
                    break;
                if (!channel.isPasswordSet())
                {
                    channel.setPassword(params[paramIndex]);
                }
                else
                    // 467
                    paramIndex++;
            }
            else
                channel.clearPassword();
            break;

        case 'l':
            if (adding)
            {
                if (paramIndex >= params.size())
                    break;
                int limit = std::atoi(params[paramIndex++].c_str());
                if (limit < 0)
                    limit = 0;
                if (limit > 100)
                    limit = 100;
                channel.setLimit(limit);
            }
            else
                channel.clearUserLimit();
            break;
        default:
            // sendResponse(client, ":" + _serverName + " 472 " + c + " :is unknown mode char to me\r\n");
            break;
        }
    }
    // MODE ANEDERUNGEN BROADCASTEN: IRC KONFORM: :nick!user@host MODE #chan +kl geheim 10
    std::string response = ":" + client.getPrefix() + " MODE " + channelName;
    for (size_t i = 1; i < params.size(); ++i)
        response += " " + params[i];

    response += "\r\n";
    server.broadcastToChannel(client, channel, response);
    server.sendResponse(client, response);
}