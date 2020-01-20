#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

char* mx_permission(const char* file);

int main(int argc, char** argv) {
    char *date;
    int ret;
    struct stat buf;
    char buff[20];
    struct tm * timeinfo;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
  
    for( int i = 1; i < argc; i++) {
    	if ((ret = lstat(argv[i], &buf))!=0)
    {
        fprintf(stderr, "stat failure error .%d", ret);
            abort();
    }
	printf("\n%s: ",argv[i]);
    date = asctime(localtime(&buf.st_ctime));
    printf("\n%s", date);
    printf("%d mode\n", buf.st_mode);
    printf("%lld size\n", buf.st_size);
    printf("st_nlink %d\n", buf.st_nlink);
    printf("st_blksize %d\n", buf.st_blksize);
    printf("st_blocks %lld\n", buf.st_blocks);
    timeinfo = localtime(&buf.st_atime);
    strftime(buff, 20, "%b %d %H:%M", timeinfo);
    printf("st_atime: %s\n", buff);
    timeinfo = localtime(&buf.st_mtime);
    strftime(buff, 20, "%b %d %H:%M", timeinfo);
    printf("st_mtime: %s\n", buff);
    timeinfo = localtime(&buf.st_ctime);
    strftime(buff, 20, "%b %d %H:%M", timeinfo);
    printf("st_ctime: %s\n", buff);
     printf("PERMISSOIN : %s\n", mx_permission(argv[i]));
   }
}
