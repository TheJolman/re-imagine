#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief A generic fixed-size stack for holding void pointers.
 */
typedef struct
{
    void **items;
    int top;
    size_t capacity;
} Stack;

/**
 * @brief Creates a new stack with a given capacity.
 *
 * @param capacity The maximum number of items the stack can hold.
 * @return A pointer to the newly created stack, or nullptr if memory allocation fails.
 * @note The stack itself and its internal buffer are allocated on the heap and must be freed
 *       using stack_destroy.
 */
Stack *stack_create(size_t capacity);

/**
 * @brief Destroys a stack and frees its memory.
 *
 * @param stack The stack to destroy.
 * @note This does not free the memory of the items that were stored in the stack.
 */
void stack_destroy(Stack *stack);

/**
 * @brief Pushes an item onto the top of the stack.
 *
 * @param stack The stack.
 * @param item The void pointer to push.
 * @return true if the item was pushed successfully, false if the stack is full.
 */
bool stack_push(Stack *stack, void *item);

/**
 * @brief Pops an item from the top of the stack.
 *
 * @param stack The stack.
 * @return The item from the top of the stack, or nullptr if the stack is empty.
 */
void *stack_pop(Stack *stack);

/**
 * @brief Returns the item at the top of the stack without removing it.
 *
 * @param stack The stack.
 * @return The item at the top of the stack, or nullptr if the stack is empty.
 */
void *stack_peek(const Stack *stack);

/**
 * @brief Checks if the stack is empty.
 *
 * @param stack The stack.
 * @return true if the stack is empty, false otherwise.
 */
bool stack_is_empty(const Stack *stack);

/**
 * @brief Checks if the stack is full.
 *
 * @param stack The stack.
 * @return true if the stack is full, false otherwise.
 */
bool stack_is_full(const Stack *stack);