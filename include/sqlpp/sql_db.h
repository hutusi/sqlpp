
#pragma once

#include "defs.h"

__SQLPP_BEGIN_NAMESPACE

class Database{
public:
	virtual int execute(const char* sql, size_t len) = 0;
	virtual int execute(const char* sql) = 0;
};

__SQLPP_END_NAMESPACE
