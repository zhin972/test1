#ifndef _NH_H
#define _NH_H
#include "list.h"
//下一跳IP结构体
struct nh {
    char ip_nexthop[20];
    struct list_head list;
};

//添加nh到nh链表
int addNextHop(struct list_head *headnode, char *ip_nexthop);

//从nh链表移除nh
int delNextHop(struct list_head *headnode_nh,  struct list_head *headnode_prefix, char *ip_nexthop);

//在np链表中检索匹配下一跳ip的np结构体
struct nh *getNhByIPnh(struct list_head *headnode_nh, char *ip_nexthop);
#endif