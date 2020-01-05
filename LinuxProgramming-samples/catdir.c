#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#ifdef linux
# define _GNU_SOURCE
# include <linux/types.h>
# include <linux/dirent.h>
# include <linux/unistd.h>
_syscall3(int, getdents, uint, fd, struct dirent *, dirp, uint, count)
#else
# include <dirent.h>
#endif

int
main(int argc, char *argv[])
{
    int fd;
    
    if (argc < 2) {
        fprintf(stderr, "missing dirname\n");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror(argv[1]);
        exit(1);
    }
    for (;;) {
#if defined(linux)
        struct dirent ent;
        int n;
        
        n = getdents(fd, &ent, sizeof ent);
        if (n < 0) {
            perror("getdents(2)");
            exit(1);
        }
        if (n == 0) break;
        write(STDOUT_FILENO, (char*)&ent, sizeof ent);
#elif defined(__digital__) && defined(__unix__)
        char buf[1024];
	long basep;
        int n;
        
        n = getdirentries(fd, buf, sizeof buf, &basep);
        if (n < 0) {
            perror("getdirentries(2)");
            exit(1);
        }
        if (n == 0) break;
        write(STDOUT_FILENO, buf, sizeof buf);
#else
        char buf[1024];
        int n;
        
        n = read(fd, buf, sizeof buf);
        if (n < 0) {
            perror("read(2)");
            exit(1);
        }
        if (n == 0) break;
        write(STDOUT_FILENO, buf, sizeof buf);
#endif
    }
    exit(0);
}
