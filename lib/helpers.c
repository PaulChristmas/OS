#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "helpers.h"

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