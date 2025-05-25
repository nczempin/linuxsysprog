# linuxsysprog

## Problem Statement

This project is a custom implementation of the `ls` command, created as a learning exercise in systems programming. The main goals are:

*   To understand the underlying mechanisms of how common Unix utilities like `ls` work by reimplementing core parts of their functionality.
*   To gain practical experience with Linux system calls related to file system interaction.

### Why create another `ls`?

The purpose of this project is not to replace the existing `ls` command, which is a mature and feature-rich utility. Instead, this implementation serves as an educational tool to explore:

*   **Directory Traversal:** How programs read the contents of a directory.
*   **File Metadata:** How to retrieve and interpret information about files and directories (e.g., permissions, ownership, size, timestamps).
*   **System Calls:** Direct interaction with the operating system kernel (specifically using `SYS_getdents`).
*   **Output Formatting:** Basic C programming techniques for presenting information to the user.

### Learning Objectives

Through this project, one can learn about:

*   The use of system calls like `open`, `stat`, and `getdents` (via `syscall`).
*   The structure of directory entries (`struct linux_dirent`).
*   Retrieving user and group information (`getpwuid`, `getgrgid`).
*   Basic C programming, including string manipulation, memory management, and standard I/O.
*   The general principles of how command-line tools interact with the file system.

Just wanted to get into a bit of lower level programming

## Current Functionality

This `ls` implementation currently supports the following features:

*   **List Directory Contents:** Lists files and directories in the current directory.
*   **File Type Indication:** Displays a 'd' for directories and a '-' for regular files at the beginning of the permissions string.
*   **Permissions (Partial):** Shows hardcoded permissions (`rwxrwxr-x`). The actual permission bits are read but not yet fully decoded.
*   **Number of Hard Links:** Displays the number of hard links to the file.
*   **Owner and Group:** Shows the username of the owner and the group name.
*   **File Size:** Displays the size of the file in bytes.
*   **Last Modification Time:** Shows the month, day, and time of the last modification (e.g., "Aug 22 15:04").
*   **File/Directory Name:** Displays the name of the file or directory.

### TODO Items

The following items are noted in the source code (`ls.c`) as planned improvements:

*   **Sort Output:** Currently, the output is not sorted and appears in directory entry order.
*   **Color Output:** Add support for colored output to differentiate file types (similar to `ls --color=auto`).
*   **Actual Permissions:** Decode and display the actual file permissions (e.g., `rwxrw-r--`) instead of the current hardcoded string.
*   **Line Formatting:** Improve the overall output formatting for better readability and alignment, potentially mimicking standard `ls` more closely.

### Comparison to Standard `ls`

This implementation is a very simplified version of the standard `ls` command found on Linux systems. Key differences include:

*   **Limited Options:** It does not support any command-line options (e.g., `-l`, `-a`, `-h`, `-t`).
*   **No Sorting:** Output is unsorted.
*   **No Color:** Lacks colored output.
*   **Simplified Permissions:** Permissions are not fully implemented.
*   **Basic Formatting:** Output formatting is rudimentary.
*   **Error Handling:** Error handling is basic.
*   **Single Directory:** Only lists the current directory; does not support specifying other paths.

It serves as a basic demonstration of reading directory entries and file metadata.

## Setup and Usage

### System Requirements

*   **Linux-specific:** This program is designed for Linux systems due to its use of the `SYS_getdents` system call and Linux-specific headers. It will likely not compile or run on other operating systems like macOS or Windows without modification.

### Building

To compile the program, a `Makefile` is provided. Simply run:

```bash
make
```

This will produce an executable file named `ls` in the current directory.

### Running

To run the program after building, execute it from your terminal:

```bash
./ls
```

This will list the contents of the current directory, similar to the standard `ls` command but with the features and limitations described above.
