
#pragma once 

#include "defs.h"

#include <string>

__SQLPP_BEGIN_NAMESPACE

class Table
{
public:	
	virtual int query(const char* sql, size_t len) = 0;
	virtual int query(const char* sql) = 0;

	virtual bool get_field(const char* field, std::string& out, int rowno) = 0;
	virtual bool get_field(const char* field, std::string& out) {return get_field(field, out, 1);}

protected:
	std::string name_;
};

__SQLPP_END_NAMESPACE
