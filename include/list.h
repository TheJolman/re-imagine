/**
 * @file list.h
 * @brief Generic linked list implementation with function pointers
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Node structure for linked list
 */
typedef struct Node
{
    void *data;        ///< Pointer to node data
    struct Node *next; ///< Pointer to next node
} Node;

/**
 * @brief Generic linked list structure
 */
typedef struct
{
    Node *head;                  ///< Pointer to first node
    size_t size;                 ///< Number of nodes in list
    size_t data_size;            ///< Size of each data element
    void (*destroy)(void *);     ///< Function to destroy data elements
    void (*print)(const void *); ///< Function to print data elements
} List;

/**
 * @brief Initializes a new list
 *
 * @param data_size Size of each data element
 * @param destroy Function to destroy data elements (can be NULL)
 * @param print Function to print data elements (can be NULL)
 * @return Initialized list structure
 */
List list_init(size_t data_size, void (*destroy)(void *), void (*print)(const void *))
{
    return (List){
        .head = nullptr, .size = 0, .data_size = data_size, .destroy = destroy, .print = print};
}

/**
 * @brief Gets the size of the list
 *
 * @param list Pointer to the list
 * @return Number of elements in the list
 */
size_t list_get_size(const List *list) { return list ? list->size : 0; }

/**
 * @brief Checks if the list is empty
 *
 * @param list Pointer to the list
 * @return true if list is empty, false otherwise
 */
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
        destroy(node->data);

    // if (node->data)
    //     free(node->data);
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
    if (list->head->next == nullptr)
    {
        node_destroy(list->head, list->destroy);
        list->head = nullptr;
        list->size--;
        return true;
    }

    // Find second-to-last node
    Node *prev = list->head;
    while (prev->next->next != nullptr)
    {
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

bool list_delete(List *list, const void *data)
{
    if (list_is_empty(list) || !data)
    {
        return false;
    }

    Node *current = list->head;
    Node *prev = nullptr;

    while (current != nullptr && memcmp(current->data, data, list->data_size) != 0)
    {
        prev = current;
        current = current->next;
    }

    if (current == nullptr)
    {
        return false; // Not found
    }

    if (prev == nullptr)
    {
        list->head = current->next; // Deleting head
    }
    else
    {
        prev->next = current->next;
    }

    node_destroy(current, list->destroy);
    list->size--;

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
