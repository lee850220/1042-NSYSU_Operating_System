#ifndef __MY_MM_H_INCLUDED__
#define __MY_MM_H_INCLUDED__

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *mymalloc(size_t size);
void myfree(void *ptr);
void *myrealloc(void *ptr, size_t size);
void *mycalloc(size_t nmemb, size_t size);

#endif

void *memStart;  
void *lastAddr;  
int Is_init;

typedef struct mcb{
    int available;  
    int size;
}mcb;
