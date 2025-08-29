#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    size_t size;
    size_t data_size;
    void (*destroy)(void *);
    void (*print)(const void *); // probably don't need this method
} List;

List list_init(size_t data_size, void (*destroy)(void *), void (*print)(const void *))
{
    return (List){
        .head = nullptr, .size = 0, .data_size = data_size, .destroy = destroy, .print = print};
}

size_t list_get_size(const List *list) { return list ? list->size : 0; }

bool list_is_empty(const List *list) { return !list || !list->head; }

Node *node_create(const void *data, size_t data_size)
{
    if (!data)
        return nullptr;

    Node *node = malloc(sizeof(Node));
    if (!node)
        return nullptr;

    node->data = malloc(data_size);
    if (!node->data)
    {
        free(node);
        return nullptr;
    }

    memcpy(node->data, data, data_size);
    node->next = nullptr;
    return node;
}

void node_destroy(Node *node, void (*destroy)(void *))
{
    if (!node)
        return;
    if (destroy)
    {
        destroy(node->data);
    }

    free(node->data);
    free(node);
}

bool list_push_front(List *list, const void *data)
{
    if (!list || !data)
        return false;

    Node *new_node = node_create(data, list->data_size);
    if (!new_node)
        return false;

    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    return true;
}

bool list_push_back(List *list, const void *data)
{
    if (!list || !data)
        return false;

    Node *new_node = node_create(data, list->data_size);
    if (!new_node)
        return false;

    if (!list->head)
    {
        list->head = new_node;
    }
    else
    {
        Node *current = list->head;

        while (current->next)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    return true;
}

bool list_pop_front(List *list)
{
    if (list_is_empty(list))
        return false;

    Node *temp = list->head;
    list->head = list->head->next;
    node_destroy(temp, list->destroy);
    list->size--;
    return true;
}

bool list_pop_back(List *list)
{
    if (list_is_empty(list))
        return false;

    // Handle single item case
    if (list->head->next == nullptr) {
        node_destroy(list->head, list->destroy);
        list->head = nullptr;
        list->size--;
        return true;
    }

    // Find second-to-last node
    Node *prev = list->head;
    while (prev->next->next != nullptr) {
        prev = prev->next;
    }

    // Destroy last node and update pointer
    node_destroy(prev->next, list->destroy);
    prev->next = nullptr;
    list->size--;
    
    return true;
}

bool list_insert(List *list, size_t index, const void *data)
{
    if (!list || !data || index > list->size)
        return false;

    if (index == 0)
    {
        return list_push_front(list, data);
    }

    Node *new_node = node_create(data, list->data_size);
    if (!new_node)
        return false;

    Node *current = list->head;
    for (size_t i = 0; i < index - 1; i++)
    {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
    return true;
}

void clear_list(List *list)
{
    if (!list)
        return;

    while (list->head)
    {
        Node *temp = list->head;
        list->head = list->head->next;
        node_destroy(temp, list->destroy);
    }
    list->size = 0;
}
