*This project has been created as part of the 42 curriculum by <jdias-ju>.*

# get_next_line

## Description
The goal of this project is to write a function that returns a line read from a file descriptor. It introduces the concept of **static variables** in C programming and reinforces understanding of dynamic memory allocation and buffer management. Calling `get_next_line` in a loop allows you to read an entire text file one line at a time.

## Execution

The function is prototyped as: char *get_next_line(int fd);

It returns the line read (including the \n if present) or NULL if there is nothing left to read or if an error occurred. Remember to free() the returned pointer to avoid memory leaks.

## Algorithm Explanation

The algorithm is designed to handle cases where BUFFER_SIZE might be larger than the line itself, meaning one read() call could contain parts of multiple lines.

    Persistence: A static variable acts as a long-term buffer. It stores characters that were read but not yet returned to the user.

    The Reading Loop: The function reads from the file descriptor in chunks of BUFFER_SIZE. It uses a helper function (ft_strjoin) to append these chunks to the static variable until a newline character (\n) is detected or the end of the file is reached.

    Extraction: Once a newline is found, the function slices the static string. The part up to the newline is prepared as the return value.

    Cleaning: The static variable is updated to keep only the remaining characters (the ones after the newline), ensuring the next call starts exactly where the previous one left off.

## Resources

    Unix System Calls - read()

    Static Variables in C

    42 Project Guidelines
