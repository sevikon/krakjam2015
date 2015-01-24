#include "glUtils.h"

using namespace std;

const string concat(string fst, string snd)
{
	return (fst + snd);
}

const char* concat_cstr(string fst, string snd)
{
	return (fst + snd).c_str();
}