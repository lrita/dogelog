#pragma once
#include <cstdio>
#include <stdarg.h>
#include "mutex.h"

namespace doge
{
using namespace details;

template<typename CHAR, typename _Mutex, int MAX=65535>
class LineBuffer
{
private:
	CHAR data_[MAX];
	mutable CHAR * buffer_;
	CHAR * bufferBeg_;
	CHAR * bufferEnd_;
	FILE * fp_;
	_Mutex & mutex_;
public:
	LineBuffer(FILE * fp, _Mutex & mutex) 
		: buffer_(data_), 
		bufferBeg_(data_), 
		bufferEnd_(data_+MAX), 
		fp_(fp),
		mutex_(mutex)
	{
		mutex_.Lock();
	};

	~LineBuffer()
	{
		Flush(true);
		mutex_.unLock();
	};

	void Flush(bool leof) const
	{
		if(leof) Put('\n');
		if(buffer_ != bufferBeg_)
		{
			size_t result = fwrite(bufferBeg_, 1, static_cast<size_t>(buffer_ - bufferBeg_), fp_);
			if(result < static_cast<size_t>(buffer_ - bufferBeg_))
			{
				//TODO?
			}
			fflush(fp_);
			buffer_ = bufferBeg_;
		}
	};

	void Put(CHAR ch) const
	{
		if(buffer_ >= bufferEnd_)
			Flush(false);
		*buffer_++ = ch;
	};

	const LineBuffer & operator<<(const std::string & str) const
	{
		return operator<<(str.c_str());
	};

	const LineBuffer & operator<<(const CHAR * str) const
	{
		CHAR ch;
		while((ch = *str++))
		{
			if(buffer_ >= bufferEnd_)
				Flush(false);
			*buffer_++ = ch;
		}
		return *this;
	};

	const LineBuffer & Write(const char * format, ...) const
	{
		Flush(false);
		va_list ap;
		va_start(ap, format);
		int result = vsnprintf(buffer_, MAX, format, ap);
		va_end(ap);
		if(result <= MAX-1)
		{
			buffer_ += result;
		}
		else
		{
			buffer_ += MAX-1;
		}
		return *this;
	};

	const LineBuffer & VWrite(const char * format, va_list ap) const
	{
		Flush(false);
		int result = vsnprintf(buffer_, MAX, format, ap);
		if(result <= MAX-1)
		{
			buffer_ += result;
		}
		else
		{
			buffer_ += MAX-1;
		}
		return *this;
	};
};
}
