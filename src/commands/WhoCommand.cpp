#include "WhoCommand.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void WhoCommand::execute(Client &client,
                         Server &server,
                         const IrcMsg &msg)
{
    if (msg.get_params().empty())
        return;

    std::string target = msg.get_params()[0];

    if (target[0] == '#' || target[0] == '&')
    {
        auto it = server.getChannels().find(target);

        if (it == server.getChannels().end())
        {
            server.sendResponse(client, ":" + server.getServerName() + " 315 " + client.getNickname() + " " + target + " :End of WHO list\r\n");
            return;
        }
        Channel &chan = it->second;
        for (Client *member : chan.getMembers())
        {
            // 352 RPL_WHOREPLY
            std::string reply = ":" + server.getServerName() + " 352 " + client.getNickname() + " " +
                                target + " " + member->getUsername() + " " +
                                member->getHostname() + " " + server.getServerName() + " " +
                                member->getNickname() + " H :0 " + member->getRealname() + "\r\n";
            server.sendResponse(client, reply);
        }
    }

    server.sendResponse(client, ":" + server.getServerName() + " 315 " + client.getNickname() + " " + target + " :End of WHO list\r\n");
}