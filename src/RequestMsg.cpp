
#include "RequestMsg.hpp"

RequestMsg::RequestMsg() : _cmd(""), _org_msg("") {}

bool is_valid_cmd(const std::string &cmd)
{
    for (auto it = IRC_COMMANDS.begin(); it < IRC_COMMANDS.end(); it++)
    {
        if (*it == cmd)
            return true;
    }
    return false;
}

RequestMsg::RequestMsg(std::string msg) : _org_msg(msg)
{
    std::stringstream ss(msg);
    std::string token;
    ss >> token;

    if (msg.size() < 2 || msg.substr(msg.size() - 2) != "\r\n")
        throw RequestMsgException("Message not terminated properly with \\r\\n");

    if (token[0] == ':')
    {
        _prefix_param = token.substr(1);
        ss >> token;
    }

    if (!is_valid_cmd(token))
        throw InvalidCommand();

    _cmd = token;
    int middle_params = 0;
    while (ss >> token)
    {
        if (token[0] == ':')
        {
            // trailing argument
            std::string remainder;
            std::getline(ss, remainder);

            _params.push_back(token.substr(1) + remainder);
            break;
        }

        _params.push_back(token);
        middle_params++;

        if (middle_params > 14) // RFC: max 14 middle params + 1 trailing
            throw TooManyParams();
    }
}

RequestMsg::RequestMsg(const RequestMsg &other) : _prefix_param(other._prefix_param), _cmd(other._cmd), _params(other._params), _org_msg(other._org_msg) {}

RequestMsg &RequestMsg::operator=(const RequestMsg &other)
{
    if (this == &other)
        return;
    _prefix_param = other._prefix_param;
    _cmd = other._cmd;
    _params = other._params;
    _org_msg = other._org_msg;
}

RequestMsg::~RequestMsg() {};

std::string RequestMsg::get_cmd(void)
{
    return _cmd;
}