
#pragma once

#include "../sql_db.h"
#include <windows.h>
#include <mysql.h>

__SQLPP_BEGIN_NAMESPACE

class MysqlDb{
public:
	MysqlDb() : mysql_(0){
		mysql_ = mysql_init(mysql_);
	}

	bool connect(const char* host, const char* user, const char* passwd, const char* db){
		return mysql_real_connect(mysql_, host, user, passwd, db, 0, NULL, 0);
	}

	void close(){
		mysql_close(mysql_);
	}

	inline bool connected(){ return connected_; }
	inline MYSQL* mysql() { return mysql_; }

private:
	MYSQL* mysql_;
	bool connected_;
};

__SQLPP_END_NAMESPACE
