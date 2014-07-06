#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

class LogMessage{
public:
	LogMessage();
	~LogMessage();
	void log(std::string message);
	void sync(void);
	void setFileName(std::string name);
	void operator()(std::string message);
private:
	std::ofstream file;
	std::string fileName_;
};

#endif