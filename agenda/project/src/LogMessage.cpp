#include "LogMessage.h"

using namespace std;

LogMessage::LogMessage(){
}
LogMessage::~LogMessage(){
	if(file.is_open())
		file.close();
}
void LogMessage::log(std::string message){
	time_t nowTime = time(NULL);
	time(&nowTime);
	tm *t;
	t = localtime(&nowTime);
	file << right;
	file << setw(4) << t->tm_year + 1900 << "-" << setw(2) << t->tm_mon + 1 << "-" << setw(2) << t->tm_mday << "/"
		<< setw(2) << t->tm_hour << ":" << setw(2) << t->tm_min << ":" << setw(2) << t->tm_sec << " : " << message << endl;
}

void LogMessage::setFileName(std::string name){
	fileName_ = name;
	if(file.is_open())
		file.close();
	file.open(fileName_,ios::app);
	file << "/----------------------------------------------------------------/" << endl;
}
void LogMessage::operator()(std::string message){
	this->log(message);
}
void LogMessage::sync(){
	file.close();
	file.open(fileName_, ios::app);
}