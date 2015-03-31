#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "bufio.h"

#ifdef DEBUG

    #define BUF_EXISTS(condition) if (condition == NULL) {abort();}
    
#else

    #define BUF_EXISTS(condition)
    
#endif

struct buf_t* buf_new(size_t capacity) {
    struct buf_t * res = (struct buf_t *) malloc(sizeof(struct buf_t));
    if (res == NULL) {
        return NULL;
    }
    res->data = malloc(capacity);
    if (res->data == NULL) {
        free(res);
        return NULL;
    }
    res->size = 0;
    res->capacity = capacity;
    return res;
}

void buf_free(struct buf_t * buf) {
    BUF_EXISTS(buf)
    free(buf->data);
    free(buf);
}

size_t buf_capacity(struct buf_t * buf) {
    BUF_EXISTS(buf)
    return buf->capacity;
}

size_t buf_size(struct buf_t * buf) {
    BUF_EXISTS(buf)
    return buf->size;
}

ssize_t buf_fill(fd_t fd, struct buf_t *buf, size_t required) {
    BUF_EXISTS(buf)
    ssize_t result_read = 0;
    while (buf->size < buf->capacity && buf->size < required) {
        result_read = read(fd, buf->data + buf->size, buf->capacity - buf->size);
        if (result_read < 0) {
            return -1;
        } else if (result_read == 0) {
            break;
        } else {
            buf->size += result_read;
        }
    }
    return buf->size;
}

ssize_t buf_flush(fd_t fd, struct buf_t *buf, size_t required) {
    BUF_EXISTS(buf)
    ssize_t result_write = 0;
    ssize_t result = 0;
    while (0 < buf->size && result < required) {
        result_write = write(fd, buf->data + result, buf->size);
        if (result_write < 0) {
              int temp = errno;
            memcpy(buf->data, buf->data + result, buf->size);
            errno = temp;
            return -1;
        } else {
            result += result_write;
            buf->size -= result_write;
        }
    }
    if (buf->size > 0) {
        memcpy(buf->data, buf->data + result, buf->size);
    }
    return result;
}
