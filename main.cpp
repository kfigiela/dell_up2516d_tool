#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <unistd.h>

#include <UP_API.h>

#define ERROR_TAG "*** ERROR ***\n"

#define monitorIndex 0

using namespace std;

void toggleCustom(bool state) {
	int res;

    if(state) {
        // custom mode (set to black and white colors)
        res = SetUniformityCompensation(0);
        if (res != MONITOR_SUCCESS) cout << ERROR_TAG;
        cout << "SetUniformityCompensation(0|Off) / return code=" << dec << (int)res << endl;

        res = SetColorPreset(0x00000080);
        if (res != MONITOR_SUCCESS) cout << ERROR_TAG;
        cout << "SetColorPreset(0x00000080|CUSTOM) / return code=" << dec << (int)res << endl;

    } else {
        res = SetUniformityCompensation(2);
        if (res != MONITOR_SUCCESS) cout << ERROR_TAG;
        cout << "SetUniformityCompensation(2|On) / return code=" << dec << (int)res << endl;

    	res = SetColorPreset(0x00000001);
    	if (res != MONITOR_SUCCESS) cout << ERROR_TAG;
    	cout << "SetColorPreset(0x00000001|STANDARD) / return code=" << dec << (int)res << endl;
    }
}

int main(int argc, char *argv[])
{
    if(argc != 3) {
        cout << "Invalid arguments" << endl;
        return 1;
    }

	int res;
	uint8_t b8Val;
    uint32_t b32Val;
	res = ConnectMonitor(monitorIndex);
	if (res == MONITOR_SUCCESS) {
		cout << "ConnectMonitor(" << dec << monitorIndex<< ")=" << (int)res << endl;
    }
	else
	{
		cout << "ConnectMonitor(" << dec << monitorIndex << ") Fails, Result=" << (int)res << endl;
		return 1;
	}

    switch(argv[1][0]) {
        case 'a': {
        	res = GetBrightness(&b8Val);
        	if ((int)res != MONITOR_SUCCESS) cout << ERROR_TAG;
        	cout << "GetBrightness=" << dec << (int)b8Val << " / return code=" << (int)res << endl;

            if ((int)res == MONITOR_SUCCESS) {
                int newBrightness = b8Val + atoi(argv[2]);
                newBrightness = max(min(newBrightness, 100), 0);
                res = SetBrightness(newBrightness);
            	if (res != MONITOR_SUCCESS) cout << ERROR_TAG;
            	cout << "SetBrightness(" << dec << ") / return code=" << dec << (int)res << endl;
            }
            break;
        }
        case 's': {
            int newBrightness = atoi(argv[2]);
            newBrightness = max(min(newBrightness, 100), 0);
            res = SetBrightness(newBrightness);
        	if (res != MONITOR_SUCCESS) cout << ERROR_TAG;
        	cout << "SetBrightness(" << dec << ") / return code=" << dec << (int)res << endl;
            break;
        }
        case 'b': {
            switch(argv[2][0]) {
                case '0': { // standard mode
                    toggleCustom(false);
                    break;
                }
                case '1': { // custom mode (set to black and white colors)
                    toggleCustom(true);
                    break;
                }
                case 't': { // custom mode (set to black and white colors)
                	res = GetColorPreset(&b32Val);

                    if(res == MONITOR_SUCCESS) {
                        if(b32Val == 0x00000080) {
                            toggleCustom(false);
                        } else {
                            toggleCustom(true);
                        }
                    }
                    break;
                }
            }
            break;
        }
    }

	res = DisconnectMonitor();
	if (res != MONITOR_SUCCESS) cout << ERROR_TAG;
	cout << "DisconnectMonitor() / return code=" << dec << (int)res << endl;

	return 0;
}

