//
// Created by Home on 14/10/2018.
//

#ifndef RAYTRACING_LOGGER_H
#define RAYTRACING_LOGGER_H

#include <iostream>
using namespace std;

class Logger {

public:
    Logger() = delete;
    ~Logger() = default;

    static void ErrorMessage(string message);
    static void WarningMessage(string message);
    static void InfoMessage(string message);


};


#endif //RAYTRACING_LOGGER_H
