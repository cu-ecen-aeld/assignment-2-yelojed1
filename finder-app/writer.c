#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    // Setup syslog logging
    openlog("writer", LOG_PID, LOG_USER);

    // Check argument count
    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments (%d)", argc);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Check if write string is empty or NULL
    if (writestr == NULL || strlen(writestr) == 0) {
        syslog(LOG_ERR, "Empty write string specified");
        fprintf(stderr, "Error: Write string cannot be empty\n");
        closelog();
        return 1;
    }

    // Log the writing operation
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    // Open file for writing (create if doesn't exist, truncate if exists)
    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        syslog(LOG_ERR, "Could not create file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: Could not create file %s: %s\n", 
                writefile, strerror(errno));
        closelog();
        return 1;
    }

    // Write content to file
    ssize_t bytes_written = write(fd, writestr, strlen(writestr));
    if (bytes_written == -1) {
        syslog(LOG_ERR, "Failed to write to file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: Failed to write to file %s: %s\n", 
                writefile, strerror(errno));
        close(fd);
        closelog();
        return 1;
    }

    // Verify all bytes were written
    if (bytes_written != (ssize_t)strlen(writestr)) {
        syslog(LOG_ERR, "Partial write to file %s (wrote %zd of %zu bytes)", 
               writefile, bytes_written, strlen(writestr));
        fprintf(stderr, "Error: Partial write to file %s\n", writefile);
        close(fd);
        closelog();
        return 1;
    }

    // Close file
    if (close(fd) == -1) {
        syslog(LOG_ERR, "Failed to close file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: Failed to close file %s: %s\n", 
                writefile, strerror(errno));
        closelog();
        return 1;
    }

    // Close syslog
    closelog();
    return 0;
}
