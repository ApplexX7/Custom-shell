FROM ubuntu:24.04

# Update and upgrade the system
RUN apt-get update --fix-missing && apt-get upgrade -y

# Install build dependencies
RUN apt-get install -y libreadline6 libreadline6-dev

# Copy source code
COPY ./builtins ./Libft-42 ./p_execution ./parsing main.c Makefile minishell_parts.c ./

# Build the application
RUN make all

# Run the application
CMD ["./minishell"]