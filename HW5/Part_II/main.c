#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define INIT_SIZE 32

typedef struct text{
    char t[INIT_SIZE];
}text;

int GetFileSize(const char* filePath, const char* mode){
  int fileLength = 0;
  FILE *fp;

  if(! (fp = fopen(filePath, mode))){
    return -1;
  }
  
  if(fseek(fp, 0, SEEK_END)) {
    return -1;
  }
  //取得檔案大小 單位byte
  fileLength = ftell(fp);
  fclose(fp);
 
  return fileLength;
}

int main(int argc, char* argv[]){
    int fd = 0, len = 0, i = 0, j = 0;
    char x, temp[INIT_SIZE], fin;
    text *ptr = NULL;
    
    fd = open(argv[1], O_RDWR); 
    if(fd<0){
        printf("File open failed!\n\n");
        exit(1);
    }
    
    len = GetFileSize(argv[1], "r");
    if(len == -1){
        printf("File open failed!\n\n");
        exit(1);
    }
    ptr = (text*)mmap(NULL, sizeof(text)*(len/32)-1, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    while(read(fd, &x, 1)){
        if(i == INIT_SIZE-1){
            memcpy((ptr+j)->t, temp, INIT_SIZE-1);
            i = 0;
            j++;
        }
        temp[i] = x;
        i++;
    }
    close(fd);
    while(1){
        printf("Input a string to replace the first page of mapping file.\nInput -1 to exit.\n");
        scanf("%s",temp);
        if(temp[0]=='-') break;
        memcpy((ptr)->t, temp, INIT_SIZE-1);
    }
    munmap(ptr, len);    
    return 0;
}
