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
	// printf("\n%s: ",argv[i]);
 //    date = asctime(localtime(&buf.st_ctime));
 //    printf("\n%s", date);
 //    printf("%d mode\n", buf.st_mode);
 //    printf("%lld size\n", buf.st_size);
 //    printf("st_nlink %d\n", buf.st_nlink);
 //    printf("st_blksize %d\n", buf.st_blksize);
 //    printf("st_blocks %lld\n", buf.st_blocks);
 //    timeinfo = localtime(&buf.st_atime);
 //    strftime(buff, 20, "%b %d %H:%M", timeinfo);
 //    printf("st_atime: %s\n", buff);
 //    timeinfo = localtime(&buf.st_mtime);
 //    strftime(buff, 20, "%b %d %H:%M", timeinfo);
 //    printf("st_mtime: %s\n", buff);
 //    timeinfo = localtime(&buf.st_ctime);
 //    strftime(buff, 20, "%b %d %H:%M", timeinfo);
 //    printf("st_ctime: %s\n", buff);
     printf("ls -l: %s", mx_permission(argv[i]));
     printf("%d ", mx_count_link(argv[i]));
     printf("%s ", pw->pw_name);
     printf("%d ",pw->pw_gid);
     printf("%lld ", buf.st_size);
     char* str = ctime(&buf.st_atime);
     char *time1 = NULL;
     time_t current = time(0);
     if ( current - buf.st_atime >= 31536000 / 2) {

     }
     else {
        str += 4;
        time1 = strndup(str, 12);
     }
     printf("%s\n", time1);
    }
}

//Tue Jan 21 19:16:55 2020
// #include <sys/types.h>
// #include <pwd.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// int main() {
//  uid_t uid;
//  gid_t gid;
//  struct passwd *pw;
//  uid = getuid();
//  gid = getgid();
//  printf("User is %sn", getlogin());
//  printf("User IDs: uid=%d, gid=%d\n", uid, gid);
//  pw = getpwuid(uid);
//  printf(
//   "UID passwd entry:n name=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
//   pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
//  pw = getpwnam("root");
//  printf("root passwd entry:n");
//  printf("name=%s, uid=%d, gid=%d, home=%s, shell=%sn",
//   pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
//  exit(0);
// }
