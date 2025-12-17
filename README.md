*This project has been created as part of the 42 curriculum by shavryle@student.42prague.com.*

# Get Next Line

## Description
This project consists of coding a function that returns one line at a time from a text file. The goal is to learn about static variables and file descriptor management in C.

**Prototype:**
`char *get_next_line(int fd);`
The function reads from a file descriptor (`fd`) and returns the line including the terminating `\n` character (unless EOF is reached without one). It returns `NULL` if there is nothing else to read or an error occurs.

## Instructions
To use this function in your code, include the header `get_next_line.h` and compile your files with the source files.

### Compilation
You **must define the buffer size** at compilation time using the `-D` flag.

``` bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

## Execution
``` bash
./gnl
```

## Algorithm Explanation and Justification

The project uses a **static variable** to store data between function calls, ensuring that no characters are lost when reading chunks larger than a single line.

The logic is divided into three steps:

1. **Reading** (join_buffers): The function reads from the file descriptor into a temporary buffer and appends it to the static stash using ft_strjoin. This loop continues until a newline character (\n) is found or the end of the file is reached.

2. **Extraction** (returned_line): Once a newline is detected, the function extracts characters from the start of the stash up to the newline to create the line to be returned.

3. **Cleanup** (create_new_stash): The remaining characters (after the newline) are saved back into the static stash for the next call. The old stash memory is freed to prevent memory leaks.

**Justification**: This approach ensures efficiency by minimizing read() calls while handling any BUFFER_SIZE correctly.

## Resources

**References:**
- Manual pages

**Peer Learning:**

Discussed the concept of static variables and buffer management with another students.

**Internet** 
- [W3Schools](https://www.w3schools.com/c/index.php) 
- [StackOverflow](https://stackoverflow.com)

**AI Usage:** 
- [ChatGPT](https://chatgpt.com/) 
- [Gemini](https://gemini.google.com/app)

AI was used as a learning assistant to explain concepts that were new to me and to help analyze and fix compilation and Norminette errors.