#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string.h>

#define MAXPACKETSIZE = 1024-12 = 1~1012;

// application reads from the specified serial port and reports the collected data
int main()
{
	printf("Welcome to the serial test app!\n\n");

	Serial* SP = new Serial("COM5");    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected\n\n");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	//printf("%s\n",incomingData);
	int dataLength = 8;
	int readResult = 0;

	while(1)
	{
		
		readResult = SP->ReadData(incomingData, dataLength);
//		printf("%s", incomingData);

		incomingData[readResult] = 0;

		if (incomingData[0] == 'a') {
			printf("%c : ", incomingData[0]);
			printf("STOP Message\n\n");
			
			while (1) {
				readResult = SP->ReadData(incomingData, dataLength);
				//printf("%c : ", incomingData[1]);
				if (incomingData[0] == 'b') {
					printf("%c : ", incomingData[0]);
					printf("RESTART Message\n\n");
					Sleep(1000);
					break;
				}
				Sleep(1000);
			}
		}
		
		unsigned int packet[1036];
		unsigned int data[1036];
		int sendlen = 8;
		packet[1] = 0; //type
		packet[2] = 0; //Sadd
		packet[3] = 4; //Dadd
		memcpy(packet + 4, data, sendlen); //payload

		packet[0] = 4 + sendlen; //length

		SP->WriteData("103A.", 6);
		SP->WriteData("\n", 2);

		Sleep(1000);
	}
	return 0;
}
