#include <iostream>
#include <Serial.h>
#include <conio.h>

using namespace std;

int main(int argc, char **argv) {
	cout<<"Welcome to the serial test app!\n\n"<<endl;

	Serial SP("\\\\\.\\COM3");

	if (SP.IsConnected())
		cout<<"We're connected"<<endl;

	char incomingData[256] = "";
	char i[256] = "";
	int dataLength = 256;

    std::string b("5");

	while(SP.IsConnected())
	{
	    std::string a;
	    a=getch();
	    b=getch();
	    cout << "Budu posilat cislo "<<a<<endl;
	    cout << "Budu posilat cislo "<<b<<endl;

        SP<<a<<b;
        Sleep(100);

        SP.ReadDataEnd(incomingData, 256).ReadDataEnd(i, 256);
        cout << incomingData;
        cout << i;
	}
	return 0;
}
