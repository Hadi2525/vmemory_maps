/* memlayout.c
    Name: Mohammadhadi Rouhani

    This file contains two functions:
        1- get_mem_layout : Which has an object and integer as inputs to scan
        the entire memory area from 0x0 to 0xffffffff with the size of
        PAGE_SIZE (default is 4096). that is defined either by the USER or by 
        the header's default definition. This function returns the number of regions.

        2- display_regions: The role of this function is to use stdout stream to
        print out the memory region as per the description of the assignment.

*/

#include "memlayout.h"


jmp_buf env;
void sig_handler(int signum)
{
    siglongjmp(env,1);
}


int get_mem_layout(struct memregion *regions, unsigned int size)
{
    int ind = 0;
    int mode_flag;
    int temp_flag; // A temporary flag to store the mode of previous page

    signal(SIGSEGV,sig_handler);
    signal(SIGBUS,sig_handler);

    char *p = (char *)0x0;
    int pages;
    if(PAGE_SIZE==4096)
    {
        pages = 1024*1024; // 2^32/4096 = 2^20 = 1024*1024
    }
    else if(PAGE_SIZE == 16384)
    {
        pages = 1024*64;
    }
    for(int i=0;i<pages;i++) 
    {
        temp_flag = mode_flag;
        int key;
        key = sigsetjmp(env, 1);
        if(key==0){
            char a = *p; // We can read!
            int key1;
            key1 = sigsetjmp(env, 1);
            if(key1==0)
            {
                *p = a; // We can read and write! 
                mode_flag = MEM_RW;
                
            }
            else
            {
                mode_flag = MEM_RO;
                
            }
        }
        else
            {
                mode_flag = MEM_NO;
                
            }
        if(p == 0x0){ // Condition for initializing the memory scanning
            regions[ind].from = p;
            regions[ind].mode = mode_flag;
        }
        if(p != 0x0 && mode_flag != temp_flag){ // Condition when the end of a memregion
                                                // is met.
            regions[ind].to = p - 1;
            regions[ind].mode = temp_flag;
            ind++;
            regions[ind].from = p;
        }
        switch(PAGE_SIZE)
        {
            case 4096:
                if(p == (void*)0xfffff000)
                {   // Condition for the end of scanning
                    regions[ind].to = p+PAGE_SIZE-1;
                    regions[ind].mode = mode_flag;
                    continue;
                }
                break;
            case 16384:
                if(p == (void*)0xffff0000)
                {   // Condition for the end of scanning
                    regions[ind].to = p+PAGE_SIZE-1;
                    regions[ind].mode = mode_flag;
                    continue;
                }
                break;
        }
        
        p+=PAGE_SIZE;
    } // End of While loop
    return ind+1; // Number of regions ...
}

void display_regions(struct memregion *regions, int number_of_regions)
{
    for(int i=0;i<=number_of_regions-1;i++)
    {
        switch (regions[i].mode)
        {
        case 0:
            printf("0x%08x - 0x%08x RW\n",(unsigned int)(regions[i].from),(unsigned int)(regions[i].to));
            break;
        
        case 1:
            printf("0x%08x - 0x%08x RO\n",(unsigned int)(regions[i].from),(unsigned int)(regions[i].to));
            break;
        case 2:
            printf("0x%08x - 0x%08x NO\n",(unsigned int)(regions[i].from),(unsigned int)(regions[i].to));
        }
        
    }
    printf("_____________________________________\n");
}