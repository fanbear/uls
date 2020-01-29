#include "uls.h"

static void print_space(int max_elem, char* str) {
	for(int j = 0; j < max_elem - mx_strlen(str); j++) {
		mx_printchar(' ');
	}
}

static void print_total(int sum_total) {
	mx_printstr("total ");
	mx_printint(sum_total);
	mx_printchar('\n');
}
void mx_output_l(st_general *gnr, int argc) {
	print_total(gnr->sum_blocks);
	for (int i = 0; i < argc; i++) {
		mx_printstr(gnr->array_p[i].permiss);
		mx_printstr("  ");
		print_space(gnr->max_link, gnr->array_p[i].nlink);
		mx_printstr(gnr->array_p[i].nlink);
		mx_printstr(" ");
		mx_printstr(gnr->array_p[i].user_name);
		print_space(gnr->max_user, gnr->array_p[i].user_name);
		mx_printstr("  ");
		mx_printstr(gnr->array_p[i].group_name);
		print_space(gnr->max_group, gnr->array_p[i].group_name);
		mx_printstr("  ");
		print_space(gnr->max_size, gnr->array_p[i].file_size);
		mx_printstr(gnr->array_p[i].file_size);
		mx_printstr(" ");
		mx_printstr(gnr->array_p[i].time1);
		mx_printstr(" ");
		mx_printstr(gnr->array_p[i].file_name);
		mx_printchar('\n');
	}
}
