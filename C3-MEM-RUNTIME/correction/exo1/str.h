#ifndef STR_H_
#define STR_H_

#include <stddef.h>
#include <stdbool.h>

struct string_s
{
	char* data;
	size_t len;
};

typedef struct string_s string;

string* str_create(const char * str);
void str_destroy(string* s1);
void str_copy(string* s1, const string* s2);
int str_compare(const string* s1, const string* s2);
void str_append(string* s1, const string* s2);
string* str_slice(const string* s1, size_t start_idx, size_t end_idx);
bool str_regex(const string*s1, const string*pattern);

#endif /* ifndef STR_H_ */
