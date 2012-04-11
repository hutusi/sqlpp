
#pragma once 

#include "defs.h"

#include <string>

__SQLPP_BEGIN_NAMESPACE

class Table
{
public:
	virtual bool execute(const char* sql, size_t len) = 0;
	virtual int query(const char* sql, size_t len) = 0;
	virtual std::string get_field() = 0;
protected:
	std::string name_;
};

__SQLPP_END_NAMESPACE
