*This project has been created as part of the 42 curriculum by camansou, makoon.*

# minishell

A small Unix shell written in C, modeled on Bash: interactive prompt, history, pipes, redirections, heredocs, environment variable expansion, quote handling, signals and the usual built-ins.

```console
$ ./minishell
minishell$ export NAME=42
minishell$ echo "Hello $NAME" | tr a-z A-Z > out.txt
minishell$ cat < out.txt
HELLO 42
minishell$ cat << EOF | wc -l
> one
> two
> EOF
2
minishell$ ls nonexistent
ls: cannot access 'nonexistent': No such file or directory
minishell$ echo $?
2
minishell$ exit
```

## Description

The goal of minishell is to understand what really happens between the moment you press Enter in a terminal and the moment a program runs: how a command line is split and interpreted, how processes are created, and how file descriptors are wired together.

### Features

**Command line**
- Prompt with a working history (GNU Readline)
- Executables found through `PATH`, or with a relative or absolute path
- Single quotes `'...'` disable all interpretation
- Double quotes `"..."` disable interpretation except `$`
- Unclosed quotes are rejected as a syntax error
- `$VAR` expansion and `$?` (exit status of the last foreground pipeline)

**Redirections and pipes**
- `<` input, `>` output, `>>` append
- `<<` heredoc with a delimiter (variables are expanded inside, and it is not added to the history)
- Pipelines of any length: `cmd1 | cmd2 | cmd3 ...`

**Signals** (interactive mode, same behavior as Bash)
- `Ctrl-C` displays a new prompt on a new line
- `Ctrl-D` exits the shell
- `Ctrl-\` does nothing

**Built-ins**

| Command | Behavior |
|---|---|
| `echo` | with `-n` |
| `cd` | relative or absolute path |
| `pwd` | no options |
| `export` | no options |
| `unset` | no options |
| `env` | no options or arguments |
| `exit` | no options, accepts an exit code |

### How it works

Each line goes through the same pipeline:

```
readline ──► lexer ──► syntax check ──► expansion ──► parser ──► executor
             tokens    pipes, redirs,   $VAR, $?,    command     fork, pipe,
                       quotes           quote        list        dup2, execve
                                        removal
```

1. **Lexer** (`Parsing/tokenization.c`) splits the line into tokens (`WORD`, `PIPE`, `REDIR_IN`, `REDIR_OUT`, `REDIR_APPEND`, `HEREDOC`) and records whether each word was single or double quoted.
2. **Syntax check** (`Parsing/syntax_check.c`) rejects invalid input such as `| ls`, `ls >` or unclosed quotes, and sets `$?` to `2`, like Bash.
3. **Expansion** (`Parsing/expansion*.c`) replaces `$VAR` and `$?` according to the quoting context, then removes the quotes.
4. **Parser** builds a linked list of `t_command`: name, arguments, input and output files, heredoc delimiter.
5. **Executor** (`Execution/`) runs a single built-in directly in the shell process, so that `cd`, `export` or `exit` affect the shell itself. Anything else, and every command in a pipeline, runs in a child process connected with `pipe()` and `dup2()`.

### Technical choices

- **One global variable, signal number only.** As required by the subject, `g_signal` is a `volatile sig_atomic_t` that stores the received signal and nothing else. The handler never touches the shell's data structures; the main loop reads the value and reacts.
- **Own environment list.** The environment is copied at startup into a `t_env` linked list, so `export` and `unset` can modify it freely. It is converted back to a `char **` only when calling `execve`.
- **Libft.** The project uses our own C library (`Libft/`), including `ft_printf` and `get_next_line`.

### Team

| | Part |
|---|---|
| **camansou** | Built-ins, execution, pipes, redirections, signals |
| **makoon** | Lexer, parsing, expansion |

## Instructions

### Requirements

- Linux or macOS
- `cc` and `make`
- GNU Readline (on Debian/Ubuntu: `sudo apt install libreadline-dev`)

### Build and run

```bash
git clone https://github.com/Camillia9/minishell.git
cd minishell
make
./minishell
```

### Makefile rules

| Rule | Effect |
|---|---|
| `make` | Builds `libft`, `get_next_line` and `minishell` |
| `make clean` | Removes object files |
| `make fclean` | Removes object files and binaries |
| `make re` | Full rebuild |

### Checking for leaks

`readline()` leaks memory by itself, which the subject allows. Leaks reported inside `libreadline` can be ignored; everything else must be clean.

```bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

## Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html), used as the reference for every behavior
- `man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 2 waitpid`, `man 2 sigaction`
- [Writing your own shell (Purdue University, CS 252)](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

### AI usage

AI (Claude) served as a learning tool:

- **Understanding concepts**: requesting explanations regarding system calls and mechanisms
  that were new to us, such as `execve`, file descriptor duplication using `dup2`, and signal handling with `sigaction`.
- **Clarifying Bash behavior**: verifying how Bash handles edge cases (quotes, `$?`, heredocs) before implementing them ourselves and testing against Bash.
- **README**: assistance with structuring this README file and phrasing the English text.

The entire codebase was written, tested, and debugged by the team.
