/*
The MIT License (MIT)

Copyright (c) 2015 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once
#include <cstdio>
#include <string>
#include <stdexcept>
#include "utils.h"

namespace doge
{
namespace details
{
class FileHandler : noncopyable
{
private:
	FILE * fp_;
	std::string name_;
public:
	FileHandler() : fp_(NULL)
	{
	};

	~FileHandler()
	{
		Close();
	};

	void Open(std::string name)
	{
		Close();
		fp_ = fopen(name.c_str(), "ab");
		if(!fp_)
			throw std::runtime_error("open " + name + "failed.");
		name_ = name;
	};

	void Close()
	{
		if(fp_)
		{
			fclose(fp_);
			name_.clear();
			fp_ = NULL;
		}
	};

	FILE * GetPointer() const
	{
		return fp_;
	}

	const std::string & FileName() const
	{
		return name_;
	};
};
}
}
