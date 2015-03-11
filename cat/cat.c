#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <helpers.h>

void throw_error() {
    char* error = strerror(errno);
    write_(STDERR_FILENO, error, strlen(error) * sizeof(char));
}

int main(int argc, char* argv[]) {
    char buf[4096];
    ssize_t result_read = 0;
    ssize_t result_written = 0;

    while(1) {
        result_read = read_(STDIN_FILENO, buf, sizeof(buf));
        if(result_read == -1) {
            throw_error();
            return 1;
        }

        result_written = write_(STDOUT_FILENO, buf, result_read);
        if(result_written == -1) {
            throw_error();
            return 1;
        }
        
        if(result_read < sizeof(buf)) {
            return 0;
        }
    }
}