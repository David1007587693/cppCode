/*
1. msgget(),创建或获取某个已存在信息队列
2. msgsend(),利用信息队列标识符发送某编号的信息
3. msgrcv(),利用信息队列标识符接收某个编号的信息
4. msgctl(),利用信息队列标识符删除队列
*/
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#define MSG_FILE "./msgfile"
//int msgget(key_t key, int msgflag);

void print_error(char *error_msg){
    printf("%s\n", error_msg);
    exit(0);
}

int create_or_get_msgque(void){
    int msgid = -1;
    key_t key = -1;
    int fd = 0;
    //创建消息队列文件(使用路径生成key)
    fd = open(MSG_FILE, O_RDWR|O_CREAT, 0664);
    if(fd == -1) print_error("open() failed.");

    //利用存在的路径名和8位整型计算出key值
    key = ftok(MSG_FILE, 'a');
    printf("key = %d\n", key);
    if(key == -1) print_error("ftok() failed.");

    //利用key值创建或获取消息队列
    msgid = msgget((key_t)123, 0664|IPC_CREAT);
    printf("msgid = %d\n", msgid);
    if(msgid == -1){
        printf("errno = %s\n", strerror(errno));
        print_error("msgget() failed.");
        
    }

    return msgid;
}

int main(){
    int msgid = -1;
    msgid = create_or_get_msgque();

}