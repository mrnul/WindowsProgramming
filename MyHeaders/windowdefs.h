#pragma once

#define MyHeaders_windefs

#include <Windows.h>

#define CREATE_NEW_DATA_TYPE(name)	struct name																		\
									{																				\
										unsigned int val;															\
										explicit name(unsigned int v) : val(v)			{ }							\
										operator unsigned int() const					{ return val; }				\
										name operator|(name v) const					{ return name(val | v); }	\
										name operator|(unsigned int v) const			{ return name(val | v); }	\
										~name() {}	/*is this ok?*/													\
									}

#define CONTROLPROC(name, handle, msg, wp, lp, id, data)	LRESULT CALLBACK name(HWND handle, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR id, DWORD_PTR data)
#define DEFCONTROLPROC(handle, msg, wp, lp)					DefSubclassProc(handle, msg, wp, lp)
