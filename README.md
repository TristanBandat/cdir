# cdir
Shell script for creating new folders with consecutive numbering.

(C) Tristan Bandat , 2021

The goal of this project is to create a function that makes folder creating much faster.
The function detects on it's own if there is an existing folder structure 
(FOLDERNAME_X where X is a number) and creates a folder with the correct folder name (FOLDERNAME_X+1).
This works with only the function call in the corisponding folder:

            ~/Folder/% cdir

But if the function get's a folder name as well, the function detects any existing folders with 
that name (if they exist) and creates a new directory with the given name and the next available number:

            ~/Folder/% cdir Exercise

Of course the function has a help page (-h or -? or --help or help).

## Other information:

1) The project is written in Python 3.8.
2) The project is hosted on Github.
4) The function only works with numbers that are after the folder name and seperated 
    with a underscore. Aditional zeros after the underscore are getting detected, so don't worry.
5) The C implementation is currently under development. When it is working it will be stated here.
