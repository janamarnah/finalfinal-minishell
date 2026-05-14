# Minishell

*This project has been created as part of the 42 curriculum by jalamarn, abmusleh.*

# Description

Minishell is a simplified Unix shell developed in C as part of the 42 curriculum.
The goal of the project is to recreate the behavior of a real shell such as Bash while learning about processes, file descriptors, signals, parsing, and memory management.

The shell supports:

* Command execution
* Built-in commands
* Pipes and redirections
* Environment variables
* Exit status handling
* Signal handling
* Heredocs
* PATH resolution

This project helped deepen understanding of low-level Unix system calls such as:

* `fork`
* `execve`
* `pipe`
* `dup2`
* `waitpid`
* `signal`

# Features

## Built-in Commands

* `echo`
* `cd`
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

## Redirections

* Input redirection `<`
* Output redirection `>`
* Append redirection `>>`
* Heredoc `<<`

## Pipes

Commands can be connected using pipes:

```bash
ls -la | grep minishell | wc -l
```

## Environment Variables

Supports variable expansion:

```bash
echo $USER
echo $PATH
echo $?
```

## Signal Handling

* `Ctrl+C`
* `Ctrl+D`
* `Ctrl+\`


# Instructions

## Compilation

Clone the repository:

```bash
git clone https://github.com/janamarnah/finalfinal-minishell.git
cd finalfinal-minishell
```

Compile the project:

```bash
make
```

Clean object files:

```bash
make clean
```

Remove all generated files:

```bash
make fclean
```

Recompile the project:

```bash
make re
```

# Execution

Run the shell using:

```bash
./minishell
```

Example:

```bash
minishell$ echo hello
hello
```

# Project Structure

```text
executing/     -> command execution and builtins
parsing/       -> lexer, parser, expansions, syntax validation
main.c         -> shell loop and initialization
minishell.h    -> structures and function prototypes
```

# Resources

## Documentation

* Linux Manual Pages
  https://man7.org/linux/man-pages/

* GNU Bash Documentation
  https://www.gnu.org/software/bash/manual/

* Readline Library Documentation
  https://tiswww.case.edu/php/chet/readline/rltop.html

* POSIX Standard
  https://pubs.opengroup.org/onlinepubs/9699919799/

# AI Usage

AI tools were used during development for:

* Debugging assistance
* Understanding Unix system calls
* Explaining shell behavior
* Reviewing edge cases
* Refactoring functions to satisfy Norminette
* Generating testing ideas and documentation guidance

All implementation decisions, coding, debugging, and integration were completed manually.

