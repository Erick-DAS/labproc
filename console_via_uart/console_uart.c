#include "uart.c"

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