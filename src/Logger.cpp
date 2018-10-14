//
// Created by Home on 14/10/2018.
//

#include "../header/Logger.h"


void Logger::ErrorMessage(string message){
    cout << "[ERROR] " << message << endl;
}

void Logger::InfoMessage(string message){
    cout << "[INFO] " << message << endl;
}