#include<cstring>
#include<cstdio>
typedef struct msg_block1
{
    int len;
    char* data;
    int hash_id;
    
} __attribute__((packed)) msg_block_t1;


typedef struct msg_block2
{
    int len;
    char data[];//后面hash_id跟data的地址相同，所以一般要放到最后。
    int hash_id;
    
} __attribute__((packed)) msg_block_t2;


typedef struct msg_block3
{
    int len;
    char data[8];
    int hash_id;
    
} __attribute__((packed)) msg_block_t3;


int main()
{
    msg_block_t1 msg1;
    //memcpy(msg1.data,"aaaaaa",7);//segment fault
    msg1.len = 7 + sizeof(msg_block_t1);
    msg1.hash_id = 1;
    printf("member address of msg_block_t1:len:%p  data:%p  hash_id%p",&msg1.len, &msg1.data, &msg1.hash_id);
    msg_block_t2 msg2; 
    static char msg_buf[1024 * 150] = {0};
    msg_block_t2 * pmsg2 = (msg_block_t2 *)msg_buf;
    msg2.len = 7 + sizeof(msg_block_t2);
    msg2.hash_id = 1;
    memcpy(msg2.data,"aaaaaa",7);
    memcpy(pmsg2->data,"aaaaaa",7);
    pmsg2->hash_id =2;
    pmsg2->len = 1;


    printf("member address of msg_block_t2:len:%p  data:%p  hash_id%p",&msg2.len, &msg2.data, &msg2.hash_id);

    msg_block_t3 msg3;
    memcpy(msg3.data,"aaaaaa",7);
    msg3.len = 7 + sizeof(msg_block_t3);
    msg3.hash_id = 1;
    printf("member address of msg_block_t3:len:%p  data:%p   hash_id%p",&msg2.len, &msg2.data, &msg2.hash_id);

    int len1,len2,len3;
    len1 = sizeof(msg_block_t1);
    len2 = sizeof(msg_block_t2);
    len3 = sizeof(msg_block_t3);    
    printf("struct length :len1:%d  len2:%d   len3%d", len1, len2, len3);

}
