#include "map.h"
#include "debug.h"
#include "utils.h"
#include <stdio.h>

Result map_load_from_csv(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (!file)
    {
        char err[256];
        snprintf(err, sizeof(err), "could not open file: %s", file_path);
        return (Result){.value = nullptr, .err = err};
    }

    debug_log("Map file %s loaded successfully");
    return (Result){.value = (Map *){}, .err = nullptr};
}
