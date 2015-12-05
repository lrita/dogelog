#pragma once
#include "logger.h"
#include "filehandler.h"
namespace doge
{
typedef Logger<details::FileHandler, details::Mutex> DailyRotateLogger; 
}
