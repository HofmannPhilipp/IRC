#include "CapCommand.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void CapCommand::execute(Client &client,
                         Server &server,
                         const IrcMsg &msg)
{
    if (client.getIsRegistered())
    {
        std::cout << "Warning: Registered client sent CAP command. Ignoring." << std::endl;
        return;
    }

    if (msg.get_params().size() < 1)
    {

        // TODO: CAP needs params
        return;
    }

    if (msg.get_params()[0] == "LS")
    {
        server.sendResponse(client, "CAP * LS\r\n");
        return;
    }

    if (msg.get_params()[0] == "END")
    {
        // if (!client.hasNick())
        // {
        //     sendResponse(client, "451 * :You have not registered\r\n");
        //     throw ServerException("451 * :You have not registered\r\n");
        // }
        // if (!client.hasUser())
        // {
        //     sendResponse(client, "451 * :You have not registered\r\n");
        //     throw ServerException("451 * :You have not registered\r\n");
        // }
        // if (!client.hasPass())
        // {
        //     sendResponse(client, "451 * :You have not registered, Password required\r\n");
        //     throw ServerException("451 * :You have not registered, Password required\r\n");
        // }
        if (client.canRegister())
            server.sendWelcomeMessage(client);

        return;
    }
}