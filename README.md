# MyShell

**MyShell** is a small Unix-like command-line shell written in **C**. The project is designed to explore systems programming concepts such as file I/O, directory operations, process management, command parsing, and interaction with the Linux/POSIX operating system.

The goal of this project is not to recreate Bash completely, but to understand how a shell works internally by implementing common Unix commands and gradually adding process-management features.

## Project Goals

This project is being developed to learn:

- C programming for systems development
- Linux/POSIX system calls
- File and directory operations
- File descriptors and I/O
- Process creation and execution
- Command parsing
- Error handling
- Pipes and I/O redirection
- Signals and process management
- Makefiles and multi-file C projects

## Current Command Interface

The shell exposes its commands through `myshell.h`:

```c
#ifndef MYSHELL_H
#define MYSHELL_H

void my_cp(const char *source, const char *destination);
void my_cat(const char *filename);
void my_ls(const char *path);
void my_mkdir(const char *path);
void my_rmdir(const char *path);
void my_rm(const char *path);
void my_touch(const char *path);
void my_cd(const char *path);
void my_pwd();
void my_echo(const char *message);
void my_grep(const char *pattern, const char *filename);
void my_wc(const char *filename);

#endif // MYSHELL_H
```

The header provides function declarations for the shell's built-in commands.

## Commands

| Function | Command | Purpose |
|---|---|---|
| `my_cp()` | `cp` | Copy a file from one location to another |
| `my_cat()` | `cat` | Display the contents of a file |
| `my_ls()` | `ls` | List files and directories |
| `my_mkdir()` | `mkdir` | Create a directory |
| `my_rmdir()` | `rmdir` | Remove an empty directory |
| `my_rm()` | `rm` | Remove a file |
| `my_touch()` | `touch` | Create a file or update its timestamp |
| `my_cd()` | `cd` | Change the current working directory |
| `my_pwd()` | `pwd` | Display the current working directory |
| `my_echo()` | `echo` | Print a message to the terminal |
| `my_grep()` | `grep` | Search for a pattern inside a file |
| `my_wc()` | `wc` | Count lines, words, and/or characters |

## Architecture

The project is organized around separating the shell interface from the implementation of individual commands.

```text
                    MyShell
                       |
                Command Parser
                       |
          +------------+------------+
          |            |            |
       Built-ins    Processes    I/O System
          |            |            |
          ▼            ▼            ▼
      my_cd()       fork()       open()
      my_pwd()      exec()       read()
      my_ls()       wait()       write()
      my_cp()                    close()
```

The `myshell.h` header acts as the interface between the shell and the command implementations.

For example:

```text
User
 │
 ▼
Input: cp file.txt backup.txt
 │
 ▼
Parser
 │
 ├── command = cp
 ├── source = file.txt
 └── destination = backup.txt
 │
 ▼
my_cp()
 │
 ▼
File system
```

## Design

The command functions use `const char *` parameters for input paths, filenames, and messages.

For example:

```c
void my_cp(const char *source, const char *destination);
```

`source` and `destination` point to strings supplied to the function. The `const` qualifier indicates that the function should not modify those strings.

Similarly:

```c
void my_grep(const char *pattern, const char *filename);
```

receives a search pattern and the file that should be searched.

## Systems Programming Concepts

This project will progressively use low-level POSIX functionality rather than relying entirely on high-level C library functions.

Important APIs and concepts include:

### File I/O

```c
open()
read()
write()
close()
```

These APIs provide direct interaction with files through file descriptors.

### Directories

```c
opendir()
readdir()
closedir()
mkdir()
rmdir()
```

These are used for directory manipulation and implementing commands such as `ls`, `mkdir`, and `rmdir`.

### Process Management

As the shell develops, external commands will be executed using:

```c
fork()
exec()
waitpid()
```

This allows the shell to create child processes and execute other programs.

### File Descriptors

The project will also explore:

```text
stdin   → 0
stdout  → 1
stderr  → 2
```

This becomes important when implementing:

- input redirection
- output redirection
- pipelines
- command chaining

For example:

```text
command1 | command2
```

will eventually require communication between processes through a pipe.

## Planned Features

The project will be developed incrementally.

### Phase 1 — Basic Commands

- [x] Define command interface
- [ ] `pwd`
- [ ] `echo`
- [ ] `touch`
- [ ] `mkdir`
- [ ] `rmdir`
- [ ] `rm`
- [ ] `cat`
- [ ] `cp`
- [ ] `ls`

### Phase 2 — File Processing

- [ ] `grep`
- [ ] `wc`
- [ ] File error handling
- [ ] Permission handling
- [ ] Path handling

### Phase 3 — Shell

- [ ] Interactive prompt
- [ ] Command parsing
- [ ] Argument parsing
- [ ] Built-in command dispatch
- [ ] External command execution

### Phase 4 — Processes

- [ ] `fork()`
- [ ] `exec()`
- [ ] `waitpid()`
- [ ] Child-process management
- [ ] Exit status handling

### Phase 5 — I/O

- [ ] `>`
- [ ] `>>`
- [ ] `<`
- [ ] Pipes `|`
- [ ] File descriptor manipulation with `dup2()`

### Phase 6 — Advanced Shell Features

- [ ] Environment variables
- [ ] Signal handling
- [ ] Background processes
- [ ] `&`
- [ ] `SIGINT`
- [ ] `SIGCHLD`

## Example Usage

The final shell is intended to provide an interface similar to:

```text
myshell> pwd
/home/user/myshell

myshell> mkdir test

myshell> cd test

myshell> touch hello.txt

myshell> echo "Hello World"
Hello World

myshell> ls
hello.txt

myshell> cat hello.txt

myshell> cd ..
```

## Project Structure

A possible project structure is:

```text
myshell/
├── include/
│   └── myshell.h
│
├── src/
│   ├── main.c
│   ├── commands.c
│   ├── file.c
│   ├── directory.c
│   └── parser.c
│
├── tests/
│
├── Makefile
├── README.md
└── .gitignore
```

The structure may change as the project grows.

## Building

The project will use a `Makefile` to manage compilation.

Eventually:

```bash
make
```

will compile the project, while:

```bash
make clean
```

will remove generated object files and binaries.

## Why I Built This

This project is part of my study of **systems programming and low-level software engineering**.

Rather than treating the shell as a black box, I am using the project to understand what happens underneath a command-line interface:

```text
User command
     ↓
Parser
     ↓
Shell
     ↓
System calls
     ↓
Kernel
     ↓
File system / Process / Device
```

The project is particularly focused on understanding the relationship between **C, Linux, processes, memory, file descriptors, and the operating system**.

## Future Improvements

Possible future work includes:

- Job control
- Better command parsing
- Quoting and escaping
- Environment variable expansion
- Command history
- Tab completion
- Process groups
- Signal management
- More robust error handling
- Automated tests
- Performance measurements

## Learning Outcome

The final goal is to develop a practical understanding of how Unix shells interact with the operating system and how higher-level software can be built on top of low-level system interfaces.

This project is intentionally being developed incrementally so that each feature introduces a new systems-programming concept.
