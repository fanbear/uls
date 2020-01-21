#include <grp.h>
#include <sys/types.h>

void mx_user(const char* str) {
	struct passwd *pw;
	pw = getpwuid(uid);

	

}