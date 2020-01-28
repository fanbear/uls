#include "uls.h"

static int max_links(st_general *gnr, int max, int i);
static int max_user_name(st_general *gnr, int max, int i);
static int max_group_name(st_general *gnr, int max, int i);
static int max_size(st_general *gnr, int max, int i);

int print_ls_l(char **data) {
    //t_file *array = malloc(argc * sizeof(t_file));
    st_general *gnr = (st_general*)malloc(sizeof(st_general));
	int i = 0;

    gnr->array_p = (t_file*)malloc(argc * sizeof(t_file));
    gnr->max_link = 0;
    gnr->max_size = 0;
    gnr->max_user = 0;
    gnr->max_group = 0;
    gnr->sum_blocks = 0;

    for(; data[i]; i++) {
        mx_get_inform(gnr, data[i], i);
        gnr->sum_blocks += gnr->array_p[i].blocks;
        gnr->max_link = max_links(gnr, gnr->max_link, i);
        gnr->max_size = max_size(gnr, gnr->max_size, i);
        gnr->max_user = max_user_name(gnr, gnr->max_user, i);
        gnr->max_group = max_group_name(gnr, gnr->max_group, i);
    }
    mx_output_l(gnr, i);
    
    //system("leaks -q uls");
}

static int max_links(st_general *gnr, int max, int i) {
	int j = mx_strlen(gnr->array_p[i].nlink);

	if(max < j)
		max = j;
	return max;
}

static int max_user_name(st_general *gnr, int max, int i) {
	int j = mx_strlen(gnr->array_p[i].user_name);

	if(max < j)
		max = j;
	return max;
}

static int max_group_name(st_general *gnr, int max, int i) {
	int j = mx_strlen(gnr->array_p[i].group_name);

	if(max < j)
		max = j;
	return max;
}

static int max_size(st_general *gnr, int max, int i) {
	int j = mx_strlen(gnr->array_p[i].file_size);

	if(max < j)
		max = j;
	return max;
}


// for(int i = 1; i < argc; i++) {
//         mx_printstr(gnr->array_p[i].permiss);
// 		mx_printstr("  ");
// 		mx_printint(gnr->array_p[i].nlink);
// 		mx_printstr("  ");
// 		mx_printstr(gnr->array_p[i].user_name);
// 		mx_printstr("  ");
// 		mx_printstr(gnr->array_p[i].group_name);
// 		mx_printstr("  ");
// 		mx_printstr(gnr->array_p[i].file_size);
// 		mx_printstr("  ");
// 		//mx_printstr(time1);
// 		mx_printstr("  ");
// 		mx_printstr(gnr->array_p[i].file_name);
// 		mx_printchar('\n');
//     }

//     printf("%d\n", sum_blocks);
//     printf("%d\n", gnr->max_link);
//     printf("%d\n", gnr->max_size);
//     printf("%d\n", gnr->max_group);
//     printf("%d\n", gnr->max_user);
//     


