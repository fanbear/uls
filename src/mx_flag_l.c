#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

char* mx_permission(const char* file);
int mx_count_link(const char* file);

int main(int argc, char** argv) {
    char *date;
    int ret;
    struct stat buf;
    char buff[20];
    struct tm * timeinfo;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
    struct passwd *pw;
    uid_t uid;
   
  
    for( int i = 1; i < argc; i++) {
    	if ((ret = lstat(argv[i], &buf))!=0)
    {
        fprintf(stderr, "stat failure error .%d", ret);
            abort();
    }
     pw = getpwuid(buf.st_uid);
     printf("%s", mx_permission(argv[i]));
     printf("%d ", mx_count_link(argv[i]));
     printf("%s ", pw->pw_name);
     printf("%d ",pw->pw_gid);
     printf("%lld ", buf.st_size);
     char* str = ctime(&buf.st_atime);
     char *time1 = NULL;
     time_t current = time(0);
     if ( current - buf.st_atime >= 31536000 / 2) {
            // str += 4;
            // time1 = strndup(str, 6);
            // str += 20;
     }
     else {
        str += 4;
        time1 = strndup(str, 12);
     }
     printf("%s ", time1);
     printf("%s\n", argv[i]);
    }
}

///Tue Jan 21 19:16:55 2020
