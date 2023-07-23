#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "nh.h"

//链表初始化
void INIT_LIST_HEAD(struct list_head *node) {
    node->next=node;
    node->prev=node;
};

//链表节点增加 
void _list_add(struct list_head *new, struct list_head *prev, struct list_head *next) {
    prev->next=new;
    new->next=next;
    next->prev=new;
    new->prev=prev;
}

//链表节点增加（头插）
void list_add(struct list_head *new, struct list_head *head) {
    _list_add(new, head, head->next);
}

//链表节点增加（尾插）
void list_add_tail(struct list_head *new, struct list_head *head) {
    _list_add(new, head->prev, head);
}

//链表节点移除
void list_del(struct list_head *entry) {
    struct list_head *prev = entry->prev;
    struct list_head *next = entry->next;
    prev->next = next;
    next->prev = prev;
}