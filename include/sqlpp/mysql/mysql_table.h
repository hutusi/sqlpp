
#pragma once

#include "../sql_db.h"
#include "mysql_db.h"
#include <mysql.h>
#include <string>

__SQLPP_BEGIN_NAMESPACE

class MysqlTable{
public:
	MysqlTable(MysqlDb* db, const char* name);
	virtual ~MysqlTable();

	virtual bool execute(const char *sql, size_t len);
	virtual int query(const char *sql, size_t len);
	virtual bool get_field(const char* field, std::string& out, int rowno = 1);

private:
	MysqlDb* db_;
	MYSQL_RES *query_result_; 
	std::string name_;
};

__SQLPP_END_NAMESPACE
