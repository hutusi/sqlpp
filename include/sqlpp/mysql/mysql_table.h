
#pragma once

#include "../sql_db.h"
#include "mysql_db.h"
#include <mysql.h>
#include <string>

__SQLPP_BEGIN_NAMESPACE
__MYSQL_BEGIN_NAMESPACE

class Table : public __MYSQL_NAMESPACE::Table{
public:
	Table(MysqlDb* db, const char* name);
	virtual ~Table();

	virtual int query(const char *sql, size_t len);
	virtual bool get_field(const char* field, std::string& out, int rowno);	

	static bool empty();
	static void clear();

private:
	MysqlDb* db_;
	//MYSQL_RES *query_result_; 
	std::string name_;
};

__MYSQL_END_NAMESPACE
__SQLPP_END_NAMESPACE
