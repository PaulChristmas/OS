#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "bufio.h"

#define BUF_SIZE 4096

int main() {
    struct buf_t * buf = buf_new(BUF_SIZE);
    if (buf == NULL) {
    fprintf(stderr, "Error");
    return -1;
}
   
    while (1) {
        ssize_t result_read = buf_fill(STDIN_FILENO, buf, buf_capacity(buf));
        if (result_read < 0) {
            buf_flush(STDOUT_FILENO, buf, buf_size(buf));
            fprintf(stderr, "Error %s\n", strerror(errno));
            buf_free(buf);
            return -1;
        } else if (result_read == 0) {
            break;            
        } else {
            ssize_t result_write = buf_flush(STDOUT_FILENO, buf, buf_size(buf));
            if (result_write < 0) {
                fprintf(stderr, "Error %s\n", strerror(errno));
                buf_free(buf);
                return -1;
            }
        }
    }
    if (buf_size(buf) > 0) {
        buf_flush(STDOUT_FILENO, buf, buf_size(buf));
    }
    buf_free(buf);
    return 0;
}
