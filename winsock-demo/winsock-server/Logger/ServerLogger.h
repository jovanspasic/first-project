#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>

using namespace std;

class ServerLogger {

    private:
        ServerLogger();
        ofstream outStream;
        string logName;
        string logMessages = "";
        // void storeLogMessage(string logMessage);
        // void storeLogMessage();
        string getCurrentDateTime();

    public:
        ServerLogger(const ServerLogger &logger) = delete;
        void operator=(const ServerLogger &logger) = delete;

        static ServerLogger& getInstance();
        void log(string message, string type);
        void storeLogMessage();
        
};