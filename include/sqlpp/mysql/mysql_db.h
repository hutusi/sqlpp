
#pragma once

#include "../sql_db.h"
#include <windows.h>
#include <mysql.h>

__SQLPP_BEGIN_NAMESPACE

class MysqlDb{
public:
	MysqlDb() : mysql_(0), connected_(false){
		mysql_ = mysql_init(mysql_);
	}

	bool connect(const char* host, const char* user, const char* passwd, const char* db = 0,
		          unsigned int port = 0, const char *unix_socket = NULL, unsigned long client_flag = 0){
		connected_ = (0 != mysql_real_connect(mysql_, host, user, passwd, db, port, unix_socket, client_flag));
		return connected_;
	}
	void close(){
		mysql_close(mysql_);
		connected_ = false;
	}

	inline bool connected(){ return connected_; }
	inline MYSQL* mysql() { return mysql_; }

	virtual int execute(const char *sql, size_t len);
	virtual inline int execute(const char *sql) { return execute(sql, strlen(sql)); }

	int create_db(const char *db_name);
	int drop_db(const char *db_name);
	int select_db(const char *db_name);

private:
	MYSQL* mysql_;
	bool connected_;
};

__SQLPP_END_NAMESPACE
