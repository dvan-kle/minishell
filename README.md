# Minishell - A basic replica of a Unix shell.
Welcome to minishell!
This project replicates the basic functionality of a unix shell, more specifically Bash.
Written in C.

## Key Features
~ Command execution: Allows users to execute commands and executables, using the execv command.

~ Implementation of built-in commands: 'cd', 'pwd', 'echo', 'export', 'unset', 'exit' 'env'.

~ Pipes and redirections: Basic implementation of the pipe functionality and input/output redirection.

~ Signals: Basic signal handling.

~ Environment: Basic implementation and maintenance of environment variables.

## Usage
1. Clone this repository: 'git clone https://github.com/tde-brui/dvan-kle/minishell.git'.
2. Compile the project using its Makefile: 'make'.
3. Run the project: './minishell'

The program provides a command-line that works similarly to bash.

//Examples
ls -l
cat Makefile | grep 'a'
env | grep HOME
export program=minishell
exit 100
