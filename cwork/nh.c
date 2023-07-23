#include <stdio.h>
#include "list.h"
#include "nh.h"
#include "prefix.h"
//添加nh到nh链表
int addNextHop(struct list_head *headnode_nh, char *ip_nexthop) {
    struct nh *nhTemp = getNhByIPnh(headnode_nh, ip_nexthop);
    //若存在旧的,用新的覆盖'

    nhTemp = malloc(sizeof(*nhTemp)); //为nh结构体申请内存并初始化
    if(nhTemp == NULL) {
        printf("内存溢出,添加nh失败\n");
        return -1;
    }
    strcpy(nhTemp->ip_nexthop, ip_nexthop); //将传入的下一跳IP填入结构体
    list_add(&nhTemp->list, headnode_nh); //将nh结构体挂到nh链表上
    return 0;
}

//从nh链表移除nh
int delNextHop(struct list_head *headnode_nh,  struct list_head *headnode_prefix, char *ip_nexthop) {
    struct nh *nhTemp = getNhByIPnh(headnode_nh, ip_nexthop);
    if(nhTemp == NULL) {
        printf("要删除的下一跳ip%s不存在,删除无效\n", ip_nexthop);
        return -1;
    }
    struct prefix *prefixTemp = getPrefixByIPnh(headnode_prefix, ip_nexthop);
    //存在与该nh关联的prefix
    if(prefixTemp != NULL) {
        prefixTemp->ip_nexthop = NULL;
    }
    list_del(&nhTemp->list);
    free(nhTemp);
    nhTemp = NULL;
    return 0;
}

//在np链表中检索匹配下一跳ip的np结构体
struct nh *getNhByIPnh(struct list_head *headnode_nh, char *ip_nexthop) {
    struct nh *nhTemp;
    list_for_each_entry(nhTemp, headnode_nh, list) {
        if (strcmp(nhTemp->ip_nexthop, ip_nexthop)==0) {
            return nhTemp;
        }
    }
    //遍历完未找到目标nexthop
    return NULL;
}