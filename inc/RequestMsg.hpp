
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <array>

#define IRC_CAP "CAP"
#define IRC_PASS "PASS"
#define IRC_NICK "NICK"
#define IRC_USER "USER"
#define IRC_OPER "OPER"
#define IRC_MODE "MODE"
#define IRC_QUIT "QUIT"
#define IRC_JOIN "JOIN"
#define IRC_TOPIC "TOPIC"
#define IRC_KICK "KICK"
#define IRC_PRIVMSG "PRIVMSG"
#define IRC_NOTICE "NOTICE"

static const std::array<std::string, 12> IRC_COMMANDS = {
    IRC_CAP,
    IRC_PASS,
    IRC_NICK,
    IRC_USER,
    IRC_OPER,
    IRC_MODE,
    IRC_QUIT,
    IRC_JOIN,
    IRC_TOPIC,
    IRC_KICK,
    IRC_PRIVMSG,
    IRC_NOTICE};

class RequestMsg
{
private:
    std::string _prefix_param;
    std::string _cmd;
    std::vector<std::string> _params;
    std::string _org_msg;

public:
    class RequestMsgException : public std::exception
    {
    private:
        std::string _message;

    public:
        RequestMsgException(const std::string &msg) : _message(msg) {}
        const char *what() const noexcept override { return _message.c_str(); }
    };

    class InvalidCommand : public RequestMsgException
    {
    public:
        InvalidCommand() : RequestMsgException("Invalid IRC Command") {}
    };

    class TooManyParams : public RequestMsgException
    {
    public:
        TooManyParams() : RequestMsgException("Too many parameters in IRC message") {}
    };

    RequestMsg();
    RequestMsg(std::string msg);
    RequestMsg(const RequestMsg &other);
    RequestMsg &operator=(const RequestMsg &other);
    ~RequestMsg();

    std::string get_cmd(void);
};