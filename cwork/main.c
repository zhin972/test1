#include <stdio.h>
#include <stdlib.h>
#include "prefix.h"
#include "nh.h"
#include "list.h"

int main() {
    //初始化prefix链表和nh链表
    struct list_head headnode_prefix;
    INIT_LIST_HEAD(&headnode_prefix);
    struct list_head headnode_nh;
    INIT_LIST_HEAD(&headnode_nh);

    //prefix链表添加如下成员
    addPrefix(&headnode_prefix, "1.0.0.1/32");
    addPrefix(&headnode_prefix, "2.0.0.1/32");
    addPrefix(&headnode_prefix, "3.0.0.1/32");
    addPrefix(&headnode_prefix, "1.0.0.0/24");
    addPrefix(&headnode_prefix, "2.0.0.0/24");

    //nh链表添加如下成员
    addNextHop(&headnode_nh, "4.0.0.1");
    addNextHop(&headnode_nh, "4.0.0.2");
    addNextHop(&headnode_nh, "4.0.0.3");

    //进行prefix与nh关联
    prefixToNh(&headnode_prefix,&headnode_nh, "1.0.0.1/32", "4.0.0.1");
    prefixToNh(&headnode_prefix,&headnode_nh, "2.0.0.1/32", "4.0.0.1");
    prefixToNh(&headnode_prefix,&headnode_nh, "3.0.0.1/32", "4.0.0.2");
    prefixToNh(&headnode_prefix,&headnode_nh, "1.0.0.0/24", "4.0.0.7");   //异常值
    prefixToNh(&headnode_prefix,&headnode_nh, "1.0.0.0/24", "4.0.0.3");
    prefixToNh(&headnode_prefix,&headnode_nh, "2.0.0.0/24", "4.0.0.3");

    //根据如下prefix查询nh
    char *nh_res;
    nh_res = getNhByPrefix(&headnode_prefix, "1.0.0.1/32");
    printf("1.0.0.1/32的nh:%s\n", nh_res);
    nh_res = getNhByPrefix(&headnode_prefix, "3.0.0.1/32");
    printf("3.0.0.1/32的nh:%s\n", nh_res);
    nh_res = getNhByPrefix(&headnode_prefix, "1.0.0.0/24");
    printf("1.0.0.0/24的nh:%s\n", nh_res);
    nh_res = getNhByPrefix(&headnode_prefix, "2.0.0.0/24");
    printf("2.0.0.0/24的nh:%s\n", nh_res);

    //删除如下nh
    delNextHop(&headnode_nh, &headnode_prefix, "4.0.0.1");
    delNextHop(&headnode_nh, &headnode_prefix, "4.0.0.12");  //异常值

    //删除如下prefix
    delPrefix(&headnode_prefix, "2.0.0.0/24");
    delPrefix(&headnode_prefix, "3.0.0.1/32");  
    
    //进行prefix与nh关联
    prefixToNh(&headnode_prefix,&headnode_nh, "1.0.0.1/32", "4.0.0.2");

    //根据如下prefix查询nh
    nh_res = getNhByPrefix(&headnode_prefix, "1.0.0.1/32");
    printf("1.0.0.1/32的nh:%s\n", nh_res);
    nh_res = getNhByPrefix(&headnode_prefix, "2.0.0.1/32");
    printf("2.0.0.1/32的nh:%s\n", nh_res);
    nh_res = getNhByPrefix(&headnode_prefix, "1.0.0.0/24");
    printf("1.0.0.0/24的nh:%s\n", nh_res);
    nh_res = getNhByPrefix(&headnode_prefix, "2.0.0.0/24");
    printf("2.0.0.0/24的nh:%s\n", nh_res);
       
    return 0;
}
