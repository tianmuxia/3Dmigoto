#pragma once

#include <windows.h>

// This version of EnterCriticalSection will use the function and line number
// in any lock stacks dumped when potential deadlock hazards are detected:
#define EnterCriticalSectionPretty(lock) \
	_EnterCriticalSectionPretty(lock, __FUNCTION__, __LINE__)
void _EnterCriticalSectionPretty(CRITICAL_SECTION *lock, char *function, int line);

// Use this when initialising a critical section in 3DMigoto to give it a nice
// name in lock stack dumps rather than using its address:
#define InitializeCriticalSectionPretty(lock) \
	_InitializeCriticalSectionPretty(lock, #lock)
void _InitializeCriticalSectionPretty(CRITICAL_SECTION *lock, char *lock_name);

void enable_lock_dependency_checks();
struct held_lock_info {
	CRITICAL_SECTION *lock;
	uintptr_t ret;
	size_t stack_hash;
	char *function;
	int line;
};