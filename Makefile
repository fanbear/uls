NAME = uls

INC = uls.h

INCI = inc/uls.h

INCLIB = libmx/libmx.a

SRC = \
main.c \
mx_sort_args.c \
mx_get_dir_entry.c \
mx_get_max_value_in_dirs.c \
mx_get_max_value_in_files.c \
mx_get_flags.c \
mx_args_to_struct.c \
mx_add_dirs_entry.c \
mx_print_not_valid.c \
mx_arr_size.c \
mx_del_str_arr.c \
mx_del_args_struct.c \
mx_print_ls_multy_colomn.c \
mx_print_multy_colomn_g.c \
mx_del_dirs_struct.c \
mx_get_data_from_struct.c \
mx_get_window_size.c \
mx_sort_data.c \
mx_print_ls_monocolomn.c \
mx_print.c \
mx_check_on_access.c \
mx_get_stat.c \
mx_print_ls_l.c \
\
\
mx_permission.c \
mx_print_flag_mp.c \
mx_recursive_open_dirs.c \
mx_quicksort_r.c \
mx_print_file_ls.c \
mx_print_info.c \
mx_print_dirs_ls.c \
mx_color_output.c \
mx_major_minor_size.c \
mx_colored_name.c \
mx_del_stat_struct.c \

SRCS = $(addprefix src/, $(SRC))

OBJ = $(SRC:%.c=%.o)

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@make -C libmx
	@cp $(SRCS) .
	@cp $(INCI) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@clang $(CFLAGS) $(INCLIB) $(OBJ) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJ) ./obj

uninstall: clean
	@rm -rf $(NAME) $(INCLIB)

clean:
	@rm -rf $(SRC) $(OBJ) $(INC)
	@rm -rf ./obj

reinstall: uninstall all
