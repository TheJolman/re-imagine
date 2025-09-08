# Memory Management

This project uses a custom memory allocator that wraps `malloc` and `free` and stores all pointers
in a linked list. At program exit (whether it exits normally or via an error), all allocated
memory is freed.

---
**Therefore:**
- Use `heap_list.malloc()` and `heap_list.free()` instead of `malloc` and `free`
  when working with heap memory. They're used the same way as the functions they wrap.
- If you allocate memory for something that can exist for the entire lifetime of the program,
  you don't need to worry about manually freeing it.
- When handling an unrecoverable error, you don't need to manually free any memory. Just let the
  program exit, and since `heap_list.free_all` is registered with `atexit()`, everything will
  get cleaned up automatically.
