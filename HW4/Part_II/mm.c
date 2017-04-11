#include "mm.h"

void mem_init(){
    lastAddr = sbrk(0);
    memStart = lastAddr;
    Is_init = 1;
}

void *mymalloc(size_t size)
{
    void *current = memStart;
    void *rlt = NULL;
    if(!Is_init)    mem_init();
    
    size += sizeof(mcb);    
    while (current != lastAddr) {   
        mcb *pcurrent = current;   
        if (pcurrent->available && pcurrent->size >= size){  
            pcurrent->available = 0;   
            rlt = current;   
            break;   
        }   
        current += pcurrent->size;   
    }  
    
    if(!rlt){  
        sbrk(size);   
        rlt = lastAddr; 
        lastAddr += size;  
        mcb *pcb = rlt;   
        pcb->size = size;   
        pcb->available = 0;   
    }   
    rlt += sizeof(mcb);   
    
    return rlt;
}

void myfree(void *ptr)
{
    mcb *pmcb = (mcb *)(ptr - sizeof(mcb));  
    pmcb->available = 1;
}

void *myrealloc(void *ptr, size_t size)
{
    void *rlt = NULL;
    
    if(ptr!=NULL){
        rlt = mymalloc(size);
        
    }else   return mymalloc(size);
}

void *mycalloc(size_t nmemb, size_t size)
{
    void *rlt = NULL;
    int *t = NULL;

    if(!Is_init)    mem_init();    
    rlt = mymalloc(nmemb*size);
    t=(int*)rlt;
    bzero((int*)t, size);
    return (void*)t;
}

int main(){
    int s = 0, i = 0;
    int *test_int = NULL;
    char *test_char = NULL;
    mem_init();
    
    printf("Test malloc\nmake a 5 char size, each member is a in default.\n");
    test_char = (char*)mymalloc(sizeof(char)*5);
    for(i = 0; i < 5; i++) {
        test_char[i]='a';
        printf("test_char[%d]=%c\n", i, test_char[i]);
    }
    myfree(test_char);
    printf("\nTest calloc\nmake a 5 int size in default without setting properties.\n");
    test_int =  (int*)mycalloc(sizeof(int), 5);
    for(i = 0; i < 5; i++) {
        printf("test_int[%d]=%d\n", i, test_int[i]);
    }
    
    printf("\nTest realloc\nmake previous int array to a 8-size array each member is 5.\n");
    test_int = (int*)myrealloc(test_int, 8);
    for(i = 0; i < 8; i++) {
        test_int[i] = 5;
        printf("test_int[%d]=%d\n", i , test_int[i]);
    }
    myfree(test_int);
    
    
    
    return 0;
}
