#include "ServerLogger.h"

ServerLogger::ServerLogger() {
    
}

ServerLogger& ServerLogger::getInstance() {
    static ServerLogger logger;
    return logger;
}

void ServerLogger::logTheMessage(string message) {
    cout << "Server log: " << message << endl;
}