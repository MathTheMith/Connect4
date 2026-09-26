#ifndef CONNECT4_H
# define CONNECT4_H

# include <stdlib.h>
# include "libft.h"

typedef enum e_state
{
	PLAYING,
	WIN_X,
	WIN_O,
	DRAW,
	QUIT
}	t_state;

typedef struct s_win
{
	int	x;
	int	y;
	int	dx;
	int	dy;
}	t_win;

typedef struct s_game
{
	int		top_row;
	int		min_col;
	int		max_col;
	int		rows;
	int		columns;
	char	**grid;
	char	current;
	t_win	win_pos;
	t_state	state;
}	t_game;

/* check_args.c */
int	is_number(char *str);
int	check_args(int ac, char **av);

/* grid.c */
int		init_game(t_game *game, int rows, int columns);
void	free_grid(char **grid, int rows);
void	free_game(t_game *game);
int		drop_piece(t_game *game, int col, char piece);

/* window.c */
bool	draw_gui_grid(t_game *game);

/* draw.c */
void	draw_grid(t_game *game);

/* rules.c */
t_state	check_connects(t_game *game, int x, int y);

/* game.c */
int		check_answer(char *response, t_game *game);
bool	get_placement(t_game *game);
void	print_result(t_game *game);
void	ai_play(t_game *game);
void	play_terminal(t_game *game);

int	get_best_move(t_game *game, int max_depth);

#endif
