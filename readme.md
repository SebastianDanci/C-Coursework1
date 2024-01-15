Author: M00886707 <sd1507@mdx.ac.uk>
Created: 09/01/2023
Updated: 15/01/2023

Library Management System

Overview

This Library Management System is a software designed to manage basic library functions efficiently. The system allows for managing books, members, librarians, and related activities like borrowing and returning books.



Features

Add and manage library members

Issue and return books

Calculate fines for late returns

Display borrowed books for each member

Validate user input with regex patterns



System Requirements

A compiler supporting C++17 or higher

Filesystem support



To compile and run this project:

Navigate to the root directory.
Run the makefile to compile the project;
"make"
Execute the binary file located in the bin directory;
"./bin/library.exe"



Usage

The system will prompt you through a menu-driven interface to perform various actions. Follow the on-screen instructions to navigate through the options.



Directory Structure

bin: Will contain the compiled binaries.

include: Contains all header files with class and function declarations.

src: Contains source files implementing the functionalities.

data: It's recommended to put the csv file here



The program can only handle one csv file at a time, it will search troughout the root directory and all it's sub-directories for the file.
