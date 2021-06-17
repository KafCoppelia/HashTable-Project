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
#define HashMaxSize 10 //��ϣ������
#define LoadFactor 1 //��������LoadFactor

typedef int KeyType;
typedef int (*HashFunc)(KeyType key); //�ض����ϣ����

typedef enum State //���ڱ�ʾÿ��Ԫ�ص�״̬
{
    EMPTY,  //��
    VALUE,  //��ǰ��ֵ
    DELETED //��ǰ����ѱ�ɾ��
} State;

typedef struct ValueStruc   //����Ԫ��
{
    char name[10];  //����
    char num[10];   //ѧ��
    int score;      //����
} ValueStruc;

typedef struct HashElem //��ϣ������ݽڵ�
{
    KeyType key;
    ValueStruc value;
    State state;
} HashElem;

typedef struct HashTable //��ϣ��
{
    HashElem *data;
    int size;   //��ϣ��ߴ�
    HashFunc func;
} HashTable;

/*----��ϣ�����ز���----*/
//��ϣ����
int HashFunction(KeyType key);

//��ʼ��
void HashInit(HashTable *ht, HashFunc func);

//����
int HashInsert(HashTable *ht, KeyType key, ValueStruc value);

//����key����
HashElem *HashSearch(HashTable *ht, KeyType key);

//����keyɾ��
int HashDelete(HashTable *ht, KeyType key);

//�п�
int HashEmpty(HashTable *ht);

//���ϣ��Ĵ�С
int HashSize(HashTable *ht);

//����
void HashDestroy(HashTable *ht);

//��ӡ
void HashShow(HashTable *ht);

//����ValueStruc�ṹ��
ValueStruc CreateValue(char *name, char *num, int score);

//��ʾָ��˵�
void ShowMenu(void);

//�����������
int KeyInput(void); 

//ָ��ѡ��
void Select(int KeyInput, HashTable *ht);

#endif
