all:
	c++ -o dell_tool -I/usr/local/include -L/usr/local/lib -lDellMonitorSdkLib main.cpp

clean:
	rm dell_tool

