
.PHONY : all fclean fclean-all re bonus clean-bin clean-obj FORCE
CC = cc
CFLAGS = -Wextra -Wall -Werror -MMD -MP
NO_DIR = --no-print-directory
MAKE := $(MAKE) -j $(NO_DIR)
NAME = connect4
CFLAGS_DEBUG = -Wall -Wextra -g3 -D DEBUG=1
CC_DEBUG = clang
CC_DEBUG_CFLAGS = -g3 -D DEBUG=1 -Weverything -Wno-padded -pedantic -O2 -Wwrite-strings -Wconversion -Wno-suggest-override -Wno-suggest-destructor-override -Wno-incompatible-pointer-types-discards-qualifiers -Wno-disabled-macro-expansion
#############################################################################################
#                                                                                           #
#                                         DIRECTORIES                                       #
#                                                                                           #
#############################################################################################

P_SRC = src/
P_INC = inc/
P_OBJ = .obj/
LIBFT_DIR = Libft/
LIBFT = $(LIBFT_DIR)libft.a
RAYLIB_REPO = https://github.com/raysan5/raylib.git
RAYLIB_VERSION = 5.5
RAYLIB_PATH = raylib/
RAYLIB_DIR = $(RAYLIB_PATH)src/
RAYLIB = $(RAYLIB_DIR)libraylib.a
LIBS = -L $(LIBFT_DIR) -lft -L $(RAYLIB_DIR) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

#############################################################################################
#                                                                                           #
#                                           FILES                                           #
#                                                                                           #
#############################################################################################

SRC = main.c check_args.c grid.c window.c draw.c rules.c game.c

#############################################################################################
#                                                                                           #
#                                        MANIPULATION                                       #
#                                                                                           #
#############################################################################################
SRCS = \
	$(addprefix $(P_SRC), $(SRC)) \

OBJS =  \
	$(subst $(P_SRC), $(P_OBJ), $(SRCS:.c=.o)) \

P_OBJS = $(subst $(P_SRC), $(P_OBJ), $(SRCS))

DEPS = $(OBJS:%.o=%.d)

#############################################################################################
#                                                                                           #
#                                          RULES                                            #
#                                                                                           #
#############################################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(RAYLIB) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) && \
	echo "$(Green)Creating executable $@$(Color_Off)" || \
	{ echo "$(Red)Error creating $@$(Color_Off)"; exit 1; }

$(P_OBJ)%.o: $(P_SRC)%.c | $(RAYLIB)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(P_INC) -I $(LIBFT_DIR) -I $(RAYLIB_DIR) -c $< -o $@ && \
	echo "$(Cyan)Compiling $<$(Color_Off)" || \
	{ echo "$(Red)Error compiling $<$(Color_Off)"; exit 1; }

$(LIBFT): FORCE
	@$(MAKE) -C $(LIBFT_DIR)

FORCE:

$(RAYLIB):
	@if [ ! -d $(RAYLIB_PATH) ]; then \
		echo "$(Yellow)Downloading raylib $(RAYLIB_VERSION)$(Color_Off)"; \
		git clone -q --depth 1 --branch $(RAYLIB_VERSION) -c advice.detachedHead=false $(RAYLIB_REPO) $(RAYLIB_PATH) && \
		rm -rf $(RAYLIB_PATH).git; \
	fi
	@echo "$(Yellow)Compiling raylib$(Color_Off)"
	@$(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_DESKTOP > /dev/null 2>&1

#############################################################################################
#                                                                                           #
#                                      Other RULES                                          #
#                                                                                           #
#############################################################################################

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -rfd $(P_OBJ)
	rm -rfd $(DEPS)

clean-bin:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

clean-obj:
	@$(MAKE) clean

fclean:
	@$(MAKE) clean-obj
	@$(MAKE) clean-bin

fclean-all: fclean
	@if [ -d $(RAYLIB_DIR) ]; then $(MAKE) -C $(RAYLIB_DIR) clean > /dev/null; fi

re:
	@$(MAKE) fclean
	@$(MAKE) all

clear: clean
fclear: fclean
flcean: fclean
flcear: fclean

#############################################################################################
#                                                                                           #
#                                           DEBUG                                           #
#                                                                                           #
#############################################################################################

debug:
	@$(MAKE) $(NAME) CFLAGS="$(CFLAGS_DEBUG)"

#############################################################################################
#                                                                                           #
#                                         COSMETIC                                          #
#                                                                                           #
#############################################################################################

Color_Off=\033[0m       # Text Reset

Black=\033[0;30m
Red=\033[0;31m
Green=\033[0;32m
Yellow=\033[0;33m
Blue=\033[0;34m
Purple=\033[0;35m
Cyan=\033[0;36m
White=\033[0;37m

On_Black=\033[40m
On_Red=\033[41m
On_Green=\033[42m
On_Yellow=\033[43m
On_Blue=\033[44m
On_Purple=\033[45m
On_Cyan=\033[46m
On_White=\033[47m

-include $(DEPS)% 