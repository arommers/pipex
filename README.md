<img src="https://i.imgur.com/HG66CCx.png?raw=true" alt="CODAM" style="max-width: 50%;">

# Pipex
Pipex is a command-line tool that emulates the shell pipeline operator (`|`). It allows us to chain commands together, with each one processing the output of the previous. Think of it as an assembly line for data processing. Simplify tasks like filtering, transforming, and analyzing data from various sources.  

Whether we're working with log files or conducting data analysis, Pipex streamlines the entire pipeline process.
Creating this project challegend and improved our understanding of Unix-like systems, focusing on process creation, file descriptors, and system calls. It's a practical tool with valuable insights into the core mechanisms of modern computing.

## Key Concepts
- Process creation using `fork`.
- Inter-process communication with pipes.
- Redirection of standard input and output.
- Proper error handling for system calls.
- Efficient execution of commands using `exec` family of functions.

---

## The Program

As mentioned in the introduction Pipex takes command-line arguments and chains these together, changing the input and output to the provided files.
Below we have the formatted line thata our program considers as valid. 
An example of chaining commands together could be with the commands 'ls' and 'grep'.

 `./pipex file1 "ls -l" "grep keyword" file2`

- `./pipex`: The name of our program
- `file1`: Input file whose contents will be processed by the first command.
- `cmd1`: First command (`ls -l`).
- `cmd2`: Second command (`grep keyword`).
- `file2`: Output file to store the result.

Of course, it is also possible to pipe custom commands, as opposed to shell commands.

`./pipex file1 "./custom_cmd1 arg1" "./custom_cmd2 arg2" file2`

including the input file, two commands, and an output file.
It parses these arguments to identify the necessary components.
File Descriptors (FD):

Pipex opens the input and output files, acquiring file descriptors for them.
It ensures that the necessary file descriptors (0 for stdin, 1 for stdout) are correctly set.
Piping:

Pipex sets up a pipe using the pipe() system call.
It forks a child process, creating two identical copies of the program (parent and child).
Redirection:

The child process redirects its stdout to the write end of the pipe using the dup2() system call.
The parent process redirects its stdin to the read end of the pipe in a similar manner.
Command Execution:

The child process executes the first command using the execvp() system call, which replaces the child's program with the specified command.
The output of the first command flows through the pipe to the parent process.
Second Command Execution:

The parent process, now receiving the output of the first command, executes the second command using execvp().
This output can be further processed or directed to the specified output file.
Cleanup:

Pipex ensures that all file descriptors are closed, and any resources used are properly released.
It waits for the child process to complete its execution.
Finishing:

Pipex completes its execution, and the desired operations (e.g., filtering, transforming) have been applied to the input data.
