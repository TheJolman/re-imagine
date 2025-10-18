#include "mon.h"
#include "debug.h"
#include "raylib.h"
#include "utils.h"
#include <cjson/cJSON.h>
#include <stdio.h>
#include <string.h>

void load_mon_texture(Mon *mon, MonSpriteView textureType)
{
    char imagePath[256];
    if (!mon->name)
    {
        error_exit(1, "attempted to load texture of mon with no name");
    }
    snprintf(imagePath, sizeof(imagePath), "assets/monsters/%s/sprite.png", mon->name);

    switch (textureType)
    {
    case FRONT:
        mon->sprite.source = (Rectangle){0, 0, 1024, 1024};
        break;
    case BACK:
        mon->sprite.source = (Rectangle){1024, 0, 1024, 1024};
        break;
    }

    if (mon->sprite.texture.id > 0)
    {
        UnloadTexture(mon->sprite.texture);
    }

    Image image = LoadImage(imagePath);
    mon->sprite.texture = LoadTextureFromImage(image);
    UnloadImage(image);

    mon->sprite_view = textureType;
}

Result load_mon_data_from_json(Mon *mon)
{
    if (!mon || !mon->name)
    {
        return (Result){.value = nullptr, .err = "Invalid monster"};
    }

    char jsonPath[256];
    snprintf(jsonPath, sizeof(jsonPath), "assets/monsters/%s/default.json", mon->name);

    FILE *file = fopen(jsonPath, "r");
    if (!file)
    {
        return (Result){.value = nullptr, .err = "Failed to open JSON file"};
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate buffer and read file
    char *jsonContent = heap_list.malloc(fileSize + 1);
    if (!jsonContent)
    {
        fclose(file);
        return (Result){.value = nullptr, .err = "Out of memory"};
    }

    size_t bytesRead = fread(jsonContent, 1, fileSize, file);
    jsonContent[bytesRead] = '\0';
    fclose(file);

    // Parse JSON
    cJSON *root = cJSON_Parse(jsonContent);
    heap_list.free(jsonContent);

    if (!root)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        debug_log("JSON parse error: %s\n", error_ptr ? error_ptr : "unknown error");
        return (Result){.value = nullptr, .err = "Failed to parse JSON"};
    }

    // Parse base-stats
    cJSON *baseStats = cJSON_GetObjectItem(root, "base-stats");
    if (baseStats)
    {
        cJSON *hp = cJSON_GetObjectItem(baseStats, "hp");
        cJSON *attack = cJSON_GetObjectItem(baseStats, "attack");
        cJSON *defence = cJSON_GetObjectItem(baseStats, "defence");
        cJSON *speed = cJSON_GetObjectItem(baseStats, "speed");

        if (hp && cJSON_IsNumber(hp))
        {
            mon->health.max = (HitPoints)hp->valueint;
            mon->health.current = mon->health.max;
        }

        if (attack && cJSON_IsNumber(attack))
            mon->base_stats.attack = (uint32_t)attack->valueint;

        if (defence && cJSON_IsNumber(defence))
            mon->base_stats.defence = (uint32_t)defence->valueint;

        if (speed && cJSON_IsNumber(speed))
            mon->base_stats.speed = (uint32_t)speed->valueint;
    }

    // Parse stats-gained-on-level
    cJSON *statsGained = cJSON_GetObjectItem(root, "stats-gained-on-level");
    if (statsGained)
    {
        cJSON *attack = cJSON_GetObjectItem(statsGained, "attack");
        cJSON *defence = cJSON_GetObjectItem(statsGained, "defence");
        cJSON *speed = cJSON_GetObjectItem(statsGained, "speed");

        if (attack && cJSON_IsNumber(attack))
            mon->stats_gained_on_level.attack = (uint32_t)attack->valueint;

        if (defence && cJSON_IsNumber(defence))
            mon->stats_gained_on_level.defence = (uint32_t)defence->valueint;

        if (speed && cJSON_IsNumber(speed))
            mon->stats_gained_on_level.speed = (uint32_t)speed->valueint;
    }

    // TODO: Parse moves-learned-on-level

    cJSON_Delete(root);
    return (Result){.value = mon, .err = nullptr};
}

Result create_mon(char *name, unsigned level)
{
    Mon *mon = heap_list.malloc(sizeof(Mon));
    if (!mon)
    {
        return (Result){.value = nullptr, .err = "Out of memory"};
    }

    mon->name = heap_list.malloc(strlen(name) + 1);
    if (!mon->name)
    {
        heap_list.free(mon);
        return (Result){.value = nullptr, .err = "Out of memory"};
    }
    strcpy((char *)mon->name, name);

    mon->sprite = (Sprite){
        .texture = {0},
        .source = {0, 0, 0, 0},
        .rotation = 0.0f,
        .scale = 1.0f,
        .tint = WHITE,
    };
    mon->health = (Health){100, 100};
    mon->level = level;
    mon->base_stats = (Stats){0, 0, 0};
    mon->stats_gained_on_level = (Stats){0, 0, 0};
    // TODO: Initialize other values

    // Load data from JSON file
    Result jsonResult = load_mon_data_from_json(mon);
    if (jsonResult.err)
    {
        debug_log("Warning: Failed to load JSON data for %s: %s\n", name, jsonResult.err);
        // Continue with default values rather than failing completely
    }

    return (Result){.value = mon, .err = nullptr};
}

void destroy_mon(Mon *mon)
{
    if (mon->sprite.texture.id > 0)
    {
        UnloadTexture(mon->sprite.texture);
    }
    heap_list.free((char *)mon->name);
    heap_list.free(mon);
    mon = nullptr;
}
