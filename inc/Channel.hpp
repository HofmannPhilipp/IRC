#include <string>
#include <vector>
#include "Client.hpp"

class Channel
{
private:
    std::string _name;
    std::string _topic;
    std::vector<Client> _memberList;
    std::vector<Client> _operatorList;

    // verscheidene Modes....
    bool _inviteOnly;
    bool _topicProtected;
    std::string _password;
    int _userlimit;

public:
    Channel();
    Channel(const std::string &nickname, bool is_op, int fd);
    Channel(const Channel &other);
    Channel &operator=(const Channel &other);
    ~Channel();
};