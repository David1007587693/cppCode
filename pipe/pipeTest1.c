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
    int pipefd[2] = {0};    //存放管道读写描述符(0读1写)
    ret = pipe(pipefd);
    if(ret == -1)
        printError("pipe failed");
    //printf("pipefd[0] = %d, pipefd[1] = %d\n ", pipefd[0], pipefd[1]);
    ret = fork();   //子进程返回0，父进程返回子进程id
    if(ret == 0){
        //子进程
        
        //关闭写操作符
        close(pipefd[1]);
        close(pipefd[0]);
        
        //printf("子进程: pipefd[0] = %d, pipefd[1] = %d\n ", pipefd[0], pipefd[1]);
        while (1)
        {
            char buf[30];
            bzero(buf, sizeof(buf));
            //从管道读信息
            read(pipefd[0], buf, sizeof(buf));
            printf("child, recv:%s\n", buf);
        }
        
        
    }else if(ret > 0){
        //父进程
        //关闭读操作符
        //忽略SIGPIPE信号
        //signal(SIGPIPE, SIG_IGN);
        //close(pipefd[0]);
        //printf("父进程: pipefd[0] = %d, pipefd[1] = %d\n ", pipefd[0], pipefd[1]);
        while (1)
        {
            char msg[] = "msg from parent";
            //写信息到管道
            write(pipefd[1], msg, sizeof(msg));
            sleep(1);
        }
        
        
    }

    return 0;
}
