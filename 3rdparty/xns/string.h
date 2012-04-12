
// Copyright (c) 2012, John Hu 

#pragma once

#include "xns/defs.h"

#include <string>
#include <vector>

#include <regex>

__XNS_BEGIN_NAMESPACE


inline std::string operator*(const std::string& str, size_t times){
	std::string s;
	for (size_t i=0; i<times; ++i){
		s += str;
	}
	return s;
}

inline bool is_digital(char ch){
	return (ch >= '0' && ch <= '9');
}

inline bool is_uppercase(char ch){
	return (ch >= 'A' && ch <= 'Z');
}

inline bool is_lowercase(char ch){
	return (ch >= 'a' && ch <= 'z');
}

inline bool is_alphabetic(char ch){
	return is_uppercase(ch)||is_lowercase(ch);
}

inline int char_to_int(char ch){
	return ch - '0';
}

class String {
public:
	static inline std::vector<std::string>& split(const std::string& str, char splitter, std::vector<std::string>& out){
		return split(str.c_str(), str.length(), splitter, out);
	}

	static inline std::vector<std::string>& split(const char* str, size_t len, char splitter, std::vector<std::string>& out){
		char sp[] = {splitter,'\0'};
		return split(str, len, sp, 1, out);
	}

	static inline std::vector<std::string>& split(const std::string& str, const std::string& splitter, std::vector<std::string>& out){
		return split(str.c_str(), str.length(), splitter.c_str(), splitter.length(), out);
	}

	static std::vector<std::string>& split(const char* str, size_t len, const char* splitter, size_t sp_len, std::vector<std::string>& out){
		out.clear();
		if (len == 0 || sp_len == 0) return out;

		const char* pos = str;
		size_t s_len = 0;

		for (size_t i = 0; i < len; ++i){
			if ((len - i >= sp_len) && (strncmp(pos+s_len, splitter, sp_len) == 0)) {
				if (s_len > 0) out.push_back(std::string(pos, s_len));
				pos = str+i+sp_len;
				i += sp_len -1;
				s_len = 0;
			} else {
				++s_len;
			}
		}

		if (s_len > 0) out.push_back(std::string(pos, s_len));
		return out;
	}


	static inline std::string& trim(std::string& str){
		return ltrim(rtrim(str));
	}
	static inline std::string& trim(std::string& str, const std::string& trim_chars){
		return ltrim(rtrim(str, trim_chars.c_str(), trim_chars.length()), trim_chars.c_str(), trim_chars.length());
	}
	static inline std::string& trim(std::string& str, const char* trim_chars, size_t n){
		return ltrim(rtrim(str, trim_chars, n), trim_chars, n);
	}

	static inline std::string& ltrim(std::string& str){
		return ltrim(str, " \t\n\r", 4);
	}
	static inline std::string& ltrim(std::string& str, const std::string& trim_chars){
		return ltrim(str, trim_chars.c_str(), trim_chars.length());
	}
	static std::string& ltrim(std::string& str, const char* trim_chars, size_t n){
		size_t trim_len = ltrim_len(str.c_str(), str.length(), trim_chars, n);
		if (trim_len > 0) str.erase(0, trim_len);
		return str;
	}

	static inline std::string& rtrim(std::string& str){
		return rtrim(str, " \t\n\r", 4);
	}
	static inline std::string& rtrim(std::string& str, const std::string& trim_chars){
		return rtrim(str, trim_chars.c_str(), trim_chars.length());
	}
	static std::string& rtrim(std::string& str, const char* trim_chars, size_t n){
		size_t len = str.length();
		size_t trim_len = rtrim_len(str.c_str(), len, trim_chars, n);
		if (trim_len > 0) str.erase(len - trim_len, trim_len);
		return str;
	}

	static std::string& capitalize(std::string& str){
		if (str.length() > 0 && is_lowercase(str[0])) {
			str.replace(0, 1, 1, (str[0] - 32));
		}
		return str;
	}

	static std::string& downcase(std::string& str){
		size_t len = str.length();
		for (size_t i = 0; i < len; ++i){
			if(is_uppercase(str[i])) str.replace(i, 1, 1, (str[i] + 32));
		}
		return str;
	}

	static std::string& upcase(std::string& str){
		size_t len = str.length();
		for (size_t i = 0; i < len; ++i){
			if(is_lowercase(str[i])) str.replace(i, 1, 1, (str[i] - 32));
		}
		return str;
	}

	static std::string& swapcase(std::string& str){
		size_t len = str.length();
		for (size_t i = 0; i < len; ++i){
			if(is_lowercase(str[i])) str.replace(i, 1, 1, (str[i] - 32));
			else if(is_uppercase(str[i])) str.replace(i, 1, 1, (str[i] + 32));
		}
		return str;
	}

	static inline int cmp_char(char x, char y){
		if (x > y) return 1;
		else if (x < y) return -1;
		else return 0;
	}

	static inline int casecmp(const std::string& x, const std::string& y){
		return casecmp(x.c_str(), x.length(), y.c_str(), y.length());
	}

	static int casecmp(const char* x, size_t x_len, const char* y, size_t y_len){
		size_t len = x_len > y_len ? y_len : x_len;
		int r = 0;
		for (size_t i = 0; i < len ; ++i){
			if (is_uppercase(x[i]) && is_lowercase(y[i])) r = cmp_char(x[i]+32, y[i]);
			else if (is_lowercase(x[i]) && is_uppercase(y[i])) r = cmp_char(x[i], y[i]+32);
			else r = cmp_char(x[i], y[i]);
			if (r != 0) return r;
		}
		return cmp_char(x_len, y_len);
	}

	static std::string& reverse(std::string& str){
		size_t len = str.length();
		size_t half_len = len / 2;
		for (size_t i = 0; i < half_len; ++i){
			if (str[i] != str[len-i-1]) {
				char ch = str[len-i-1];
				str.replace(len-i-1, 1, 1, str[i]);
				str.replace(i, 1, 1, ch);
			}
		}
		return str;
	}

	static std::string& squeeze(std::string& str){
		size_t len = str.length();
		char last = str.back();
		size_t dup_n = 0;
		for(size_t i=len-1; i>0; --i){
			if (str[i-1] == last){
				++dup_n;
			} else {
				if (dup_n>0){
					str.erase(i, dup_n);				
					dup_n = 0;
				}
				last = str[i-1];
			}
		}
		if (dup_n>0) str.erase(1, dup_n);
		return str;
	}

	static std::string& squeeze(std::string& str, const std::string& squeezed_str){
		return squeeze(str, squeezed_str.c_str(), squeezed_str.length());
	}

	static std::string& squeeze(std::string& str, const char* squeezed_str, size_t n){
		size_t len = str.length();
		char last = str.back();
		size_t dup_n = 0;
		for(size_t i=len-1; i>0; --i){
			if (str[i-1] == last && in_chars(str[i-1], squeezed_str, n)){
				++dup_n;
			} else {
				if (dup_n>0){
					str.erase(i, dup_n);
					dup_n = 0;
				}
				last = str[i-1];
			}
		}
		if (dup_n>0) str.erase(1, dup_n);
		return str;
	}

	static std::vector<std::string>& lines(const std::string& str, std::vector<std::string>& out){
		out.clear();
		size_t idx = 0;
		size_t line_len = 0;
		size_t last_idx = 0;
		while((idx = str.find('\n', idx)) != std::string::npos){
			line_len = idx < (last_idx + 1) ? 0 : (idx - last_idx);
			if (idx > last_idx && str[idx-1] == '\r' && line_len > 0) --line_len;
			if (line_len > 0) out.push_back(std::string(str.c_str()+last_idx, line_len));
			last_idx = ++idx;
		}

		if (last_idx < str.size()){
			out.push_back(std::string(str.c_str()+last_idx, str.size() - last_idx));
		}
		return out;
	}

	static inline bool include(const std::string& str, const std::string& sub){
		return (str.find(sub) != std::string::npos);
	}
	static inline bool include(const std::string& str, const char* sub){
		return (str.find(sub) != std::string::npos);
	}
	static inline bool include(const std::string& str, const char* sub, size_t len){
		return (str.find(sub, len) != std::string::npos);
	}

	static std::string& replace(std::string& str, const std::string& replaced, const std::string& sub){
		size_t idx = str.find(replaced);
		if (idx == std::string::npos) return str;
		return str.replace(idx, replaced.length(), sub);
	}

	static std::string& replace(std::string& str, char replaced, char sub){
		size_t idx = str.find(replaced);
		if (idx == std::string::npos) return str;
		return str.replace(idx, 1, 1, sub);
	}

	static std::string& replace_all(std::string& str, const std::string& replaced, const std::string& sub){
		size_t idx = std::string::npos;
		while((idx = str.rfind(replaced, idx)) != std::string::npos){
			str.replace(idx, replaced.length(), sub);
		}
		return str;
	}

	static std::string& replace_all(std::string& str, char replaced, char sub){
		size_t idx = std::string::npos;
		while((idx = str.rfind(replaced, idx)) != std::string::npos){
			str.replace(idx, 1, 1, sub);
		}
		return str;
	}
		
	static bool match(const std::string& str, const std::string& regexp){
		return std::regex_match(str.c_str(), std::regex(regexp));
	}

	static std::vector<std::string>& search(const std::string& str, const std::string& regexp, std::vector<std::string>& out){
		out.clear();
		std::match_results<std::string::const_iterator> mrs;
		std::string s = str;
		while (std::regex_search(s, mrs, std::regex(regexp))){
			out.push_back(mrs.str());
			s = mrs.suffix().str();		
		}
		return out;
	}

	static std::string& search(const std::string& str, const std::string& regexp, std::string& out){
		out.clear();
		std::match_results<std::string::const_iterator> mrs;
		std::regex rx(regexp); 
		if (std::regex_search(str, mrs, rx)){
			out = mrs.str();
		}
		return out;
	}

	static std::string& sub(std::string& str, const std::string& regexp, const std::string& fmt){
		if (has_catch(fmt)){
			std::cmatch mrs;
			if (std::regex_search(str.c_str(), str.c_str()+ str.length(), mrs, std::regex(regexp))){
				std::string s;
				str = mrs.prefix().str();
				std::string suf = mrs.suffix().str();
				str += sub_catch(mrs, fmt, s);
				str += suf;		
			} 
		} else {
			str = std::regex_replace(str, std::regex(regexp), fmt, std::regex_constants::format_first_only);
		}
	
		return str;
	}

	static std::string& gsub(std::string& str, const std::string& regexp, const std::string& fmt){
		if (has_catch(fmt)){
			std::cmatch mrs;
			std::regex rx(regexp);
			std::string suf = str;
			str.clear();
			while (std::regex_search(suf.c_str(), suf.c_str()+ suf.length(), mrs, rx, std::regex_constants::format_first_only)){
				std::string s;
				str += mrs.prefix();
				suf = mrs.suffix();
				str += sub_catch(mrs, fmt, s);
			}
			str += suf;
		} else {
			str = std::regex_replace(str, std::regex(regexp), fmt);
		}

		return str;
	}
	
private:
	String(){}

	static inline bool in_chars(char ch, const char* chars, size_t n){
		for(size_t i=0; i<n; ++i){
			if(ch == chars[i]) return true;
		}
		return false;
	}

	static size_t ltrim_len(const char* str, size_t len, const char* trim_chars, size_t n){
		size_t i = 0;
		for (i = 0; i < len; ++i){
			if (!in_chars(*(str + i), trim_chars, n)) break;
		}
		return i;
	}

	static size_t rtrim_len(const char* str, size_t len, const char* trim_chars, size_t n){
		size_t i = 0;
		for (i = len; i > 0; --i){
			if (!in_chars(*(str + i - 1), trim_chars, n)) break;
		}

		return (len - i);
	}

	static bool has_catch(const std::string& fmt){
		size_t len = fmt.length();
		for(size_t i = 0; i < len-1; ++i){
			if(fmt[i] == '\\' && is_digital(fmt[i+1])) return true;
		}
		return false;
	}

	static std::string& sub_catch(std::cmatch& mrs, const std::string& fmt, std::string& out){
		out.clear();
		size_t len = fmt.length();
		size_t i=0;

		for(i=0; i<len-1; ++i){
			if (fmt[i] == '\\' && is_digital(fmt[i+1])){
				out += mrs[char_to_int(fmt[i+1])].str();
				++i;
			} else {
				out += fmt[i];
			}
		}

		if(i<len) out += fmt[i];
		return out;
	}

};

__XNS_END_NAMESPACE
