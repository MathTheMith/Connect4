#ifndef CONNECT4_H
# define CONNECT4_H

# include <stdlib.h>
# include "libft.h"

typedef struct s_game
{
	int		rows;
	int		columns;
	char	**grid;
}	t_game;

/* check_args.c */
int	is_number(char *str);
int	check_args(int ac, char **av);

/* grid.c */
int		init_game(t_game *game, int rows, int columns);
void	free_grid(char **grid, int rows);
void	free_game(t_game *game);

/* window.c */
void	draw_gui_grid(t_game *game);

/* draw.c */
void	draw_grid(t_game *game);

#endif
