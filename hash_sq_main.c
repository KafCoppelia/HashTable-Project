/**
* @file hash_sq_main.c
* @author Ziru Pan
* @version 1.2
* @date 2021/6/16
* @brief This file includes functions and main function.
*/
#include "hash_sq_utils.h"

/**
* @brief Hash function.
* @param Key
* @return Offset calculated by hash function.
*/
int HashFunction(KeyType key)
{
    return key % HashMaxSize;
}

/**
* @brief Initialization of HashTable.
* @param HashTable*
* @param HashFunc
*/
void HashInit(HashTable *ht, HashFunc func)
{
    if (ht == NULL)
        return;
    ht->size = 0;
    ht->func = func;
    ht->data = (HashElem *)malloc(HashMaxSize * sizeof(HashElem));
    if (!ht->data)
        exit(0);
    int i;
    ValueStruc *v;
    for (i = 0; i < HashMaxSize; i++)
    {
        ht->data[i].key = -1;
        v = (ValueStruc *)malloc(sizeof(ValueStruc));
        ht->data[i].value = *v;
        ht->data[i].state = EMPTY;
    }
    printf("Initialized Successfully!\n");
}

/**
* @brief Destroy HashTable.
* @param HashTable*
*/
void HashDestroy(HashTable *ht)
{
    if (ht->func == NULL)
    {
        printf("Initialize a HashTable FIRST!\n");
        return;
    }
    ht->size = 0;
    ht->func = NULL;
    ht->data = NULL;
    printf("Destroyed Successfully!\n");
}

/**
* @brief Insert data into HashTable given the HashTable, key and value structure.
* @param HashTable*
* @param Key
* @param ValueStruc
* @return 0 means inserting failed.1 means successful. 
*/
int HashInsert(HashTable *ht, KeyType key, ValueStruc value)
{
    if (ht->func == NULL || ht->size >= LoadFactor * HashMaxSize) //表满则插入失败
    {
        printf("Insertion failed!\n");
        return 0;
    }
    int offset = ht->func(key);
    while (1)
    {
        // 查找状态不为VALUE节点
        if (ht->data[offset].state != VALUE)
        {
            ht->data[offset].key = key;
            ht->data[offset].value = value;
            ht->data[offset].state = VALUE;
            ht->size++;
            printf("Inserted successfully!\n");
            return 1;
        }
        else if (ht->data[offset].state == VALUE && ht->data[offset].key == key)
        {
            //VALUE且key相同，插入失败，规定插入失败不覆盖原有值
            printf("Insertion failed!Key value conflict!\n");
            return 0;
        }
        //key不同，则线性探测
        else
        {
            offset++;
            offset = (offset >= LoadFactor * HashMaxSize) ? 0 : offset;
        }
    }
    printf("Inserted successfully!\n");
    return 1;
}

/**
* @brief Delete data into HashTable given the HashTable and key.
* @param HashTable*
* @param Key
* @return 0 means deletion failed.1 means successful. 
*/
int HashDelete(HashTable *ht, KeyType key)
{
    if (ht->func == NULL || ht->size == 0)
    {
        printf("Deletion failed!\n");
        return 0;
    }
    int offset = ht->func(key);
    //记录初始offset
    int orig_offset = offset;
    while (ht->data[offset].state != EMPTY)
    {
        //将状态置DELETED，视为已删除
        if (ht->data[offset].key == key && ht->data[offset].state == VALUE)
        {
            ht->data[offset].state = DELETED;
            ht->size--;
            printf("Deleted successfully!\n");
            return 1;
        }
        //key不相等，线性探测，直到该元素下标为EMPTY
        else
        {
            offset++;
            offset = (offset >= LoadFactor * HashMaxSize) ? 0 : offset;
        }
        //所探测的节点均不为VALUE，说明没找到，返回NULL
        if (orig_offset == offset)
        {
            printf("Deletion failed!Not such a KEY!\n");
            return 0;
        }
    }
}

/**
* @brief Search data into HashTable given the HashTable and key.
* @param HashTable*
* @param Key
* @return NULL means searching failed.A successful search will return the adderess of HashElem. 
*/
HashElem *HashSearch(HashTable *ht, KeyType key)
{
    if (ht->func == NULL || ht->size == 0)
    {
        printf("Searching failed!\n");
        return NULL;
    }
    //求offset
    int offset = ht->func(key);
    //记录初始offset
    int orig_offset = offset;
    while (ht->data[offset].state != EMPTY)
    {
        //key相等，返回节点结构体指针
        if (ht->data[offset].key == key && ht->data[offset].state == VALUE)
        {
            printf("Searched successfully!\n");
            return &ht->data[offset];
        }
        //key不相等，线性探测
        else
        {
            offset++;
            offset = (offset >= LoadFactor * HashMaxSize) ? 0 : offset;
        }
        //所探测的节点均不为VALUE，说明没找到，返回NULL
        if (orig_offset == offset)
        {
            printf("Searching failed!Not such a KEY!\n");
            return NULL;
        }
    }
}

/**
* @brief Check if the HashTable is empty.
* @param HashTable*
* @return 1 means YES while 0 means NO.
*/
int HashEmpty(HashTable *ht)
{
    if (ht->func == NULL)
        return 1;
    else
        return (ht->size == 0) ? 1 : 0;
}

/**
* @brief Get the size of HashTable.
* @param HashTable*
* @return Size of the HashTable.
*/
int HashSize(HashTable *ht)
{
    if (ht->func == NULL)
        return 0;
    else
        return ht->size;
}

/**
* @brief Print all the details of data stored in the HashTable whose state is NOT EMPTY.
* @param HashTable*
*/
void HashShow(HashTable *ht)
{
    if (ht->func == NULL || ht->size == 0)
    {
        printf("Display failed!Check the HashTable please!\n");
        return;
    }
    int i;
    printf("=====Printing HashTable=====\n");
    for (i = 0; i < HashMaxSize; i++)
    {
        if (ht->data[i].state != EMPTY)
        {
            printf("[%d] Key=%d Name=%s Num=%s Score=%d State=%d\n",
                   i, ht->data[i].key, ht->data[i].value.name, ht->data[i].value.num,
                   ht->data[i].value.score, ht->data[i].state);
        }
    }
}

/**
* @brief Create value structure.
* @param string
* @param string
* @param int
* @return ValueStruc.
*/
ValueStruc CreateValue(char *name, char *num, int score)
{
    ValueStruc *v;
    v = (ValueStruc *)malloc(sizeof(ValueStruc));
    if (!v)
        exit(0);
    strcpy(v->name, name);
    strcpy(v->num, num);
    v->score = score;
    return *v;
}

/**
* @brief Show the command menu.
*/
void ShowMenu()
{
    printf(
        "|=============Welcome=============|\n"
        "|---------------------------------|\n"
        "|->1:Initialize HashTable         |\n"
        "|->2:Insert Data                  |\n"
        "|->3:Search Data                  |\n"
        "|->4:Delete Data                  |\n"
        "|->5:Print HashTable              |\n"
        "|->6:Empty?                       |\n"
        "|->7:Size                         |\n"
        "|->8:Destroy                      |\n"
        "|->9:Exit                         |\n"
        "|->0:Command Menu                 |\n"
        "|---------------------------------|\n");
    printf("Please input a command：");
}

/**
* @brief Check if the key input is legal and return.
* @return The key input by user.
*/
int KeyInput()
{
    int choice, confirm;
    scanf("%d", &choice);
    while (1)
    {
        while ((confirm = getchar()) != '\n') //用户再次输入空格键才表示其真正确认
            continue;
        //输入检测
        if (choice < 0 || choice > 9)
        {
            printf("Your command '%d' is illegal!Please input again:", choice);
            scanf(" %d", &choice);
        }
        else
            return choice;
    }
}

/**
* @brief Given the key input operate the corresponding function.
* @param int 
* @param HashTable*
*/
void Select(int choice, HashTable *ht)
{
    switch (choice)
    {
        case 0:
        {
            ShowMenu();
            break;
        }

        case 1:
        {
            HashInit(ht, HashFunction);
            break;
        }

        case 2:
        {
            if (ht->func == NULL)
                printf("Initialize a HashTable FIRST!\n");
            else
            {
                int key, score;
                char name[10], num[10];
                ValueStruc v;
                printf("=====Creating Value Structure=====\n");
                printf("Input the KEY：");
                scanf("%d", &key);
                printf("Input data:Name Num Score(split by a space)：");
                scanf("%s %s %d", name, num, &score);
                getchar();
                v = CreateValue(name, num, score);
                HashInsert(ht, key, v);
            }
            break;
        }

        case 3:
        {
            if (ht->func == NULL)
                printf("Initialize a HashTable FIRST!\n");
            else
            {
                int key;
                HashElem *tofind;
                printf("=====Searching=====\n");
                printf("Input the KEY：");
                scanf("%d", &key);
                tofind = HashSearch(ht, key);
                if (tofind)
                {
                    printf("======Details=====\n");
                    printf("Key:%d State:%d\n", tofind->key, tofind->state);
                    printf("Name:%s Num:%s Score:%d\n", tofind->value.name, tofind->value.num, tofind->value.score);
                }
            }
            break;
        }

        case 4:
        {
            if (ht->func == NULL)
                printf("Initialize a HashTable FIRST!\n");
            else
            {
                int key;
                printf("=====Deleting=====\n");
                printf("Input the KEY：");
                scanf("%d", &key);
                HashDelete(ht, key);
            }
            break;
        }

        case 5:
        {
            HashShow(ht);
            break;
        }

        case 6:
        {
            if (HashEmpty(ht))
                printf("HashTable is empty.\n");
            else
                printf("HashTable is NOT empty.\n");
            break;
        }

        case 7:
        {
            printf("Size of HashTable is %d.\n", HashSize(ht));
            break;
        }

        case 8:
        {
            HashDestroy(ht);
            break;
        }
    }
}

/**
* @brief Main function.
* @return 0 means a normal abortion.
*/
int main()
{
    int choice;
    HashTable ht;
    ht.func = NULL;
    ShowMenu();
    while ((choice = KeyInput())!=9)
        Select(choice, &ht);
    printf("Exiting...\n");
    Sleep(1);
    return 0;
}