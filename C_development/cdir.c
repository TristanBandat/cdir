#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

#define VERSION "1.1.0"             // current version of the project
#define LEN_FLAG_ARR 3              // number of flags
#define LEN_ARGS_ARR LEN_FLAG_ARR   // use this name for all use cases where you don't refer directly to the flag array
#define MAX_PATH_LEN 1024           // max. path length of cwd
#define MAX_DIR_NUMBER 512          // max. number of directories in cwd
#define MAX_DIR_NAME_LEN 256        // max. string length of the directories in cwd incl. the path
#define MAX_DIR_NAME_SEQ_LEN MAX_DIR_NAME_LEN   // max. length a directory name can have
#define MAX_STR_NUM_LEN 16          // max. number digits the number of the new directory name can have
#define IGNORED_DIRS {".", ".."}    // directories to be ignored by default
#define LEN_STR_ARGS_ARR 2          // length of the string argument array
#define NUM_NAME_ARG 1              // number of possible given dir/file name arguments

// structure for directories with correct formatting
struct directory {
    char name[MAX_DIR_NAME_LEN];    // name of the directory
    int occurrence;                 // how often the directory name appeared in cwd
    int num_digits;                  // number of digits after the underscore (leading zeros + actual number)
    int highest_number;             // highest number that appeared in all directories with the same name
};

// function prototypes
int arg_handler(int, char**, int *flag_arr, int *str_flag_arr, const char *args_arr,
                const char str_args_arr[LEN_STR_ARGS_ARR][MAX_DIR_NAME_SEQ_LEN], int *num_folders,
                char name_arr[NUM_NAME_ARG][MAX_DIR_NAME_SEQ_LEN]);
int update_flag(char flag, int* flag_arr, const char* args_arr);
int update_flag_str(char*, int *str_flag_arr, const char str_args_arr[LEN_STR_ARGS_ARR][MAX_DIR_NAME_SEQ_LEN]);
void get_cwd(char *cwd_arr);
int get_directories(struct directory*, DIR*);
void print_help();
void create_dir(struct directory, char*, int *num_dirs);

int main(int argc, char **argv) {
    // array with all single character flags
    int flag_arr[LEN_FLAG_ARR] = {};
    // array with all string argument flags
    int str_flag_arr[LEN_STR_ARGS_ARR] = {};
    // array with all single character arguments
    const char args_arr[LEN_ARGS_ARR] = {'h', 'v', 'V'};
    // array with all string arguments
    const char str_args_arr[LEN_STR_ARGS_ARR][MAX_DIR_NAME_SEQ_LEN] = {"help", "version"};
    // array where the parsed arguments are stored
    char name_arr[NUM_NAME_ARG][MAX_DIR_NAME_SEQ_LEN] = {};
    // array for storing the current working directory (cwd)
    char cwd_arr[MAX_PATH_LEN];
    // variable to go through all directories and files in cwd
    DIR *dr;
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
    // found arguments inside name_arr
    bool name_args_found = false;
    // number of folders to be created
    int num_folders = 1;

    // get the current working directory
    get_cwd(cwd_arr);
    // open de current directory
    dr = opendir(cwd_arr);
    // check if the pointer is valid
    if (dr == NULL) {
        printf("Unable to open current directory.");
        exit(-1);
    }

    // set the flags
    // if (set_flags(argc, argv, flag_arr, args_arr)) {
    if (arg_handler(argc, argv, flag_arr, str_flag_arr, args_arr, str_args_arr, &num_folders, name_arr)) {
        // Something went wrong - abort
        printf("Error with args - aborted\n");
        return -1;
    }

    // check for 'name_args'
    for (int i = 0; i < NUM_NAME_ARG; i++) {
        if (strcmp(name_arr[i], "\0") != 0) {
            name_args_found = true;
            break;
        }
    }

    // check for flags
    if (flag_arr[0] || str_flag_arr[0]) {                              // check if the user wants help
        print_help();
        return 0;
    } else if (flag_arr[1] || flag_arr[2] || str_flag_arr[1]) {        // check for version number
        printf("CDIR Version %s\n\n", VERSION);
        return 0;
    }

    // get all considered directories
    considered_directories_index = get_directories(considered_directories, dr);

    // no directory or arg found
    if ((considered_directories_index == 0) && !name_args_found) {
        printf("No folder(s) found.\n");
        return 0;
    }

    // Check command line args for given directory name
    if (!name_args_found) {
        // no directory name given
        // get the directory with the highest occurrence
        for (int i = 0; i < considered_directories_index; i++) {
            if (considered_directories[con_dir_occ_index].occurrence < considered_directories[i].occurrence) {
                con_dir_occ_index = i;
            }
        }
        // create additional directory with given parameters
        create_dir(considered_directories[con_dir_occ_index], cwd_arr, &num_folders);
    } else {
        // directory name given as arg
        // get directory name and append an underscore to the given name
        strcpy(given_dir_name, name_arr[0]);
        strcat(given_dir_name, "_");

        // check for already existing directories with given name
        for (int i = 0; i < considered_directories_index; i++) {
            if (strcmp(considered_directories[i].name, given_dir_name) == 0) {
                // there exists a directory with given name -> create
                create_dir(considered_directories[i], cwd_arr, &num_folders);
                dir_found = true;
                break;
            }
        }

        // if there was no directory found -> create a new one
        if (!dir_found) {
            // creating a new directory structure element with given name
            strcpy(considered_directories[considered_directories_index].name, given_dir_name);
            considered_directories[considered_directories_index].occurrence = 1;
            // set number of digits to 1 because the directory number is in this case 0 by default
            considered_directories[considered_directories_index].num_digits = 1;
            considered_directories[considered_directories_index].highest_number = -1;
            // update the next free slot in the array
            considered_directories_index++;
            // creating the directory
            create_dir(considered_directories[considered_directories_index-1], cwd_arr, &num_folders);
        }
    }

    // close directory
    closedir(dr);

    // task completed successfully and returns
    printf("done.\n");
    return 0;
}

int arg_handler(int argc, char **argv, int *flag_arr, int *str_flag_arr, const char *args_arr,
                const char str_args_arr[LEN_STR_ARGS_ARR][MAX_DIR_NAME_SEQ_LEN], int *num_folders,
                char name_arr[NUM_NAME_ARG][MAX_DIR_NAME_SEQ_LEN])
/*
 * This function sets all flags given by the command line arguments
 * and are in the arguments array 'args_arr' in the flag array 'flag_arr'.
 * Throws an error if an unknown flag occurred.
 * Command line arguments which are not flags will be processed accordingly.
 */
{
    // indicator for an upcoming flag
    bool is_flag = false;
    // counter for the number of used dashes (1 or 2 - indicates char/string)
    int flag_dash_count = 0;
    // indicator that a single dash appeared at the beginning of an argument
    bool single_dash_flag_updated = false;
    // buffer for flag argument string
    char arg_buffer[MAX_DIR_NAME_SEQ_LEN] = {};
    // next free index in 'arg_buffer'
    int arg_buffer_index = 0;
    // indicator that the upcoming characters will be a number
    bool check_num_folder = false;

    // go through the command line args
    // -> skipping the first argument because it contains the command itself
    for (int i = 1; i < argc; i++) {
        // stop when the end is reached
        if (argv[i] == NULL)
            break;

        if (isdigit(argv[i][0]))
            check_num_folder = true;

        // go through the string
        for (int j = 0; argv[i][j] != '\0'; j++) {
            // check for a flag
            if (argv[i][j] == '-') {
                is_flag = true;
                flag_dash_count++;
                // 3 or more dashes -> abort
                if (flag_dash_count >= 3)
                    return 1;
            }

            // check for beginning of string
            if (is_flag && (argv[i][j] != '-')) {
                // check for invalid arg (multiple characters after single dash)
                if (single_dash_flag_updated) {
                    // invalid argument -> abort
                    return 1;
                }
                // check if only one character is parsed as flag
                if (flag_dash_count == 1) {
                    // update flag
                    if (update_flag(argv[i][j], flag_arr, args_arr) == 1) {
                        // unknown argument
                        return 1;
                    }
                    single_dash_flag_updated = true;
                    continue;
                }
            }

            // handle string argument
            if (argv[i][j] != '-') {
                arg_buffer[arg_buffer_index] = argv[i][j];
                arg_buffer_index++;
            }

            single_dash_flag_updated = false;
        }

        // handle argument in 'arg_buffer' ...
        if ((arg_buffer_index > 0) && is_flag) {
            // ... when it is a flag
            if (update_flag_str(arg_buffer, str_flag_arr, str_args_arr) == 1) {
                // unknown argument
                return 1;
            }
        } else if (arg_buffer_index > 0) {
            // ... when it is an argument
            if (check_num_folder) {
                *num_folders = atoi(arg_buffer);
            } else {
                // NOTE: when 'name_arr' gets multiple strings, this has to be rewritten
                // check if there is already something in 'name_arr'
                if (strcmp(name_arr[0], "\0") != 0) {
                    return 1;
                }
                // HELP INFO: if flag set -> copy arg_buffer + set flag
                // save argument
                strcpy(name_arr[0], arg_buffer);
            }
        }

        // handle number in 'num_folder_buffer'


        // --- check for wrong argument parsing
        // dash counter is 1 and there was no character parsed to 'update_flag()' (parsing '-' only)
        if ((flag_dash_count == 1) && !single_dash_flag_updated)
            return 1;
        // dash counter is 2 but nothing in arg buffer (parsing '--' only)
        if ((flag_dash_count == 2) && (arg_buffer_index == 0))
            return 1;
        // ---

        // --- reset all temporary variables
        // reset flag indicator and counter
        is_flag = false;
        flag_dash_count = 0;
        // reset number indicator
        check_num_folder = false;
        // reset argument buffer and its index
        memset(arg_buffer,0,MAX_DIR_NAME_SEQ_LEN);
        arg_buffer_index = 0;
        // ---
    }

    // all worked fine
    return 0;
}

int update_flag(char flag, int* flag_arr, const char* args_arr)
/*
 * This function updates the flag given by the variable 'flag'.
 * It takes one flag at a time and updates the state if the flag is defined in
 * the arguments array 'args_arr'.
 * The function runs through the possible args and if the flag is found, it
 * will set the value at the corresponding index to 1.
 * After the flag was set, it will terminate.
 */
{
    // go through the flag array
    for (int i = 0; i < LEN_ARGS_ARR; i++) {
        // check if a flag is found
        if (flag == *(args_arr + i)) {
            // flag found -> set and terminate
            *(flag_arr + i) = 1;
            return 0;
        }
    }
    // flag not found
    return 1;
}

int update_flag_str(char *arg_buffer, int *str_flag_arr, const char str_args_arr[LEN_STR_ARGS_ARR][MAX_DIR_NAME_SEQ_LEN])
/*
 * This function updates the flag given by the string 'arg_buffer'.
 * It takes one flag at a time and updates the state if the flag is defined in
 * the arguments array 'str_args_arr'.
 * The function runs through the possible args and if the flag is found, it
 * will set the value at the corresponding index to 1.
 * After the flag was set, it will terminate.
 */
{
    // go through the flag array
    for (int i = 0; i < LEN_STR_ARGS_ARR; i++) {
        // check if a flag is found
        if (strcmp(arg_buffer, str_args_arr[i]) == 0) {
            // flag found -> set and terminate
            *(str_flag_arr + i) = 1;
            return 0;
        }
    }
    // flag not found
    return 1;
}

void get_cwd(char *cwd_arr)
/*
 * Gets the current working directory (cwd) and saves it in the given cwd_arr.
 * The maximal path length is defined by the constant MAX_PATH_LEN.
 * If the path is larger than the constant defines, the function will raise an error.
 */
{
    // compute the size in bits of the array the cwd path is stored in
    int cwd_arr_size = sizeof(*cwd_arr) * MAX_PATH_LEN;
    // gets cwd - exits the program with status -1 if something bad happens
    if (getcwd(cwd_arr, cwd_arr_size) == NULL) {
        perror("get_cwd() error");
        exit(-1);
    }
}

int get_directories(struct directory *considered_directories, DIR *dr)
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
    // pointer to directory entry
    struct dirent *de;
    // directories to be ignored by default
    char ignored_dirs[2][3] = IGNORED_DIRS;
    // variable to go through a string (runner)
    char current_char;
    // variable is true if there exists appropriate formatting after a underscore
    bool is_valid_number = false;
    // index of the next free position in 'considered_directories'
    int considered_directories_index = 0;
    // converted number given in 'number_sequence'
    int number_sequence_int;
    // directory name without the number
    char name_sequence[MAX_DIR_NAME_SEQ_LEN] = {};
    // index of the next free position in 'name_sequence'
    int name_seq_index = 0;
    // found name sequence in considered directory array
    bool name_seq_exists = false;
    // sequence of valid numbers as string
    char number_sequence[MAX_STR_NUM_LEN] = {};
    // length of 'number_sequence'
    int number_sequence_len = 0;
    // index of the next free position in 'number_sequence'
    int number_seq_index = 0;

    // get all directories from cwd
    while ((de = readdir(dr)) != NULL) {
        // check if the current element is a directory
        if (de->d_type == DT_DIR) {
            // check if the directory should be ignored
            // if there should exist more than these 2 options: replace with for loop
            if ((strcmp(de->d_name, ignored_dirs[0]) == 0) ||
                (strcmp(de->d_name, ignored_dirs[1]) == 0)) {
                continue;
            }

            // --- check all directories for the correct formatting
            for (int j = 0; de->d_name[j] != '\0'; j++) {
                // get the next character from the directory name
                current_char = de->d_name[j];
                // check if the current characters are valid numbers
                if (is_valid_number) {
                    // check if char is a number
                    if ((current_char >= '0') && (current_char <= '9')) {
                        // add char to 'number_sequence' and increment index
                        number_sequence[number_seq_index] = current_char;
                        number_seq_index++;
                    } else {
                        // --- incorrect formatting - delete number sequence
                        // add incorrect 'number_sequence' to the directory name
                        strcat(name_sequence, number_sequence);
                        // update index of the 'name_sequence'
                        name_seq_index += number_seq_index;
                        // append current char to the sequence and update index
                        name_sequence[name_seq_index] = current_char;
                        name_seq_index++;
                        // clear the 'number_sequence' and reset index
                        memset(number_sequence,0,MAX_STR_NUM_LEN);
                        number_seq_index = 0;
                        // toggle 'valid number' indicator
                        is_valid_number = false;
                    }
                } else {    // char is no valid number (no underscore appeared)
                    is_valid_number = false;
                    // save char in 'name_sequence' and update index
                    name_sequence[name_seq_index] = current_char;
                    name_seq_index++;
                }

                // check if the current character is an underscore and the next character is a number
                if ((current_char == '_') && (de->d_name[j+1] >= '0') && (de->d_name[j+1] <= '9')) {
                    // the following sequence could be a valid 'number_sequence' -> set indicator
                    is_valid_number = true;
                }
            }

            // length of the number sequence
            number_sequence_len = (int)(strlen(number_sequence));

            // check if a valid directory was found (with numbering)
            if (number_seq_index > 0) {
                // convert the number to an integer
                number_sequence_int = atoi(number_sequence);
                // go through all already existing directory entries
                for (int j = 0; j < considered_directories_index; j++) {
                    // check if the name already exists
                    if (strcmp(considered_directories[j].name, name_sequence) == 0) {
                        // the directory exists already -> increment occurrence
                        considered_directories[j].occurrence++;

                        // check if the highest seen number of this directory name needs to be updated
                        if (number_sequence_int > considered_directories[j].highest_number) {
                            // updating the highest seen number
                            considered_directories[j].highest_number = number_sequence_int;
                        }

                        // check if the highest number of digits needs to be updated
                        if (number_sequence_len > considered_directories[j].num_digits) {
                            // updating the highest number of seen digits
                            considered_directories[j].num_digits = number_sequence_len;
                        }

                        // set the indicator to true and break
                        name_seq_exists = true;
                        break;
                    }
                }

                // if the directory does not already exist -> add it to the array
                // -> depends on the fact that the if statement above was executed
                if (!name_seq_exists) {
                    // --- creating a new directory entry with given variables
                    strcpy(considered_directories[considered_directories_index].name, name_sequence);
                    considered_directories[considered_directories_index].occurrence = 1;
                    considered_directories[considered_directories_index].num_digits = number_sequence_len;
                    considered_directories[considered_directories_index].highest_number = number_sequence_int;
                    considered_directories_index++;
                }

                // reset indicator
                name_seq_exists = false;
            }

            // --- done for the current iteration
            // empty the strings and reset the indices
            memset(number_sequence,0,MAX_STR_NUM_LEN);
            number_seq_index = 0;
            memset(name_sequence,0,MAX_DIR_NAME_SEQ_LEN);
            name_seq_index = 0;
            is_valid_number = false;
            // ---
        }
        // ---
    }

    // return the length/next free index of the 'considered_directories' data structure
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

void create_dir(struct directory dir, char *cwd_arr, int *num_dirs)
/*
 * Puts directory name and path together and creates the directory.
 * If an error while creating occurs, the program exits with status -1.
 */
{
    // finished directory name incl. path
    char path_dir_name[MAX_DIR_NAME_LEN] = {};
    // new directory number
    int new_number = dir.highest_number + 1;
    // new directory number as string
    char new_number_str[MAX_STR_NUM_LEN] = {};
    // digit length of the new number
    int new_number_str_len = 0;

    for (int i = 0; i < *num_dirs; i++) {
        // --- cast the new number to string and calculate its digit length
        // cast new directory number to string
        sprintf(new_number_str, "%i", new_number);
        // get the digit length of the new number
        new_number_str_len = (int) strlen(new_number_str);
        // ---

        // --- put the directory name together
        // paste current path
        strcpy(path_dir_name, cwd_arr);
        // paste a missing slash for completeness
        strcat(path_dir_name, "/");
        // paste the given directory name
        strcat(path_dir_name, dir.name);
        // paste the given amount of zeros between the underscore and the number
        for (int i = 0; i < (dir.num_digits - new_number_str_len); i++)
            strcat(path_dir_name, "0");
        // paste the new directory number
        strcat(path_dir_name, new_number_str);
        // ---

        // print the finished directory path + name
        printf("Creating directory %s\n", path_dir_name);
        // create directory
        if (mkdir(path_dir_name, 0700) == -1) {
            // something bad happened
            printf("ERROR while creating directory.\n\n");
            exit(-1);
        }

        // increment the current new number
        new_number++;
    }
}
