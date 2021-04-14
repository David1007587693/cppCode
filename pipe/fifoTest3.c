#include<stdlib.h>
#include<stdio.h>
#include<strings.h>
#include<signal.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<errno.h>
#define FIFO_NAME1 "./fifo_file1"
#define FIFO_NAME2 "./fifo_file2"
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
    fd = open(FIFO_NAME1, open_mode);
    if(fd == -1)
        printError("open() failed.");
    return fd;
}

void signal_fun(int signo){
    remove(FIFO_NAME1);
    remove(FIFO_NAME2);
    exit(-1);
}

int main(void){
    char buf[100] = {0};
    int fd1 = -1, fd2 = -1;
    //对管道fd1读，对管道fd2写
    fd1 = create_open_fifo(FIFO_NAME1, O_RDONLY);
    fd2 = create_open_fifo(FIFO_NAME2, O_WRONLY);
    //创建子进程，父进程负责写fd2,子进程负责读fd1
    int ret = fork();
    if(ret > 0){
        //父进程
        while (1)
        {
            char msg[] = "message from fifoTest3";
            write(fd2, msg, sizeof(msg));
            sleep(1);
        }
    }else if(ret == 0){
        //子进程
        signal(SIGINT, signal_fun);
        while (1)
        {
            bzero(buf, sizeof(buf));
            read(fd1, buf, sizeof(buf));
            printf("fifoTest3 child recv: %s\n", buf);
        }
    }
    return 0;
}