#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef enum
{
    STRING,
    INTEGER,
    FLOAT,
    CHAR
} DataType;

typedef struct Node
{
    void *key, *value;
    DataType key_type, value_type;
    struct Node *next;
} Node;

typedef struct
{
    Node *buckets[TABLE_SIZE];
} HashTable;

HashTable *table;

// Hash function
unsigned long hash(void *key, DataType type)
{
    if (type == STRING)
    {
        unsigned long hash = 5381;
        for (char *str = (char *)key; *str; str++)
            hash = ((hash << 5) + hash) + *str;
        return hash % TABLE_SIZE;
    }
    return (type == INTEGER ? *(int *)key : (unsigned long)(*(float *)key * 1000)) % TABLE_SIZE;
}

// Create node
Node *create_node(void *key, void *value, DataType key_type, DataType value_type)
{
    Node *node = malloc(sizeof(Node));
    node->key = key_type == STRING ? strdup((char *)key) : malloc(sizeof(double));
    node->value = value_type == STRING ? strdup((char *)value) : malloc(sizeof(double));
    memcpy(node->key, key, key_type == INTEGER ? sizeof(int) : sizeof(double));
    memcpy(node->value, value, value_type == INTEGER ? sizeof(int) : sizeof(double));
    node->key_type = key_type, node->value_type = value_type, node->next = NULL;
    return node;
}

// Insert function
void insert(void *key, void *value, DataType key_type, DataType value_type)
{
    unsigned long index = hash(key, key_type);
    Node *node = create_node(key, value, key_type, value_type);
    node->next = table->buckets[index];
    table->buckets[index] = node;
}

// Search function
void *search(void *key, DataType key_type, DataType *found_value_type)
{
    Node *node = table->buckets[hash(key, key_type)];
    while (node)
    {
        int found = (key_type == STRING)    ? strcmp((char *)node->key, (char *)key) == 0
                    : (key_type == INTEGER) ? *(int *)node->key == *(int *)key
                                            : *(float *)node->key == *(float *)key;
        if (found)
        {
            *found_value_type = node->value_type;
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

// Free table
void free_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *node = table->buckets[i];
        while (node)
        {
            Node *temp = node;
            node = node->next;
            free(temp->key), free(temp->value), free(temp);
        }
    }
    free(table);
}

// Main function
int main()
{
    table = calloc(1, sizeof(HashTable));

    char *key1 = "apple";
    int key2 = 123, value1 = 10;
    float key3 = 45.67f, value2 = 99.99f;
    char value3 = 'Z';

    insert(key1, &value1, STRING, INTEGER);
    insert(&key2, &value2, INTEGER, FLOAT);
    insert(&key3, &value3, FLOAT, CHAR);

    DataType found_value_type;
    int *result1 = (int *)search(key1, STRING, &found_value_type);
    if (result1 && found_value_type == INTEGER)
        printf("Value for 'apple': %d\n", *result1);

    float *result2 = (float *)search(&key2, INTEGER, &found_value_type);
    if (result2 && found_value_type == FLOAT)
        printf("Value for '123': %.2f\n", *result2);

    char *result3 = (char *)search(&key3, FLOAT, &found_value_type);
    if (result3 && found_value_type == CHAR)
        printf("Value for '45.67': %c\n", *result3);

    free_table();
    return 0;
}
