#pragma once

#include <ctime>
#include <cstdio>
#include <string>
#include <stdarg.h>
#include "mutex.h"
#include "linebuffer.h"

#include <iostream>
namespace doge
{
template<typename _FileHandler, typename _Mutex>
class Logger
{
private:
	time_t rotate_time_;
	_Mutex lk_;
	std::string name_;
	_FileHandler file_;
	typedef LineBuffer<char, _Mutex> CharLineBuffer;

	time_t calcRotateTime(const int hour, const int minute)
	{
		struct tm tm_time;
		time_t time_now = time(NULL);

	       	localtime_r(&time_now, &tm_time);
		tm_time.tm_hour = hour;
		tm_time.tm_min = minute;
		time_t time_rotate = mktime(&tm_time);

		if(time_rotate < time_now)
			time_rotate += 86400;
		
		return time_rotate;
	};

	const std::string calcFileName()
	{
		char buffer[1024];
		struct tm tm_time;
		time_t time_now = time(NULL);
	       	localtime_r(&time_now, &tm_time);
		snprintf(buffer, 1024, "%s-%d-%02d-%02d", 
				name_.c_str(), 
				tm_time.tm_year + 1900,
				tm_time.tm_mon + 1,
				tm_time.tm_mday);
		return std::string(buffer);
	};
public:
	Logger(const std::string & name, const int hour, const int minute)
		:name_(name)
	{
		rotate_time_ = calcRotateTime(hour, minute);
		file_.Open(calcFileName());
	};

	~Logger()
	{
	};

	CharLineBuffer Info(const char * format, ...)
	{
		if(time(NULL) > rotate_time_)
		{
			rotate_time_ += 86400;
			file_.Open(calcFileName());
		}

		CharLineBuffer buffer(file_.GetPointer(), lk_);
		va_list ap;
		va_start(ap, format);
		buffer.VWrite(format, ap);
		va_end(ap);
		return buffer;
	};

	CharLineBuffer Info()
	{
		if(time(NULL) > rotate_time_)
		{
			rotate_time_ += 86400;
			file_.Open(calcFileName());
		}

		CharLineBuffer buffer(file_.GetPointer(), lk_);
		return buffer;
	};
};
}
