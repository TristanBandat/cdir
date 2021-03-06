import os
import re
import sys

# current version of the project
VERSION = '1.1.0'


def get_dir_name(dir_names):
    """
    This function searches for the directory name which appears the most
    in a given folder.
    :param dir_names: string list
    :return: dir_name: string
    """
    match_list_len = []
    # check if there are existing directories
    if len(dir_names) == 0:
        print("No folder(s) found.")
        exit()
    # go through all the directory names
    for pattern in dir_names:
        # finding all redundant directory names
        match_list = re.findall(pattern, str(dir_names))
        # appending there frequency to a list
        match_list_len.append(len(match_list))
    # get the folder with the highest occurrence
    max_occurrence = [i for i, j in enumerate(match_list_len) if j == max(match_list_len)][0]
    # look up how the folder name is called
    dir_name = dir_names[max_occurrence]
    # return the folder name
    return dir_name


def help_text():
    """
    This function displays the help text.
    :return: None
    """
    print("HELP\n----")
    print("cdir [argument]\n")

    print("When you type only the function name the program will search for a folder structure")
    print("that looks like [folder_name]_[number]. If there are more than one available it will")
    print("choose the one which appears the most. Then the program looks for the highest number")
    print("of the folder structure, increments it by 1 and creates a new directory with the\nnew folder name.\n")

    print("If you want to choose the folder name, simply type in the preferred name as")
    print("an argument. The program will search for the highest number in the folder structure with")
    print("that keyword, increments it by 1 and creates a new directory with the new folder name.")
    print("If there exists no directory in the current working directory, the program will start with\n")
    print("0 as the highest number and proceed like normal.")

    print("To get this help statement displayed use the arguments 'help', '-h', '-?', '--help'\n\n")
    pass


def main():
    """
    This is the main function of this program.
    :return: None
    """
    # get the command line arguments
    command_line_args = sys.argv
    # get the current working directory
    cwd = os.getcwd()
    # get the content of the cwd
    folder_content = os.listdir(cwd)
    # filter only the directory's
    folders = []
    [folders.append(current_object) for current_object in folder_content if os.path.isdir(current_object)]
    # folder names and corresponding numbers
    numbers = []
    folder_names = []
    # list with digit counts of each given folder name
    numbers_num_digits = list()
    # number of directories which will be created
    num_new_dirs = 1
    # go through all folders
    for element in folders:
        element_list = element.split('_')
        # check if the folder name has the correct structure
        if len(element_list) >= 2:
            try:
                # get the folder name and the number separate
                numbers.append(int(element_list[-1]))
                # putting the directory name back together
                folder_name_str = ''
                for x in element_list[:-1]:
                    folder_name_str += '_' + x
                # remove additional underscores if they occur
                if folder_name_str[0] == '_':
                    folder_name_str = folder_name_str[1:]
                # append directory name to list
                folder_names.append(folder_name_str)
                # get the digit count of the number -> this part fails pretty easily
                numbers_num_digits.append(int(len(element_list[-1])))
            except ValueError:
                print(f"Was not able to convert string to int of folder '{element}'")
                continue
    # name of the new folder
    directory_name = ""
    # if no additional argument was given
    if command_line_args.__len__() == 1 or command_line_args[1] == '':
        directory_name = get_dir_name(folder_names)
    # if a additional command line argument is given
    elif command_line_args.__len__() == 2 and command_line_args[1] != '':
        # help flag is set
        if command_line_args[1] == 'help' or \
                command_line_args[1] == '-h' or \
                command_line_args[1] == '-?' or \
                command_line_args[1] == '--help':
            # prints help text and exits
            help_text()
            exit(0)
        # version flag is set
        elif command_line_args[1] in ['--version', '-v', '-V']:
            # displays current version and exits
            print('CDIR Version {}\n'.format(VERSION))
            exit(0)
        elif command_line_args[1].isdigit():
            directory_name = get_dir_name(folder_names)
            num_new_dirs = int(command_line_args[1])
        else:
            # given argument is a directory name
            directory_name = command_line_args[1]
    # if a directory name and number of directories is given
    elif command_line_args.__len__() == 3:
        if command_line_args[1][0] == '-' or not command_line_args[2].isdigit():
            raise SyntaxError("Command not properly used!")
        # given argument is a directory name
        directory_name = command_line_args[1]
        num_new_dirs = int(command_line_args[2])
    else:
        # something went wrong
        raise SyntaxError("Command not properly used!")
    # highest number of chosen directory name
    highest_number = -1
    # length of the number (needed for given 0s before the number)
    number_length = -1
    # get the highest number of the directory numbering
    for i, element in enumerate(folder_names):
        if element == directory_name and highest_number < numbers[i]:
            highest_number = numbers[i]
            number_length = numbers_num_digits[i]
    # set the new number
    new_number = highest_number
    # run through the number of new directories
    for i in range(num_new_dirs):
        # count digit length of the highest number
        highest_number_digit_count = len(str(new_number))
        placeholder_count = number_length - highest_number_digit_count
        # get the new directory number
        new_number += 1
        # check for the digit number of the new directory number
        new_number_digit_count = len(str(new_number))
        # update the placeholder counter
        if new_number_digit_count > highest_number_digit_count and placeholder_count > 0:
            placeholder_count -= 1
        # put the directory name together
        new_dir_name = directory_name + '_' + ('0' * placeholder_count) + str(new_number)
        print(f"Creating directory {new_dir_name}")
        # create the new directory
        os.makedirs(new_dir_name)
    # everything went fine -> print and terminate
    print("done.")


if __name__ == '__main__':
    main()
