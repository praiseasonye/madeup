#include "main.h"

int write_command_to_file(const char* filename) {
    char command[BUFFSIZE];
    int file_descriptor;
    ssize_t bytes_read, bytes_written;

   
    bytes_read = read(STDIN_FILENO, command, sizeof(command));

    if (bytes_read == -1) {
        perror("Error: Unable to read input.");
        return -1;
    }

   
    file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (file_descriptor == -1) {
        perror("Error: Unable to write to the file.");
        return -1;
   
    }
    bytes_written = write(file_descriptor, command, bytes_read);

    if (bytes_written == -1) {
        perror("Error: Unable to write to the file.");
        close(file_descriptor);
        return -1;
    }

    return file_descriptor;
}

