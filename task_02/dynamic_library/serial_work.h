#ifndef __SERIAL__WORK__H__
#define __SERIAL__WORK__H__

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

ARR_DLL int ARR_DECL read_string(char **str, int *len);
ARR_DLL int ARR_DECL find_matchings(char *line, char *str, int mainstr, int len_substr);
#endif