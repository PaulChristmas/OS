#include <unistd.h>
#include <stdlib.h>
#include <helpers.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 4096

void back_to_front(int length, char* buf) {
	int back, front = length - 1;
	char temp;
	for (back = 0; back < front; back++, front--){
		temp = buf[back];
		buf[back] = buf[front];
		buf[front] = temp;
	}
}

int main(int argc, char* argv[]) {
	ssize_t result_read = 0, result_write = 0, shift = 0;
	int i = 0, j = 0;
	char buf[BUF_SIZE];
	
	while (1) {
		result_read = read_until(STDIN_FILENO, buf + shift, BUF_SIZE - shift, ' ');
		if (result_read == -1) {
		    char* exception = strerror(errno);
    		write_(STDERR_FILENO, exception, strlen(exception)); 
			return 1;
		}
		if (result_read == 0) {
			if (shift == 0) {
				return 0;
			}
			back_to_front(shift, buf);
			result_write = write_(STDOUT_FILENO, buf, shift);
			if (result_write == -1) {
			    char* exception = strerror(errno);
    		    write_(STDERR_FILENO, exception, strlen(exception)); 
				return 1;
			}
			return 0;
		}
		i = shift;
		shift += result_read;
		j = 0;
		for (; i < shift; i++) {
			if (buf[i] == ' ') {
				back_to_front(i - j, buf + j);
				result_write = write_(STDOUT_FILENO, buf + j, i - j + 1);
				if (result_write == -1) {
				    char* exception = strerror(errno);
    		        write_(STDERR_FILENO, exception, strlen(exception)); 
					return 1;
				}
				j = i + 1;
			}
		}
		if (shift- j == BUF_SIZE) {
			back_to_front(shift, buf);
			result_write = write_(STDOUT_FILENO, buf, shift);
			if (result_write == -1) {
			    char* exception = strerror(errno);
    		    write_(STDERR_FILENO, exception, strlen(exception)); 
				return 1;
			}
			j = shift;
		}
		shift -= j;
		for (i = 0; i < shift; i++) {
			buf[i] = buf[i + j];
		}
	}
}
