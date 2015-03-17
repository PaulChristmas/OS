#include <unistd.h>
#include <stdlib.h>
#include <helpers.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 4096

void back_to_front(int length, char* buf) {
	int back, front = length-1;
	char temp;
	for (back = 0; back < front; back++, front--){
		temp = buf[back];
		buf[back] = buf[front];
		buf[front] = temp;
	}
}

int main(int argc, char* argv[]) {
    ssize_t result_read = 0, result_write = 0;
    int i = 0, j = 0;
    char buf[BUF_SIZE];

    while(1) {
        ssize_t shift = result_read;
        result_read = read_until(STDIN_FILENO, buf + shift * sizeof(char), sizeof(buf) - shift * sizeof(char), ' ');
        if (result_read <= 0) {
            back_to_front(shift, buf);
            result_write = write_(STDOUT_FILENO, buf, shift * sizeof(char));

            if (result_write == -1) {          
        	char* exception = strerror(errno);
    		write_(STDERR_FILENO, exception, strlen(exception) * sizeof(char));                         
        	return 1;                               
   	    }

            if (result_read == -1) {          
        	char* exception = strerror(errno);
    		write_(STDERR_FILENO, exception, strlen(exception) * sizeof(char));                         
        	return 1;                               
   	    }
            

            if (result_read == 0) {
                return 0;
            }
        }

        result_read += shift;
        shift = 0;
        for (i = 0; i < result_read; i++) {
            if(buf[i] == ' ') {
                back_to_front(i - shift, buf + shift * sizeof(char));
                result_write = write_(STDOUT_FILENO, buf + shift * sizeof(char), (i + 1 - shift) * sizeof(char));

                if (result_write == -1) {          
        	char* exception = strerror(errno);
    		write_(STDERR_FILENO, exception, strlen(exception) * sizeof(char));                         
        	return 1;                               
   	        }
                shift = i;
            }
        }

        result_read -= (shift + 1) * sizeof(char);
        if(result_read > 0) {
            memmove(buf, buf + (shift + 1) * sizeof(char), result_read);
        }
    }
}
