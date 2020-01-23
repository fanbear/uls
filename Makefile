NAME = uls

INC = uls.h

INCI = inc/uls.h

INCLIB = libmx/libmx.a

SRC = \
main.c \
mx_uls_no_flag.c \
mx_print_directory.c \
mx_uls_only.c \
mx_output.c \
mx_get_flags.c \
mx_args_to_struct.c \
mx_print_not_valid.c \
mx_arr_size.c \
mx_del_str_arr.c \
print_ls.c \
mx_del_struct.c \
mx_get_data_from_struct.c \
mx_get_window_size.c \


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

reinstall: uninstall install
