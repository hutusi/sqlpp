
#pragma once 

#include "defs.h"
#include "sql_db.h"

#include <string>
#include <vector>

__SQLPP_BEGIN_NAMESPACE

class QueryResultSet{
public:
	int index_of_fields(const char* field_name);
	int num_of_rows();
	int num_of_columns();

private:
	std::vector<std::string> fields_;
	std::vector<std::vector<std::string>> values_;
};

class Query{
private:
	virtual int execute();
private:
	QueryResultSet* set_;
	std::string sql_;
};

class Table{
public:	
	virtual int query(const char* sql, size_t len) = 0;
	virtual int query(const char* sql) = 0;

	virtual bool get_field(const char* field, std::string& out, int rowno) = 0;
	virtual bool get_field(const char* field, std::string& out) {return get_field(field, out, 1);}
		
protected:
	std::string name_;

	Database* db_adapter_;
	Query* query_;
};

__SQLPP_END_NAMESPACE
