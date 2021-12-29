/*  
    memlayout.h
    Name: Mohammadhadi Rouhani
    Contains all the required items to be included in the header file including:
    - required libraries for memlayout.c
    - The definitions of MEM_XX
    - Declaration of functions used
    - Conditions for PAGE_SIZE and USER_PAGE_SIZE
    - structure memregion
*/


#include<stdio.h>
#include<signal.h>
#include<setjmp.h>
#include<unistd.h>

#define MEM_RW 0
#define MEM_RO 1
#define MEM_NO 2



struct memregion
{
    void*from;
    void*to;
    unsigned char mode; /* Memory accessibility MEM_RW || MEM_RO || MEM_NO */
};

void sig_handler(int signum);
int get_mem_layout(struct memregion *regions, unsigned int size);
void display_regions(struct memregion *regions, int number_of_regions);
const unsigned int PAGE_SIZE;

#ifndef USER_PAGE_SIZE
#define PAGE_SIZE 4096
#endif

#ifdef USER_PAGE_SIZE
#define PAGE_SIZE USER_PAGE_SIZE
#endif