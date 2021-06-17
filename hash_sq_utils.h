/**
* @file hash_sq_utils.h
* @author Ziru Pan
* @version 1.2
* @date 2021/6/16
* @brief The header file of hash_sq_main.c which describes the property of HashTable and functions.
*/
#pragma once
#ifndef __HASH_H__
#define __HASH_H__
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "malloc.h"
#include "windows.h"
#define HashMaxSize 10 //哈希表容量
#define LoadFactor 1 //负载因子LoadFactor

typedef int KeyType;
typedef int (*HashFunc)(KeyType key); //重定义哈希函数

typedef enum State //用于表示每个元素的状态
{
    EMPTY,  //空
    VALUE,  //当前有值
    DELETED //当前结点已被删除
} State;

typedef struct ValueStruc   //数据元素
{
    char name[10];  //姓名
    char num[10];   //学号
    int score;      //分数
} ValueStruc;

typedef struct HashElem //哈希表的数据节点
{
    KeyType key;
    ValueStruc value;
    State state;
} HashElem;

typedef struct HashTable //哈希表
{
    HashElem *data;
    int size;   //哈希表尺寸
    HashFunc func;
} HashTable;

/*----哈希表的相关操作----*/
//哈希函数
int HashFunction(KeyType key);

//初始化
void HashInit(HashTable *ht, HashFunc func);

//插入
int HashInsert(HashTable *ht, KeyType key, ValueStruc value);

//根据key查找
HashElem *HashSearch(HashTable *ht, KeyType key);

//根据key删除
int HashDelete(HashTable *ht, KeyType key);

//判空
int HashEmpty(HashTable *ht);

//求哈希表的大小
int HashSize(HashTable *ht);

//销毁
void HashDestroy(HashTable *ht);

//打印
void HashShow(HashTable *ht);

//创建ValueStruc结构体
ValueStruc CreateValue(char *name, char *num, int score);

//显示指令菜单
void ShowMenu(void);

//按键检测输入
int KeyInput(void); 

//指令选择
void Select(int KeyInput, HashTable *ht);

#endif
