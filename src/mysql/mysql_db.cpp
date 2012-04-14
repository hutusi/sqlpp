
#include "sqlpp/mysql/mysql_db.h"
#include "xns/string.h"
__SQLPP_USING_NAMESPACE
__XNS_USING_NAMESPACE

int MysqlDb::execute(const char *sql, size_t len){
	if (!connected()) {return -1;}
	return mysql_real_query(mysql_, sql, len);
}

int MysqlDb::create_db(const char *db_name){
	if (!db_name || strlen(db_name) == 0) {return -1;}
	std::string sql = "create database ";
	sql += db_name; 
	return execute(sql.c_str());
}

int MysqlDb::drop_db(const char *db_name){
	if (!db_name || strlen(db_name) == 0) {return -1;}
	std::string sql = "drop database ";
	sql += db_name; 
	return execute(sql.c_str());
}

int MysqlDb::select_db(const char *db_name){
	if (!mysql_) {return -1;}
	return mysql_select_db(mysql_, db_name);
}
