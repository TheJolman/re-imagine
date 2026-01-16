#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

#ifndef GIT_VERSION
#define GIT_VERSION "unkown"
#endif

/**
 * @returns true if target matches short_arg or long_arg and false otherwise.
 *
 * If only short_arg or long_arg is needed, pass nullptr in place of the other.
 */
static bool _match_arg(const char *target, const char *short_arg, const char *long_arg) {
    return (short_arg && strcmp(target, short_arg) == 0 ||
            long_arg && strcmp(target, long_arg) == 0);
}

int main(int argc, char **argv) {
#ifdef DEBUG
    SetTraceLogLevel(LOG_DEBUG);
#else
    SetTraceLogLevel(LOG_INFO);
#endif

    // ----------- Command line argument parsing -----------
    for (int i = 1; i < argc; i++) {
        if (_match_arg(argv[i], "-v", "--version")) {
            printf("%s %s\n", argv[0], GIT_VERSION);
            exit(0);
        } else if (_match_arg(argv[i], "-h", "--help")) {
            printf("Usage: %s [-h | --help] [-v | --version]\n"
                   "Have fun!\n",
                   argv[0]);
            exit(0);
        } else {
            fprintf(stderr,
                    "Unrecognized argument. "
                    "Try '%s --help' for usage information.",
                    argv[0]);
            exit(1);
        }
    }

    int exit_code = game_run();
    exit(exit_code);
}
