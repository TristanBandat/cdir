# cdir
Shell script for creating new folders with consecutive numbering.

(C) Tristan Bandat , 2021

The goal of this project is to create a function that makes folder creating much faster.
The function should detect on it's own if there is an existing folder structure 
(FOLDERNAME_X where X is a number) and create a folder with the correct folder name (FOLDERNAME_X+1).
This should work with only the function call in the corisponding folder:

            ~/Folder/% cdir

But if the function get's a folder name as well, the function detects any existing folders with 
that name (if they exist) and creates a new directory with the given name and the next available number:

            ~/Folder/% cdir Exercise

Of course the function should have a help page (-h or -? or --help or help).

Other information:

# 1) The project is written in C (C99). Stoped because of the high complexity for a script.
1) The project is written in Python 3.7.
2) The finished file will be copied in the .bin/ folder aka project.
3) There is a version on BCB as well as on the git server.
4) The function will only work with numbers that are after the folder name and seperated 
    with a _.
