#include<stdlib.h>
#include<stdio.h>
#include<strings.h>
#include<signal.h>
#include<unistd.h>

void printError(char* estr){
    perror(estr);
    exit(-1);
}

int main(){
    int ret = 0;
    //创建管道1
    int pipefd1[2] = {0};    //存放管道读写描述符(0读1写)
    ret = pipe(pipefd1);
    if(ret == -1)
        printError("pipe1 failed");
    //创建管道2
    int pipefd2[2] = {0};
    ret = pipe(pipefd2);
    if(ret == -1)
        printError("pipe2 failed");
    //printf("pipefd[0] = %d, pipefd[1] = %d\n ", pipefd[0], pipefd[1]);
    ret = fork();   //子进程返回0，父进程返回子进程id

    if(ret == 0){
        //子进程
        //关闭管道1写操作符，关闭管道2读操作
        close(pipefd1[1]);
        close(pipefd2[0]);
        char buf1[30];
        //printf("子进程: pipefd[0] = %d, pipefd[1] = %d\n ", pipefd[0], pipefd[1]);
        while (1)
        {
            char msg[] = "msg from child";
            //写管道2
            write(pipefd2[1], msg, sizeof(msg));
            sleep(1);
            //读管道1
            bzero(buf1, sizeof(buf1));
            read(pipefd1[0], buf1, sizeof(buf1));
            printf("child, recv:%s\n", buf1);
            //sleep(1);
        }
    }else if(ret > 0){
        //父进程
        //关闭读操作符
        //忽略SIGPIPE信号
        //signal(SIGPIPE, SIG_IGN);
        //close(pipefd[0]);
        //printf("父进程: pipefd[0] = %d, pipefd[1] = %d\n ", pipefd[0], pipefd[1]);
        char buf2[30];
        close(pipefd1[0]);
        close(pipefd2[1]);
        while (1)
        {
            char msg[] = "msg from parent";
            //写信息到管道1
            write(pipefd1[1], msg, sizeof(msg));
            sleep(1);
            //读管道2信息
            bzero(buf2, sizeof(buf2));
            read(pipefd2[0], buf2, sizeof(buf2));
            printf("parent, recv:%s\n", buf2);
        }  
    }
    return 0;
}
