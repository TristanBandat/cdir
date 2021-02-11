#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define LEN_FLAG_ARR 2              // number of flags
#define LEN_ARGS_ARR LEN_FLAG_ARR   // use this name for all use cases where you don't refer directly to the flag array
#define MAX_PATH_LEN 1024
#define MAX_DIR_NUMBER 512
#define MAX_DIR_NAME_LEN 256
#define MAX_DIR_NAME_SEQ_LEN MAX_DIR_NAME_LEN
#define MAX_STR_NUM_LEN 16

// structure for directories with correct formatting
struct directory {
    char name[MAX_DIR_NAME_LEN];
    int number;
    int num_zeros;
};

int set_flags(int, char**, int*, const char*);
void update_flag(char flag, int* flag_arr, const char* args_arr);
void get_cwd(char *cwd_arr);

int main(int argc, char **argv) {
    
}

int set_flags(int argc, char **argv, int* flag_arr, const char* args_arr)
/*
 * This function sets all flags given by the command line arguments
 * and are in the arguments array 'args_arr' in the flag array 'flag_arr'.
 * Throws an error if an unknown flag occurred.
 */
{
    // Variable to go through all args
    int c;
    // prevent an error message from getopt()
    opterr = 0;
    // String with all args
    char all_args[LEN_ARGS_ARR + 1] = "";

    // save all args in the all_args array
    for (int i = 0; i < LEN_ARGS_ARR; i++) {
        all_args[i] = *(args_arr + i);
    }

    // go through the args
    while ((c = getopt (argc, argv, all_args)) != -1) {
        switch (c) {
            case 'b':
            case 's':
                // updates the flags array at the position of given flag
                update_flag((char)c, flag_arr, args_arr);
                break;
            case '?':
                // an unknown option/character appeared
                if (isprint (optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr,
                            "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                return 1;
        }
    }

    // all worked fine
    return 0;
}

void update_flag(char flag, int* flag_arr, const char* args_arr)
/*
 * This function updates the flag given by the variable 'flag'.
 * It takes one flag at a time and updates the state if the flag is defined in
 * the arguments array 'args_arr'.
 * The function runs through the possible args and if the flag is found, it
 * will set the value at the corresponding index to 1.
 */
{
    for (int i = 0; i < LEN_ARGS_ARR; i++) {
        if (flag == *(args_arr + i))
            *(flag_arr + i) = 1;
    }
}

void get_cwd(char *cwd_arr)
/*
 * Gets the current working directory (cwd) and saves it in the given cwd_arr.
 * The maximal path length is defined by the constant MAX_PATH_LEN.
 * If the path is larger than the constant defines, the function will raise an error.
 */
{
    int cwd_arr_size = sizeof(*cwd_arr) * MAX_PATH_LEN;
    if (getcwd(cwd_arr, cwd_arr_size) == NULL) {
        perror("get_cwd() error");
        exit(-1);
    }
}
