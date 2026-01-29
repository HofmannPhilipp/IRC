#include "Server.hpp"
#include "Channel.hpp"

void handleUser(Client &client, Server &server, const IrcMsg &msg)
{
    // USER <username> <hostname> <servername> :<realname>
    // USER chris 0 * :Christopher Klein
    //-> hostname und serverbname ignoriert da eh schon bekannt

    std::string nick = client.getNickname().empty() ? "*" : client.getNickname();
    if (msg.get_params().size() < 4)
    {
        // ERR_NEEDMOREPARAMS (461)
        server.sendMsg(client, ":" + server.getServerName() + " 461 " + nick + " USER :Not enough parameters\r\n");
        return;
    }

    if (client.hasUser())
    {
        // ERR_ALREADYREGISTRED (462)
        server.sendMsg(client, ":" + server.getServerName() + " 462 " + nick + " :Unauthorized command (already registered)\r\n");
        return;
    }

    std::string username = msg.get_params()[0];
    if (username.empty())
        return;
    if (username.find_first_of(" @!") != std::string::npos)
    {
        std::cout << "[Server] Rejected USER command: Username '" << username << "' contains invalid characters." << std::endl;
        return;
    }
    if (username.length() > 9)
        username = username.substr(0, 9);

    client.setUsername(username);
    client.setRealname(msg.get_params()[3]);
    client.setHasUser(true);
    if (client.canRegister())
        server.sendWelcomeMessage(client);
}