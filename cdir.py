import os
import re
import sys

# current version of the project
VERSION = '1.0.4'


def get_foldername(folder_names):
    """
    This function searches for the foldername which appears the most
    in a given folder.
    :param folder_names: string list
    :return: foldername
    """
    match_list_len = []
    # check if there are existing folders
    if len(folder_names) == 0:
        print("No folder(s) found.")
        exit()
    # go through all the folder names
    for pattern in folder_names:
        # finding all redundant folder names
        match_list = re.findall(pattern, str(folder_names))
        # appending there frequency to a list
        match_list_len.append(len(match_list))
    # get the folder with the highest occurrence
    max_occurrence = [i for i, j in enumerate(match_list_len) if j == max(match_list_len)][0]
    # look up how the folder name is called
    foldername = folder_names[max_occurrence]
    # return the folder name
    return foldername


def help_text():
    """
    This function displayes the help text.
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
    # go through all folders
    for element in folders:
        element_list = element.split('_')
        # check if the folder name has the correct structure
        if len(element_list) >= 2:
            try:
                # get the folder name and the number separably
                numbers.append(int(element_list[-1]))
                folder_name_str = ''
                for x in element_list[:-1]:
                    folder_name_str += '_' + x
                if folder_name_str[0] == '_':
                    folder_name_str = folder_name_str[1:]
                folder_names.append(folder_name_str)
                # get the digit count of the number
                numbers_num_digits.append(int(len(element_list[-1])))
            except ValueError:
                print(f"Was not able to convert string to int of folder '{element}'")
                continue
    # name of the new folder
    foldername = ""
    # if no additional argument was given
    if command_line_args.__len__() == 1 or command_line_args[1] == '':
        foldername = get_foldername(folder_names)
    # if a additional folder name is given
    elif command_line_args.__len__() == 2 and command_line_args[1] != '':
        if command_line_args[1] == 'help' or \
                command_line_args[1] == '-h' or \
                command_line_args[1] == '-?' or \
                command_line_args[1] == '--help':
            help_text()
            exit(0)
        elif command_line_args[1] in ['--version', '-v', '-V']:
            # display current version
            print('CDIR Version {}\n'.format(VERSION))
            exit(0)
        else:
            foldername = command_line_args[1]
    else:
        raise SyntaxError("Command not properly used!")
    highest_number = -1
    # length of the number (needed for given 0s before the number)
    number_length = -1
    # get the highest number of the folder names
    for i, element in enumerate(folder_names):
        if element == foldername and highest_number < numbers[i]:
            highest_number = numbers[i]
            number_length = numbers_num_digits[i]
    # count digit length of the highest number
    highest_number_digit_count = len(str(highest_number))
    placeholder_count = number_length - highest_number_digit_count
    # create the new folder name
    new_foldername = foldername + '_' + ('0' * placeholder_count) + str((highest_number + 1))
    print(f"Creating directory {new_foldername}")
    # create the new folder
    os.makedirs(new_foldername)
    print("done.")


if __name__ == '__main__':
    main()
