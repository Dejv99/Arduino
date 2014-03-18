#include <iostream>
#include <Serial.h>
using namespace std;

int main(int argc, char **argv) {
	cout<<"Welcome to the serial test app!\n\n"<<endl;

	Serial* SP = new Serial("\\\\\.\\COM3");    // adjust as needed

	if (SP->IsConnected())
		cout<<"We're connected"<<endl;

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	//printf("%s\n",incomingData);
	int dataLength = 256;
	int readResult = 0;

	while(SP->IsConnected())
	{
	    char a[1]="";
		for(int i = 4; i<8;i++) {
            a[0]=48+i;
            SP->WriteData(a, 1);
		}
		Sleep(1000);
	}
	return 0;
}
