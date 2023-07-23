#include <stdio.h>
#include "list.h"
#include "nh.h"
#include "prefix.h"

//添加prefix到prefix链表
int addPrefix(struct list_head *headnode_prefix, char *ip_prefix) {
    struct prefix *prefixTemp = getPrefixByIPpf(headnode_prefix, ip_prefix);
    //若存在旧的,用新的覆盖
    if( prefixTemp != NULL) {
        delPrefix(headnode_prefix, ip_prefix);
    }
    prefixTemp = malloc(sizeof(*prefixTemp)); //为prefix结构体申请内存并初始化
    if(prefixTemp == NULL) {
        printf("内存溢出,添加prefix失败\n");
        return -1;
    }
    strcpy(prefixTemp->ip_prefix, ip_prefix); //将传入的IP前缀填入结构体
    prefixTemp->ip_nexthop = NULL; //防止野指针
    list_add(&prefixTemp->list, headnode_prefix); //将prefix结构体挂到prefix链表上
    return 0;
}

//从prefix链表移除prefix
int delPrefix(struct list_head *headnode_prefix, char *ip_prefix) {
    struct prefix *prefixTemp = getPrefixByIPpf(headnode_prefix, ip_prefix);
    if(prefixTemp == NULL) {
        printf("移除的ip前缀%s不存在,移除失败\n", prefixTemp->ip_prefix);
        return -1;
    }
    printf("移除的ip前缀为:%s\n", prefixTemp->ip_prefix);
    list_del(&prefixTemp->list);
    free(prefixTemp);
    prefixTemp = NULL;
    return 0;
}

//prefix与nh关联(prefix链表,nh链表,ip前缀,下一跳ip)
int prefixToNh(struct list_head *headnode_prefix, struct list_head *headnode_nh, char *ip_prefix, char *ip_nexthop) {
    struct prefix *prefixTemp = getPrefixByIPpf(headnode_prefix, ip_prefix);
    //prefix检索不到的情况
    if (prefixTemp == NULL) {
        printf("ip前缀%s不存在,关联失败",ip_prefix);
        return -1;
    }
    struct nh *npTemp = getNhByIPnh(headnode_nh, ip_nexthop);
    //nh检索不到的情况
    if (npTemp == NULL) {
        printf("下一跳ip%s不存在,关联失败\n",ip_nexthop);
        return -1;
    }
    prefixTemp->ip_nexthop = npTemp;
    return 0;
}

//根据prefix查询nh
char *getNhByPrefix(struct list_head *headnode_prefix,char *ip_prefix) {
    struct prefix *prefixTemp = getPrefixByIPpf(headnode_prefix, ip_prefix);
    if( prefixTemp == NULL) {
        printf("该ip前缀不存在\t");
        return "error";
    }
    if( prefixTemp->ip_nexthop == NULL) {
        printf("该ip前缀对应的nh不存在\t");
        return "error";
    }
    return prefixTemp->ip_nexthop->ip_nexthop;
}

//在prefix链表中检索匹配ip前缀的prefix结构体
struct prefix *getPrefixByIPpf(struct list_head *headnode_prefix, char *ip_prefix) {
    struct prefix *prefixTemp;
    list_for_each_entry(prefixTemp, headnode_prefix, list) {
        //找到目标prefix
        if (strcmp(prefixTemp->ip_prefix, ip_prefix)==0) {
            return prefixTemp;
        }
    }
    //遍历完未找到目标prefix
    return NULL;
}

//在prefix链表中检索匹配下一跳ip的prefix结构体
struct prefix *getPrefixByIPnh(struct list_head *headnode_prefix, char *ip_nexthop) {
    struct prefix *prefixTemp;
    list_for_each_entry(prefixTemp, headnode_prefix, list) { 
        if (prefixTemp->ip_nexthop != NULL && strcmp(prefixTemp->ip_nexthop->ip_nexthop, ip_nexthop)==0) {
            return prefixTemp;               
        }              
    }
    return NULL;
}

