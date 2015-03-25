#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include "helpers.h"
#include <errno.h>
#include <sys/wait.h>

ssize_t read_(int fd, void* buf, size_t count) {
    int result = 0;
    int result_read = 0;
    while(1) {
        result = read(fd, buf, count);
        if(result == count) {
            return result_read + result;
        }
        if(result == -1) {
            return -1;
        }
        
        if(result == 0) {
            return result_read;
        }

        result_read += result;
        buf += result;
        count -= result;
    }
}

ssize_t read_until(int fd, void* buf, size_t count, char delimeter) {
    int result = 0;
    int result_read = 0;
    while(1) {
        result = read(fd, buf, count);

        int i;
        for(i = 0; i < result; i++) {
            if(((char*) buf)[i] == delimeter) {
                return result + result_read;
            }
        }

        if(result == count) {
            return result + result_read;
        }

        if(result == -1) {
           return -1;
        }

        if(result == 0) {
            return result_read;
        }

        result_read += result;
        buf += result;
        count -= result;
    }
}

ssize_t write_(int fd, void* buf, size_t count) {
    int result = 0;
    int result_read = 0;
    while(1) {
        result = write(fd, buf, count);

        if(result == count) {
            return result_read + result;
        }

        if(result == -1) {
            return -1;
        }

        result_read += result;
        buf += result;
        count -= result;
    }
}

int spawn(const char * file, char * const argv []) {
   int pid = fork();
    if (pid == -1) {
        char* exception = strerror(errno);
    	write_(STDERR_FILENO, exception, strlen(exception)); 
        return -1;
    }
    if (pid == 0) {
        int s = execvp(file, argv);
        if (s == -1) {
            char* exception = strerror(errno);
    		write_(STDERR_FILENO, exception, strlen(exception)); 
            return -1;
        }
        
    } else {
        int status;
        wait(&status);
        if(!WIFEXITED(status)) {
            char* exception = strerror(errno);
    		write_(STDERR_FILENO, exception, strlen(exception)); 
            return -1;
        }
        return WEXITSTATUS(status);
    }
    return -1;
}
