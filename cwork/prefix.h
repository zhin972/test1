#ifndef _PREFIX_H
#define _PREFIX_H
#include "list.h"
//prefix结构体
struct prefix {
    char ip_prefix[20];
    struct nh *ip_nexthop;
    struct list_head list;
};
//添加prefix到prefix链表(prefix链表,ip前缀)
int addPrefix(struct list_head *headnode, char *ip_prefix);

//从prefix链表移除prefix(prefix链表,ip前缀)
int delPrefix(struct list_head *headnode, char *ip_prefix);

//prefix与nh关联(prefix链表,nh链表,ip前缀,下一跳ip)
int prefixToNh(struct list_head *headnode_prefix, struct list_head *headnode_nh, char *ip_prefix, char *ip_nexthop);

//根据prefix查询nh
char *getNhByPrefix(struct list_head *headnode1,char *ip_prefix);

//在prefix链表中检索匹配ip前缀的prefix结构体
struct prefix *getPrefixByIPpf(struct list_head *headnode_prefix, char *ip_prefix);

//在prefix链表中检索匹配下一跳ip的prefix结构体
struct prefix *getPrefixByIPnh(struct list_head *headnode_prefix, char *ip_nexthop);
#endif