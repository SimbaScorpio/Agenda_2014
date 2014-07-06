#include "Date.h"

using namespace std;

Date::Date()
: year_(2000), month_(1), day_(1), hour_(0), minute_(0) {}

Date::Date(int y, int m, int d, int h, int mi)
: year_(y), month_(m), day_(d), hour_(h), minute_(mi) {}

int Date::getYear() const {
	return year_;
}
void Date::setYear(int year) {
	year_ = year;
}
int Date::getMonth() const {
	return month_;
}
void Date::setMonth(int month) {
	month_ = month;
}
int Date::getDay() const {
	return day_;
}
void Date::setDay(int day) {
	day_ = day;
}
int Date::getHour() const {
	return hour_;
}
void Date::setHour(int hour) {
	hour_ = hour;
}
int Date::getMinute() const {
	return minute_;
}
void Date::setMinute(int minute) {
	minute_ = minute;
}

/* static function */
bool Date::isValid(Date date) {
        if (date.getYear() < 1000 || date.getYear() > 9999) return false;
	if (date.getMonth() < 1 || date.getMonth() > 12) return false;
	if (date.getDay() < 1) return false;
	if (date.getHour() < 0 || date.getHour() > 23) return false;
	if (date.getMinute() < 0 || date.getMinute() > 59) return false;
	int dayNum[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (date.getMonth() != 2) {
		return date.getDay() <= dayNum[date.getMonth() - 1] ? true : false;
	} else {
		if (date.getYear() % 400 == 0 || date.getYear() % 4 == 0 && date.getYear() % 100 != 0) {
			return date.getDay() <= dayNum[1] + 1 ? true: false;
		}
		return date.getDay() <= dayNum[1] ? true : false;
	}
	return false;
}

//  auxilary function
int transfer(int& count, std::string dateString) {
	std::string temp = "";
	int date = 0;
	for (int i = count + 1; i <= dateString.length(); i++) {
		if (dateString[i] <= '9' && dateString[i] >= '0') {
			temp += dateString[i];
		}
		else {
			stringstream a;
			a << temp;
			a >> date;
			count = i;
			break;
		}
	}
	return date;
}

Date Date::stringToDate(std::string dateString) {
	int year, mon, day, hour, min;
	int count = -1;
	year = transfer(count, dateString);
	mon = transfer(count, dateString);
	day = transfer(count, dateString);
	hour = transfer(count, dateString);
	min = transfer(count, dateString);
 
	Date out(year, mon, day, hour, min);
	return out;
}

std::string Date::dateToString(Date date) {
	std::string out = "";
	std::string y[5];
	stringstream a;
	a << date.getYear();
	a >> y[0];
	stringstream b;
	b << date.getMonth();
	b >> y[1];
	stringstream c;
	c << date.getDay();
	c >> y[2];
	stringstream d;
	d << date.getHour();
	d >> y[3];
	stringstream e;
	e << date.getMinute();
	e >> y[4];
	//output formate "aaaa-bb-cc/dd:ee"
	out += y[0];
	for(int j = 1; j < 5; j++) {
		if (j == 1 || j == 2) out += "-";
		else if (j == 3) out += "/";
		else if (j == 4) out += ":";
		if (y[j].length() < 2) {
			out += "0" + y[j];
		} else {
			out += y[j];
		}
	}
	return out;
}

/* operators */
Date& Date::operator=(const Date& date) {
	year_ = date.getYear();
	month_ = date.getMonth();
	day_ = date.getDay();
	hour_ = date.getHour();
	minute_ = date.getMinute();
	return *this;
}

bool Date::operator==(const Date& date) const {
	if (year_ != date.getYear() ||
	    month_ != date.getMonth() ||
	    day_ != date.getDay() ||
	    hour_ != date.getHour() ||
		minute_ != date.getMinute()) {
		return false;
	}
	return true;
}

bool Date::operator>(const Date& date) const {
	if (year_ > date.getYear()) {
		return true;
	}
	else if (year_ == date.getYear() &&
		     month_ > date.getMonth()) {
		return true;
	}
	else if (year_ == date.getYear() && 
		     month_ == date.getMonth() &&
		     day_ > date.getDay()) {
		return true;
	}
	else if(year_ == date.getYear() && 
		    month_ == date.getMonth() &&
		    day_ == date.getDay() &&
			hour_ > date.getHour()){
		return true;
	}
	else if(year_ == date.getYear() &&
		    month_ == date.getMonth() &&
	    	day_ == date.getDay() && 
	    	hour_ == date.getHour() && 
			minute_ > date.getMinute()) {
		return true;
	}
	return false;
}

bool Date::operator<(const Date& date) const {
	if (!(*this == date) && !(*this > date)) return true;
	return false;
}

bool Date::operator>=(const Date& date) const {
	if (!(*this < date)) return true;
	return false;
}

bool Date::operator<=(const Date& date) const {
	if (!(*this > date)) return true;
	return false;
}
