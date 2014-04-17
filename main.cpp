#include <map>
#include <string>
#include <string.h>
#include <my_global.h>
#include <my_sys.h>
#include <mysql_com.h>

extern "C" {
	my_bool most_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
	void most_clear(UDF_INIT* initid, char* is_null, char *error);
	void most_add(UDF_INIT* initid, UDF_ARGS* args, char* is_null, char *error);
	void most_deinit(UDF_INIT *initid);
	char * most(UDF_INIT *initid, UDF_ARGS *args,
			  char *result, unsigned long *length,
			  char *is_null, char *error);
}

struct UDFMostData
{
	std::map<std::string, int> hits;
};

my_bool most_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
	if (args->arg_count != 1) {
		strcpy(message, "most must have exaclty one argument");
		return 1;
	}

	args->arg_type[0] = STRING_RESULT;

	initid->max_length = 65535;
	initid->maybe_null = 1;
	initid->ptr = (char*) new UDFMostData;

	return 0;
}

void most_clear(UDF_INIT* initid, char* is_null, char *error)
{
	UDFMostData * p = (UDFMostData *)initid->ptr;

	p->hits.clear();
}

void most_add(UDF_INIT* initid, UDF_ARGS* args, char* is_null, char *error)
{
	if (args->args[0])
	{
		UDFMostData * p = (UDFMostData *)initid->ptr;

		std::string k(args->args[0], args->lengths[0]);
		std::map<std::string, int>::iterator it = p->hits.find(k);
		if (it == p->hits.end())
		{
			p->hits[k] = 1;
		}
		else 
		{
			++(*it).second;
		}
	}
}

void most_deinit(UDF_INIT *initid)
{
	UDFMostData * p = (UDFMostData *)initid->ptr;
	delete p;
}

char * most(UDF_INIT *initid, UDF_ARGS *args,
		  char *result, unsigned long *length,
		  char *is_null, char *error)
{
	UDFMostData * p = (UDFMostData *)initid->ptr;

	if (p->hits.empty())
	{
		*is_null = 1;

		return NULL;
	}
	else
	{
		std::map<std::string, int>::iterator itMost = p->hits.begin();
		std::map<std::string, int>::iterator it = itMost;
		++it;
		for (; it != p->hits.end(); ++it)
		{
			if ((*it).second > (*itMost).second)
				itMost = it;
		}
		result = (char *)(*itMost).first.c_str();
		*length = (*itMost).first.size();
		
		return result;
	}
}
