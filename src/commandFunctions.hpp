#pragma once
#include "User.hpp"
#include <vector>
#include <string>
#include <sstream>

//Commands

void handlePass(User &user, const std::vector<std::string> &args);
void handleNick(User &user, const std::vector<std::string> &args);
void handleUser(User &user, const std::vector<std::string> &args);
void handleOper(User &user, const std::vector<std::string> &args);
void handleMode(User &user, const std::vector<std::string> &args);
void handleQuit(User &user, const std::vector<std::string> &args);
void handleJoin(User &user, const std::vector<std::string> &args);