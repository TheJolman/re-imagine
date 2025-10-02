#include "stack.h"
#include "utils.h"

#include <stddef.h>

Stack *stack_create(size_t capacity)
{
    if (capacity == 0)
    {
        return nullptr;
    }

    Stack *stack = heap_list.malloc(sizeof(Stack));
    if (stack == nullptr)
    {
        return nullptr;
    }

    stack->items = heap_list.malloc(sizeof(void *) * capacity);
    if (stack->items == nullptr)
    {
        heap_list.free(stack);
        return nullptr;
    }

    stack->capacity = capacity;
    stack->top = -1;

    return stack;
}

void stack_destroy(Stack *stack)
{
    if (stack != nullptr)
    {
        if (stack->items != nullptr)
        {
            heap_list.free(stack->items);
        }
        heap_list.free(stack);
    }
}

bool stack_push(Stack *stack, void *item)
{
    if (stack == nullptr || stack_is_full(stack))
    {
        return false;
    }

    stack->top++;
    stack->items[stack->top] = item;
    return true;
}

void *stack_pop(Stack *stack)
{
    if (stack == nullptr || stack_is_empty(stack))
    {
        return nullptr;
    }

    void *item = stack->items[stack->top];
    stack->top--;
    return item;
}

void *stack_peek(const Stack *stack)
{
    if (stack == nullptr || stack_is_empty(stack))
    {
        return nullptr;
    }

    return stack->items[stack->top];
}

bool stack_is_empty(const Stack *stack)
{
    if (stack == nullptr)
    {
        return true;
    }
    return stack->top == -1;
}

bool stack_is_full(const Stack *stack)
{
    if (stack == nullptr)
    {
        return false;
    }
    return stack->top == (int)stack->capacity - 1;
}
