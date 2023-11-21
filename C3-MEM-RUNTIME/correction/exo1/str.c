#include <str.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>




string* str_create(const char * str)
{
	string* ret = malloc(sizeof(string));
	if(!ret)
	{
		ret->data = NULL;
		ret->len = 0;
	}
	ret->len = strlen(str);
	ret->data = malloc(sizeof(char) * ret->len);
	memcpy(ret->data, str, ret->len);
	
	return ret;

}

void str_destroy(string* s1)
{
	if(s1->data)
		free(s1->data);
	free(s1);

}

void str_copy(string* s1, const string* s2)
{
	if(s1->data)
		free(s1->data);
	s1->len = 0;

	if (s2->len > 0)
	{
		s1->len = s2->len;
		s1->data = malloc(sizeof(char) * s2->len);
		memcpy(s1->data, s2->data, s2->len);
	}
}

int str_compare(const string* s1, const string* s2)
{
	size_t i;
	for (i = 0; i < s1->len && i < s2->len; ++i) {
		if(s1->data[i] == s2->data[i])
			continue;
		else if(s1->data[i] < s2->data[i])
			return -1;
		else return 1;
	}

	return 0;
}

void str_append(string* s1, const string* s2)
{
	if(s2->data == NULL)
		return;

	char* buf = realloc(s1->data, sizeof(char) * (s1->len + s2->len));
	s1->data = buf;
	s1->len += s2->len;
	memcpy(buf + s1->len, s2->data, s2->len);
	
}

string* str_slice(const string* s1, size_t start, size_t end)
{
	if(start < 0 || end > s1->len || end < 0 || s1->data == NULL)
		return str_create(NULL);

	string *ret = malloc(sizeof(string));
	ret->data = malloc(sizeof(char) * (end-start));
	ret->len = end-start;

	memcpy(ret->data, s1->data + start, ret->len);
	return ret;
}

#include <regex.h>

bool str_regex(const string*s1,const string*pattern)
{
	regex_t obj;
	if(regcomp(&obj, pattern->data, REG_EXTENDED | REG_NOSUB) <0)
		return false;
	
	int ret = regexec(&obj, s1->data, 0, NULL, 0);
	regfree(&obj);
	if(ret == 0)
		return true;
	return false;

}

void str_print(string*s1)
{
	if(s1->data == NULL) return;
	char* buf = malloc(sizeof(char) * (s1->len + 1));
	memcpy(buf, s1->data, s1->len);
	buf[s1->len] = '\0';
	printf("%s\n", buf);
	free(buf);
}
