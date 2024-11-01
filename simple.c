#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node
{
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct
{
    Node *buckets[TABLE_SIZE];
} HashTable;
HashTable *table;

unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    while (*str)
    {
        hash = ((hash << 5) + hash) + *str++; // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

HashTable *create_table()
{
    return (HashTable *)calloc(1, sizeof(HashTable));
}

Node *create_node(const char *key, int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void insert(const char *key, int value)
{
    unsigned long index = hash(key);
    Node *new_node = create_node(key, value);
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

int search(const char *key)
{
    for (Node *node = table->buckets[hash(key)]; node; node = node->next)
    {
        if (strcmp(node->key, key) == 0)
            return node->value;
    }
    return -1;
}

void free_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *node = table->buckets[i];
        while (node)
        {
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table);
}

int main()
{
    table = create_table();

    insert("apple", 1);
    insert("banana", 2);
    insert("grape", 3);

    printf("Value for 'apple': %d\n", search("apple"));
    printf("Value for 'banana': %d\n", search("banana"));
    printf("Value for 'grape': %d\n", search("grape"));
    printf("Value for 'orange': %d\n", search("orange"));

    free_table();

    return 0;
}
