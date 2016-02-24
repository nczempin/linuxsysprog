#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFSZ 1024

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)


void perms(mode_t mode){
	if (mode & S_IFDIR){
		printf("d");
	}else {
		printf("-");
	}
	printf("rwxrwxr-x");
}

struct linux_dirent {
	long           d_ino;
	off_t          d_off;
	unsigned short d_reclen;
	char           d_name[];
};

//TODO: sort
//TODO: colour
//TODO: actual permissions
//TODO: line formatting

int main()
{
	struct linux_dirent *dir;
	struct stat st;
	struct passwd *pw;
	struct group *grp;
	char buf[BUFSZ], *bp, *ftime;
	char buf2[160];
	int dfd, fd, nread;
	struct linux_dirent *d;
	int bpos;
	char d_type;

	dfd = open(".", O_RDONLY|O_DIRECTORY);
	if (dfd == -1)
	{
		handle_error("open");
	}
	memset(buf, 0, BUFSZ);
	for( ; ; ) {
		nread = syscall(SYS_getdents,dfd, buf, BUFSZ);
		if (nread == -1)
			handle_error("getdents");

		if (nread == 0)
			break;
		for (bpos = 0; bpos < nread;) {
			d = (struct linux_dirent *) (buf + bpos);
			bpos += d->d_reclen;

			bp = buf;
			dir = (struct linux_dirent *)buf;
			if (dir->d_reclen != 0) {
				stat(d->d_name, &st);
				ftime = ctime_r(&st.st_mtime,buf2);
				buf2[16]='\0';
				pw = getpwuid(st.st_uid);
				grp = getgrgid(st.st_gid);
				perms(st.st_mode);
				printf("%3d ",st.st_nlink);
				if (pw!=0){
					printf("%-8s ",pw->pw_name);
				}
				if (grp!=0) 
				{
					printf("%-8s ", grp->gr_name);
				}
				printf("%9d ", st.st_size);
				printf("%s ",&buf2[4]);
				printf("%s\n",d->d_name);
				/*
					 printf("%3d %-8s %-7s %9d %s %s\n",
					 st.st_nlink, pw->pw_name, grp->gr_name,    
					 st.st_size, ftime, dir->d_name);
					 */
			}
			bp = bp + dir->d_reclen;
			dir = (struct linux_dirent *)(bp);
		}
		memset(buf, 0, BUFSZ);
	}
	return 0;
}
