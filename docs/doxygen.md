# In-Code Documentation

This project uses the **Doxygen** standard for documenting source code. This makes it easier
for new developers to understand what's going on and makes our language servers more useful.

## Functions
Document public, non-trivial functions with the following format. You don't need to include
everything, just what you think is necessary.
```c
/**
 * @brief Calculates the sum of two integers.
 *
 * This function takes two integer arguments and returns their sum.
 * It handles potential overflow by returning an error status.
 *
 * @param a The first integer operand.
 * @param b The second integer operand.
 * @param[out] result Pointer to store the sum.
 * @return 0 on success, -1 on overflow.
 * @note This is a simple example note.
 */
int add(int a, int b, int* result);
```

## Structs and Enums
Again, document public non-trivial data structures with the following format.
```c
/**
 * @brief Represents a 2D point with integer coordinates.
 */
typedef struct {
    int x; /**< The x-coordinate of the point. */
    int y; /**< The y-coordinate of the point. */
} Point;
```

## Common Doxygen tags
- `@brief`: One-line summary
- `@param <name>`: Describes a function parameter
- `@return`: Describes the function's return value
- `@note`: Add extra notes
- `@see`: Create cross-reference to other code

## What not to do
Please do not feel the need to document non-public, self explanatory code or very basic
functions. Variable names should be descriptive enough to where it's obvious what they contain.

## Using Doxygen
Run `doxygen` in the project root. If you're on windows, you will need to install doxygen
before you can do this. Then open `docs/html/index.html` in your browser.

For more information, see the [Doxygen manual](https://www.doxygen.nl/manual/docblocks.html).
