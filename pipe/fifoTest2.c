#include<stdlib.h>
#include<stdio.h>
#include<strings.h>
#include<signal.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<errno.h>
#define FIFO_NAME "./fifo_file"

int mkfifo(const char *pathname, mode_t mode);

void printError(char* estr){
    perror(estr);
    exit(-1);
}

int create_open_fifo(char *fifo_name, int open_mode){
    int ret = -1;
    int fd = -1;
    ret = mkfifo(fifo_name, 0664);
    //只报错文件存在时错误
    if(ret == -1 && errno != EEXIST)
        printError("mkfifo() failed.");
    //只写方式
    fd = open(FIFO_NAME, open_mode);
    if(fd == -1)
        printError("open() failed.");
    return fd;
}

void signal_fun(int signo){
    remove(FIFO_NAME);
    exit(-1);
}

int main(void){
    char buf[100] = {0};
    int fd = -1;
    signal(SIGINT, signal_fun);
    fd = create_open_fifo(FIFO_NAME, O_RDONLY);
    while (1)
    {
        bzero(buf, sizeof(buf));
        read(fd, buf, sizeof(buf));
        printf("recv: %s\n", buf);
    }
    


    return 0;
}