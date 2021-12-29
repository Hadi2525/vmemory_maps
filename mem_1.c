/*mem_1
  Name: Mohammadhadi Rouhani
  By using calloc() from stdlib library we can allocate and initialize a chunk
  of memory to zero. calloc() is assigned to a pointer called ptr. 
  This variable points to 16 MB of memory in this demo. */


#include"memlayout.h"
#include<stdlib.h>

int main(){
  unsigned int size = 30;
  struct memregion regions[size];
  int num_of_regions;
  float *ptr;

  num_of_regions = get_mem_layout(regions,size);
  display_regions(regions,num_of_regions);

  ptr = (float *)calloc(4096*4096,sizeof(float));

  num_of_regions = get_mem_layout(regions,size);
  display_regions(regions,num_of_regions);

  return 0;
}