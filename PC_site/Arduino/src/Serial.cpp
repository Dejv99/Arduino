#include "Serial.h"
Serial::Serial(char *portName)
{
    this->connected = false;

    this->hSerial = CreateFile(portName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    if(this->hSerial==INVALID_HANDLE_VALUE)
    {
        if(GetLastError()==ERROR_FILE_NOT_FOUND){

            printf("ERROR: Handle was not attached. Reason: %s not available.\n", portName);

        }
        else
        {
            printf("ERROR!!!");
        }
    }
    else
    {
        DCB dcbSerialParams = {0};

        if (!GetCommState(this->hSerial, &dcbSerialParams))
        {
            printf("failed to get current serial parameters!");
        }
        else
        {
            dcbSerialParams.BaudRate=CBR_9600;
            dcbSerialParams.ByteSize=8;
            dcbSerialParams.StopBits=ONESTOPBIT;
            dcbSerialParams.Parity=NOPARITY;

             if(!SetCommState(hSerial, &dcbSerialParams))
             {
                printf("ALERT: Could not set Serial Port parameters");
             }
             else
             {
                 this->connected = true;
                 Sleep(ARDUINO_WAIT_TIME);
             }
        }
    }

}

Serial::~Serial()
{
    if(this->connected)
    {
        this->connected = false;
        CloseHandle(this->hSerial);
    }
}

int Serial::ReadData(char *buffer, unsigned int nbChar)
{
    DWORD bytesRead;
    unsigned int toRead;

    ClearCommError(this->hSerial, &this->errors, &this->status);

    if(this->status.cbInQue>0)
    {
        if(this->status.cbInQue>nbChar)
        {
            toRead = nbChar;
        }
        else
        {
            toRead = this->status.cbInQue;
        }

        if(ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL) && bytesRead != 0)
        {
            return bytesRead;
        }

    }

    return -1;

}

Serial& Serial::ReadDataEnd(char *buffer, const unsigned int nbChar) {
    DWORD bytesRead;
    unsigned int toRead = 1;

    ClearCommError(this->hSerial, &this->errors, &this->status);

    if(this->status.cbInQue>0)
    {
        for(unsigned int i = 0;i<nbChar;i++) {
            ReadFile(this->hSerial, &buffer[i], 1, &bytesRead, NULL);
            //cout << buffer[i] << "\t" << &buffer[i] << "\t" << (int) buffer[i] << endl;
            char a = buffer[i];
            if(a==0x0) {
                break;
            }
        }

    }

    return *this;
}


bool Serial::WriteData(const char *buffer, unsigned int nbChar)
{
    DWORD bytesSend;

    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &bytesSend, 0))
    {
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    }
    else
        return true;
}

bool Serial::IsConnected()
{
    return this->connected;
}
