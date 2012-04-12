
#include "sqlpp/mysql/mysql_table.h"
#include "xns/string.h"
__SQLPP_USING_NAMESPACE
__XNS_USING_NAMESPACE

MysqlTable::MysqlTable(MysqlDb* db, const char* name) : db_(db), name_(name), query_result_(0){
}

MysqlTable::~MysqlTable(){
	mysql_free_result(query_result_);
}

bool MysqlTable::execute(const char *sql, size_t len){
	if (!(db_ && db_->connected())) {return false;}
	return(0 == mysql_real_query(db_->mysql(), sql, len));
}

int MysqlTable::query(const char *sql, size_t len){
	if (!execute(sql, len)) {return -1;}

	mysql_free_result(query_result_);
	query_result_ = mysql_store_result(db_->mysql());
	if (!query_result_) {
		return -1;
	}

	return mysql_num_rows(query_result_);
}

bool MysqlTable::get_field(const char* field, std::string& out, int rowno){
	out.clear();
	if (rowno < 1) {return false;}
	if (!query_result_) {return false;}

	int index = -1;
	size_t num_fields = mysql_num_fields(query_result_);
	MYSQL_FIELD *fields = mysql_fetch_fields(query_result_);
	for(size_t i = 0; i < num_fields; ++i){
		if (String::casecmp(fields[i].name, strlen(fields[i].name), field, strlen(field)) == 0) { 
			index = i; 
			break;
		}			
	}
	if (index == -1) {return false;}

	mysql_data_seek(query_result_, rowno - 1);
	MYSQL_ROW row = mysql_fetch_row(query_result_);
	if (!row) {return false;}
	out =  row[index];
	return true;
}
