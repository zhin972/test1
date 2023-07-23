#include <stddef.h>
#ifndef _LIST_H
#define _LIST_H
// #include <stddef.h>
#define container_of(ptr, type, member) ({ \
    const typeof( ((type *)0)->member ) *__mptr = (ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})
//使用list_entry之后，得到容器结构体的地址
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)
//遍历head:pos类型为容器结构类型的指针,head是使用INIT_LIST_HEAD初始化的头指针,member是容器结构中的链表元素对象
#define list_for_each_entry(pos, head, member) \
    for (pos = list_entry((head)->next, typeof(*pos), member); \
    &pos->member != (head); \
    pos = list_entry(pos->member.next, typeof(*pos), member))

//链表结构
struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

//链表初始化
void INIT_LIST_HEAD(struct list_head *node);

//链表节点增加 
void _list_add(struct list_head *_new, struct list_head *prev, struct list_head *next);

//链表节点增加（头插）
void list_add(struct list_head *_new, struct list_head *head);

//链表节点增加（尾插）
void list_add_tail(struct list_head *_new, struct list_head *head);

//链表节点移除
void list_del(struct list_head *entry);

#endif 