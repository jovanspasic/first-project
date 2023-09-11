#include "ServerLogger.h"

ServerLogger::ServerLogger() {
    logName = ".\\Logs\\" + getCurrentDateTime() + ".txt";
    outStream.open(logName);
    outStream.close();
}

ServerLogger& ServerLogger::getInstance() {
    static ServerLogger logger;
    return logger;
}

void ServerLogger::log(string message, string type) {
    string logLine = "";
    if(type == "info") {
        logLine += "[INFO] ";
    }
    else if(type == "error") {
        logLine += "[ERROR] ";
    }
    else if(type == "output") {
        logLine += "[OUTPUT] ";
    }
    logLine += message;
    cout << logLine << endl;
    logMessages += logLine + "\n";
    // storeLogMessage(logLine);
}

string ServerLogger::getCurrentDateTime() {
    time_t rawTime;
    struct tm *timeInfo;
    char timeStr[100];

    time(&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(timeStr, 100, "%Y-%m-%d_%H-%M-%S", timeInfo);
    return timeStr;
}

// void ServerLogger::storeLogMessage(string logMessage) {
//     outStream.open(logName, ios::app);
//     outStream << logMessage << endl;
//     outStream.close();
// }

void ServerLogger::storeLogMessage() {
    while(true) {
        this_thread::sleep_for(2000ms);
        if(logMessages != "") {
            outStream.open(logName, ios::app);
            outStream << logMessages;
            outStream.close();
            logMessages = "";
        }
    }
}