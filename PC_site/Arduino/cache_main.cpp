#include <iostream>
#include <Serial.h>
using namespace std;

int main(int argc, char **argv) {
	printf("Welcome to the serial test app!\n\n");

	Serial* SP = new Serial("\\\\\.\\COM3");    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	//printf("%s\n",incomingData);
	int dataLength = 256;
	int readResult = 0;

	while(SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData,dataLength);
		printf("Bytes read: (-1 means no data available) %i\n",readResult);

		std::string test(incomingData);

		printf("%s",incomingData);
		test = "";
        SP->WriteData("0", 1);
		Sleep(500);
	}
	return 0;
}
