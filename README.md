# Custom minishell Project (C)

This project is a custom shell implementation written in C. It provides a basic command-line interface with support for executing external commands, handling simple built-in commands, and managing processes. It is designed to demonstrate fundamental operating system concepts and C programming skills.

## Features

* **Command Execution:** Executes external commands using `fork()`, `exec()`, and `wait()`.
* **Built-in Commands:** (Expand this list with the actual built-in commands your shell supports, for example: `cd`, `exit`, `help`, etc.)
    * `exit`: Exits the shell.
    * `cd`: Changes the current working directory.
    * (Add other built-in commands here)
* **Basic Error Handling:** Handles common errors such as command not found.
* **Dockerized:** Easily run the shell within a consistent environment using Docker.

## Prerequisites

* **Docker:** To run the project using Docker.
* **GCC (Optional):** If you wish to compile the project directly without Docker.

## Running the Shell

### Using Docker (Recommended)

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/ApplexX7/minishell.git
    cd minishell
    ```
2.  **Build the Docker Image:**
    ```bash
    docker build -t custom-shell .
    ```
3.  **Run the Docker Container:**
    ```bash
    docker run -it custom-shell
    ```
    This will start the shell within the container. You can now interact with it by typing commands.

### Compiling and Running Directly (Optional)

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/ApplexX7/minishell.git
    cd minishell
    ```
2.  **Compile the Source Code:**
    ```bash
    make all clean #or whatever your main c file is named.
    ```
3.  **Run the Shell:**
    ```bash
    ./minishell
    ```

## Usage

Once the shell is running, you can enter commands at the prompt.

* **External Commands:** Type the name of an executable file (e.g., `ls`, `pwd`) followed by any arguments.
* **Built-in Commands:** Use the built-in commands listed above (e.g., `cd /path/to/directory`, `exit`).

## Project Structure
minishell/

├── main.c       # Main source file

├── Dockerfile   # Docker configuration file

├── README.md    # This file

├── parsing/     # Parsing files, headers, etc.

├── p_execution/ # Execution files, etc.

├── builtins/    #built-ins command in bash.

├── Makefile     #management file for making the executable file.

# Contributing

If you would like to contribute to this project, please feel free to submit a pull request.

## Example
   ```
   $ pwd
   /home/user
   $ ls
   file1.txt  file2.c  shell
   $ cd /tmp
   $ pwd
   /tmp
   $ exit```
