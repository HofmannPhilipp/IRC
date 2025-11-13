#include "commandFunctions.hpp"
#include "User.hpp"

void handlePass(User &user, const std::vector<std::string> &args)
{
    // pruefen ob registriert
    // pruefen ob arg == 2
    // preufen ob arg[1] == passwort von user
    // falls ja, speichern dass pw akzeptiert wurde
}

void handleNick(User &user, const std::vector<std::string> &args)
{
    //checken ob Nick erlaubt (Laenge, bestimmte Zeichen)
    //checken ob Name bereits vergeben ist
    //wenn ok, nickname setten fuer user
}

void handleUser(User &user, const std::vector<std::string> &args)
{
    //USER <username> <hostname> <servername> :<realname>
    //check ich nciht
}

void handleOper(User &user, const std::vector<std::string> &args)
{
    //OPER <username> <password>
    //checken ob 3 in arg
    //checken ob User uebrhaupt exestiert
    //checken ob Operator PW uebereinstimmt
    //User zu Operator setten
    //msg senden
}

void handleMode(User &user, const std::vector<std::string> &args)
{
    //MODE <channel> <modes> [parameters]
    //kein plan
}

void handleQuit(User &user, const std::vector<std::string> &args)
{
    //braodcast to channel
    //remove User from channel
    //disconnect User
}

void handleJoin(User &user, const std::vector<std::string> &args)
{
    //check ob arg groesser als 2 
    //channle name muss mit # anfangen?
    //get Channel class falls nein erstelle neuen Channel als class
    //add user to channel
    //boradcast join

}