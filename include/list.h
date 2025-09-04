/**
 * @file list.h
 * @brief Generic linked list implementation with function pointers
 */

#pragma once

#include <stdbool.h> // For bool type
#include <stddef.h>  // For size_t
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

List list_init(size_t data_size, void (*destroy)(void *), void (*print)(const void *));
size_t list_get_size(const List *list);
bool list_is_empty(const List *list);
Node *node_create(const void *data, size_t data_size);
void node_destroy(Node *node, void (*destroy)(void *));
bool list_push_front(List *list, const void *data);
bool list_push_back(List *list, const void *data);
bool list_pop_front(List *list);
bool list_pop_back(List *list);
bool list_insert(List *list, size_t index, const void *data);
bool list_delete(List *list, const void *data);
void clear_list(List *list);
