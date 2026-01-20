#include "QuitCommand.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void QuitCommand::execute(Client &client,
                          Server &server,
                          const IrcMsg &msg)
{
    std::string reason = msg.get_params().empty() ? client.getNickname() : msg.get_params()[0];

    std::string quitNotify = ":" + client.getPrefix() + " QUIT :Quit: " + reason + "\r\n";

    // TODO: REMOVE FROM OPERATOR LIST
    for (Channel *chan : client.getChannels())
    {
        server.broadcastToChannel(client, *chan, quitNotify);
        chan->removeMember(client);
    }

    std::string errDoc = "ERROR :Closing Link: " + client.getHostname() + " (Quit: " + reason + ")\r\n";
    server.sendResponse(client, errDoc);

    server.disconnectClient(client);
}