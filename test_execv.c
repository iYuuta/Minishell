#include <unistd.h>
#include <stdio.h>

int main() {
    char *args[] = {"/bin/ls", "-a" "", NULL};
    execv(args[0], args);
    perror("execv"); // execv only returns on error
    return 1;
}