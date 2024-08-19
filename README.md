# Minishell - A Simple Unix Shell Replica

Welcome to **Minishell**! This project is a basic replica of a Unix shell, specifically inspired by Bash, and is implemented in C.

## Key Features

- **Command Execution**: Execute user commands and executables using the `execv` system call.
- **Built-in Commands**: Includes implementations of essential shell commands like `cd`, `pwd`, `echo`, `export`, `unset`, `exit`, and `env`.
- **Pipes and Redirections**: Supports basic pipe functionality and input/output redirection.
- **Signal Handling**: Basic handling of signals for better control over shell behavior.
- **Environment Management**: Handles environment variables, allowing users to view, modify, and maintain them.

## Usage

1. Clone this repository:
    ```bash
    git clone https://github.com/tde-brui/dvan-kle/minishell.git
    ```
2. Compile the project using the provided Makefile:
    ```bash
    make
    ```
3. Run the shell:
    ```bash
    ./minishell
    ```

Minishell provides a command-line interface that behaves similarly to Bash.

## Examples

```bash
ls -l
cat Makefile | grep 'a'
env | grep HOME
export program=minishell
exit 100
