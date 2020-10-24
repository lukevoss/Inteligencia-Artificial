#pragma once

// Data structure for stack
#ifndef stack
#define stack
typedef struct{
	int maxsize;	// define max capacity of stack
	int top;
	int* items;
}; stack
#endif

// Utility function to initialize stack
#ifndef newStack
#define newStack
typedef struct(int capacity)
{
	struct stack* pt = (struct stack*)malloc(sizeof(struct stack));

	pt->maxsize = capacity;
	pt->top = -1;
	pt->items = (int*)malloc(sizeof(int) * capacity);

	return pt;
}; new Stack
#endif
