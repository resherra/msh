#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


#include <unistd.h>
#include <stdio.h>

 
int main() {
    // Define the arguments for the clear command
    char *argv[] = {"clear", NULL};  // argv[0] is the command, argv[1] is NULL to end the array
    char *envp[] = {"TERM=xterm-256color",NULL};  // No additional environment variables

    // Use execve to replace the current process image with the clear command
    if (execve("/usr/bin/clear", argv, envp) == -1) {
        perror("execve");  // Print error if execve fails
    }

    // This line will NOT be executed if execve is successful
    printf("This won't be printed if execve succeeds\n");
    return 0;
}
