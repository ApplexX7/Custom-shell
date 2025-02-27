FROM ubuntu:24.04

# Update and upgrade the system
RUN apt-get update --fix-missing && apt-get upgrade -y

# Install build dependencies

RUN apt -y  install build-essential libreadline-dev

WORKDIR /minishell

# Copy source code
COPY . /minishell/

# Build the application
RUN make all clean

# Run the application
CMD ["./minishell"]
