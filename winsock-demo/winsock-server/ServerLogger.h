#pragma once
#include <iostream>

using namespace std;

class ServerLogger
{
    private:
        ServerLogger();

    public:
        ServerLogger(ServerLogger &logger) = delete;
        void operator=(const ServerLogger &) = delete;

        static ServerLogger& getInstance();
        void logTheMessage(string message);
};