#include "pi.h"
#include "stdio.h"
#include <stdlib.h>
#include <sys/stat.h>

extern unsigned heap_svr;


void *_sbrk(int incr) {
    static unsigned char *heap = NULL;
    unsigned char *prev_heap;
  
    if (heap == NULL) {
      heap = (unsigned char *)&heap_svr;
    }
    prev_heap = heap;
  
    heap += incr;
    return prev_heap;
  }
  
int _close(int file) {
    return -1;
  }
  
int _fstat(int file, struct stat *st) {
    // st->st_mode = S_IFCHR;
    return 0;
  }
  
int _isatty(int file) {
    return 1;
  }
  
int _lseek(int file, int ptr, int dir) {
    return 0;
  }
  
void _exit(int status) {
    
  }
  
void _kill(int pid, int sig) {
    
  }
  
int _getpid(void) {
    return -1;
  }
  
int _open(const char *name, int flags, int mode) {
    return -1;
  }
  
int _read (int file, char * ptr, int len) {
    return -1;
  }
  
  

int _write(int handle, char *data, int size) {
    uart_init(115200);
    int i;
    if(handle != 1) return -1;     // 1 = stdout
    for(i=0; i<size; i++) {
        uart_putc(data[i]);
    }
    return i;
 }
 
 int main(){
     printf("Hello World\n");
 }