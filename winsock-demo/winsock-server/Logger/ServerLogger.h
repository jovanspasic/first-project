#pragma once
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class ServerLogger {

    private:
        ServerLogger();
        ofstream outStream;
        string logName;
        void storeLogMessage(string logMessage);
        string getCurrentDateTime();

    public:
        ServerLogger(const ServerLogger &logger) = delete;
        void operator=(const ServerLogger &logger) = delete;

        static ServerLogger& getInstance();
        void log(string message, string type);
        
};