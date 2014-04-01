#ifndef SERIAL_H
#define SERIAL_H
#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

class Serial
{
    private:
        HANDLE hSerial;
        bool connected;
        COMSTAT status;
        DWORD errors;

    public:
        Serial(char *portName);
        ~Serial();
        int ReadData(char *buffer, unsigned int nbChar);
        Serial& ReadDataEnd(char *buffer, unsigned int nbChar);
        bool WriteData(const char *buffer, const unsigned int nbChar);
        bool IsConnected();
        Serial& operator <<(string const& s) {
                char *a=new char [s.length()+1];
                std::strcpy (a, s.c_str());
                WriteData(a, s.length());
            return *this;
        }
};
#endif // SERIAL_H
