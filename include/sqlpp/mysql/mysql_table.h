
#pragma once

#include "../sql_db.h"
#include "mysql_db.h"
#include <mysql.h>
#include <string>

__SQLPP_BEGIN_NAMESPACE

class MysqlTable{
public:
	MysqlTable(MysqlDb* db, const char* name) : db_(db), name_(name), query_result_(0){
	}

	virtual ~MysqlTable(){
		mysql_free_result(query_result_);
	}

	virtual bool execute(const char *sql, size_t len){
		if (!(db_ && db_->connected())) {return false;}
		return(0 == mysql_real_query(db_->mysql(), sql, len));
	}

	virtual int query(const char *sql, size_t len){
		if (!execute(sql, len)) {return -1;}

		mysql_free_result(query_result_);
		query_result_ = mysql_store_result(db_->mysql());
		if (!query_result_) {
			return -1;
		}

		return mysql_num_rows(query_result_) - 1;
	}

	virtual bool get_field(const char* field, std::string& out, int row = 1){
		if (row < 1) {return false;}

		int index = 0;
		size_t num_fields = mysql_num_fields(query_result_);
		MYSQL_FIELD *fields = mysql_fetch_fields(query_result_);
		for(size_t i = 0; i < num_fields; ++i){
			if (strcmp(fields[i].name, field) == 0) { index = i; }
			return false;
		}

		MYSQL_ROW_OFFSET off = mysql_row_tell(query_result_);
		mysql_row_seek(query_result_, row - off);

		MYSQL_ROW row = mysql_fetch_row(query_result_);
		out =  row[index];
		return true;
	}

private:
	MysqlDb* db_;
	MYSQL_RES *query_result_; 
	std::string name_;
};

__SQLPP_END_NAMESPACE
