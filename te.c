#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

//消息的数据结构
struct msg_st{
    long int msg_type;
    char text[1024];
};

int main()
{
    int msgid=-1;
    struct msg_st data;
    long int msgtype = 0;     //接收为0，发送为1
    int ret=-1;
    
    //建立消息队列
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if(msgid==-1)
    {
        perror("msgget create fail!");
        return -1;
    }
    
    while(1)
    {
        //从队列中获取消息，直到遇到quit为止
        ret=msgrcv(msgid,(void*)&data,1024,msgtype,0);
        if(ret==-1)
        {
            perror("msgrcv fail");
            break;
        }
        
        printf("msg receive:%s\n",data.text);
        
        if(strncmp(data.text,"quit",4)==0)
        {
            printf("msg receive end!\n");
            break;
        }
        
    }
    
    //删除消息队列
    ret=msgctl(msgid,IPC_RMID,0);
    if(ret==-1)
    {
        perror("msgctl delete fail!");
        return -1;
    }
    
    return 0;
}