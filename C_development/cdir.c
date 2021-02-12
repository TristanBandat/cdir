#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#define LEN_FLAG_ARR 1              // number of flags
#define LEN_ARGS_ARR LEN_FLAG_ARR   // use this name for all use cases where you don't refer directly to the flag array
#define MAX_PATH_LEN 1024
#define MAX_DIR_NUMBER 512
#define MAX_DIR_NAME_LEN 256
#define MAX_DIR_NAME_SEQ_LEN MAX_DIR_NAME_LEN
#define MAX_STR_NUM_LEN 16

// structure for directories with correct formatting
struct directory {
    char name[MAX_DIR_NAME_LEN];
    int occurrence;
    int num_zeros;
    int highest_number;
};

int set_flags(int, char**, int*, const char*);
void update_flag(char flag, int* flag_arr, const char* args_arr);
void get_cwd(char *cwd_arr);
int get_directories(struct directory*, int, struct dirent*);
void print_help();
void create_dir(struct directory, char*);

int main(int argc, char **argv) {
    // array with all flags
    int flag_arr[LEN_FLAG_ARR] = {0};
    // array with all arguments
    const char args_arr[LEN_ARGS_ARR] = {'h'};
    // array for storing the current working directory (cwd)
    char cwd_arr[MAX_PATH_LEN];
    // variable to go through all directories and files in cwd
    DIR *dr;
    // pointer to directory entry
    struct dirent *de;
    // array of all directories
    struct dirent dirs[MAX_DIR_NUMBER];
    // number of directories in cwd
    int num_dirs = 0;
    // current index of the next free slot in 'dirs[]'
    int dirs_index = 0;
    // directories to be ignored by default
    char ignored_dirs[2][3] = {".", ".."};
    // correct formatted directories in cwd
    struct directory considered_directories[MAX_DIR_NUMBER];
    // index of the next free position in 'considered_directories'
    int considered_directories_index = 0;
    // index of the considered directory with the highest occurrence
    int con_dir_occ_index = 0;
    // there exists a directory with given name from args
    bool dir_found = false;
    // directory name given as arg
    char given_dir_name[MAX_DIR_NAME_LEN];

    // get the current working directory
    get_cwd(cwd_arr);
    // open de current directory
    dr = opendir(cwd_arr);
    // check if the pointer is valid
    if (dr == NULL) {
        printf("Unable to open current directory.");
        exit(-1);
    }

    // get all directories from cwd
    while ((de = readdir(dr)) != NULL) {
        if (de->d_type == DT_DIR) {
            if ((strcmp(de->d_name, ignored_dirs[0]) == 0) ||
                (strcmp(de->d_name, ignored_dirs[1]) == 0)) {
                continue;
            }
            // save directory pointer in array
            dirs[dirs_index] = *de;
            // increment counter
            num_dirs++;
            // increment index
            dirs_index++;
        }
    }

    // set the flags
    if (set_flags(argc, argv, flag_arr, args_arr)) {
        // Something went wrong - abort
        printf("Exit\n");
        return -1;
    }

    // check if the user wants help
    if (flag_arr[0]) {
        print_help();
        return 0;
    }

    // get all considered directories
    considered_directories_index = get_directories(considered_directories, num_dirs, dirs);

    // no directory or arg found
    if ((considered_directories_index == 0) && (optind >= argc)) {
        printf("No folder(s) found.\n");
        return 0;
    }

    // Check command line args for given directory name
    // TODO: append here
    if (optind >= argc) {
        // no directory name given
        // get the directory with the highest occurrence
        for (int i = 0; i < considered_directories_index; i++) {
            if (considered_directories[con_dir_occ_index].occurrence < considered_directories[i].occurrence) {
                con_dir_occ_index = i;
            }
        }
        // create additional directory with given parameters
        create_dir(considered_directories[con_dir_occ_index], cwd_arr);
    } else {
        // directory name given as arg
        // append an underscore to the given name
        strcpy(given_dir_name, argv[optind]);
        strcat(given_dir_name, "_");

        // check for already existing directories
        for (int i = 0; i < considered_directories_index; i++) {
            if (strcmp(considered_directories[i].name, given_dir_name) == 0) {
                create_dir(considered_directories[i], cwd_arr);
                dir_found = true;
                break;
            }
        }

        // if there was no directory found -> create a new one
        if (!dir_found) {
            strcpy(considered_directories[considered_directories_index].name, given_dir_name);
            considered_directories[considered_directories_index].occurrence = 1;
            considered_directories[considered_directories_index].num_zeros = 0;
            considered_directories[considered_directories_index].highest_number = -1;
            considered_directories_index++;
            create_dir(considered_directories[considered_directories_index-1], cwd_arr);
        }
    }

    // close directory
    closedir(dr);

    printf("done.\n");
    return 0;
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
        if (c == '?') {
            // an unknown option/character appeared
            if (isprint (optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr,
                        "Unknown option character `\\x%x'.\n", optopt);
            return 1;
        } else {
            if (c == args_arr[0]) {
                // updates the flags array at the position of given flag
                update_flag((char)c, flag_arr, args_arr);
            } else {
                // unknown argument
                return 1;
            }
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

int get_directories(struct directory *considered_directories, int num_dirs, struct dirent *dirs)
/*
 * WELCOME TO THE JUNGLE!
 * In this function are still some comments missing.
 *
 * This function filters all given directories and updates the directory structure
 * 'considered_directories'. Also it returns the next free slot in the struct array.
 *
 * Please be careful when changing code in here.
 * It may result in some very awkward bugs!
 * And this function is not so nice to debug... Thanks! -tb
 */
{
    // variable to go through all dirs (runner)
    struct dirent current_dir;
    // variable to go through a string (runner)
    char current_char;
    // variable is true if there exists appropriate formatting after a underscore
    bool is_valid_number = false;
    // index of the next free position in 'considered_directories'
    int considered_directories_index = 0;
    // converted number given in 'number_sequence'
    int number_sequence_int;
    // reconverted number to string from 'number_sequence_int'
    char number_sequence_int_char[MAX_STR_NUM_LEN] = {};
    // number of leading 0s in 'number_sequence'
    int num_zeros_number_sequence;
    // directory name without the number
    char name_sequence[MAX_DIR_NAME_SEQ_LEN] = {};
    // index of the next free position in 'name_sequence'
    int name_seq_index = 0;
    // found name sequence in considered directory array
    bool name_seq_exists = false;
    // sequence of valid numbers as string
    char number_sequence[MAX_STR_NUM_LEN] = {};
    // index of the next free position in 'number_sequence'
    int number_seq_index = 0;

    // check all directories for the correct formatting
    // go through all directories
    for (int i = 0; i < num_dirs; i++) {
        current_dir = dirs[i];
        for (int j = 0; current_dir.d_name[j] != '\0'; j++) {
            // get the next character from the directory name
            current_char = current_dir.d_name[j];
            // check if the current characters are valid numbers
            if (is_valid_number) {
                if ((current_char >= '0') && (current_char <= '9')) {
                    number_sequence[number_seq_index] = current_char;
                    number_seq_index++;
                } else {
                    // incorrect formatting - delete number sequence
                    strcat(name_sequence, number_sequence);
                    name_seq_index += number_seq_index;
                    name_sequence[name_seq_index] = current_char;
                    name_seq_index++;
                    memset(number_sequence,0,MAX_STR_NUM_LEN);
                    number_seq_index = 0;
                    is_valid_number = false;
                }
            } else {
                is_valid_number = false;
                // save char in 'name_sequence'
                name_sequence[name_seq_index] = current_char;
                name_seq_index++;
            }
            // check if the current character is an underscore and the next character is a number
            if ((current_char == '_') && (current_dir.d_name[j+1] >= '0') && (current_dir.d_name[j+1] <= '9')) {
                is_valid_number = true;
            }
        }
        // check for leading 0s
        if (number_seq_index > 0) {
            number_sequence_int = atoi(number_sequence);
            sprintf(number_sequence_int_char, "%i", number_sequence_int);
            num_zeros_number_sequence = strlen(number_sequence) - strlen(number_sequence_int_char);
            for (int j = 0; j < considered_directories_index; j++) {
                // check if the name already exists
                if (strcmp(considered_directories[j].name, name_sequence) == 0 &&
                    (num_zeros_number_sequence == considered_directories[j].num_zeros)) {
                    considered_directories[j].occurrence++;
                    if (number_sequence_int > considered_directories[j].highest_number)
                        considered_directories[j].highest_number = number_sequence_int;
                    name_seq_exists = true;
                    break;
                }
            }
            // if the directory does not already exist -> add it to the array
            if (!name_seq_exists) {
                strcpy(considered_directories[considered_directories_index].name, name_sequence);
                considered_directories[considered_directories_index].occurrence = 1;
                considered_directories[considered_directories_index].num_zeros = num_zeros_number_sequence;
                considered_directories[considered_directories_index].highest_number = number_sequence_int;
                considered_directories_index++;
            }
            name_seq_exists = false;
        }

        // empty the strings and reset the indices
        memset(number_sequence,0,MAX_STR_NUM_LEN);
        number_seq_index = 0;
        memset(name_sequence,0,MAX_DIR_NAME_SEQ_LEN);
        name_seq_index = 0;
        is_valid_number = false;
    }

    return considered_directories_index;
}

void print_help()
/*
 * Display the help message.
 */
{
    printf("HELP\n----\n");
    printf("cdir [argument]\n\n");

    printf("When you type only the function name the program will search for a folder structure\n");
    printf("that looks like [folder_name]_[number]. If there are more than one available it will\n");
    printf("choose the one which appears the most. Then the program looks for the highest number\n");
    printf("of the folder structure, increments it by 1 and creates "
           "a new directory with the\nnew folder name.\n\n");

    printf("If you want to choose the folder name, simply type in the preferred name as\n");
    printf("an argument. The program will search for the highest number in the folder structure with\n");
    printf("that keyword, increments it by 1 and creates a new directory with the new folder name.\n");
    printf("If there exists no directory in the current working directory, the program will start with\n");
    printf("0 as the highest number and proceed like normal.\n\n");

    printf("To get this help statement displayed use the argument '-h'.\n\n\n");
}

void create_dir(struct directory dir, char *cwd_arr)
/*
 * Puts directory name and path together and creates the directory.
 * If an error while creating occurs, the program exits with status -1.
 */
{
    char path_dir_name[MAX_DIR_NAME_LEN] = {};
    char str[MAX_STR_NUM_LEN] = {};

    // put the directory name together
    strcpy(path_dir_name, cwd_arr);
    strcat(path_dir_name, "/");
    strcat(path_dir_name, dir.name);
    for (int i = 0; i < dir.num_zeros; i++)
        strcat(path_dir_name, "0");
    sprintf(str, "%i", dir.highest_number+1);
    strcat(path_dir_name, str);

    // print the finished directory path + name
    printf("Creating directory %s\n", path_dir_name);
    // create directory
    if (mkdir(path_dir_name, 0700) == -1) {
        printf("ERROR while creating directory.\n\n");
        exit(-1);
    }
}
