#include "connect4.h"
#include <stdlib.h>
#include <time.h>
void	free_grid(char **grid, int rows)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < rows)
		free(grid[i++]);
	free(grid);
}

void	free_game(t_game *game)
{
	free_grid(game->grid, game->rows);
	game->grid = NULL;
}

int	init_game(t_game *game, int rows, int columns)
{
	int	i;

	game->rows = rows;
	game->columns = columns;
	game->moves_count = 0;
	game->top_row = rows;
	game->min_col = columns - 1;
	game->max_col = 0;
	game->temp_top_row = game->top_row;
	game->temp_min_col = game->min_col;
	game->temp_max_col = game->max_col;
	game->win_pos = (t_win){0, 0, 0, 0};
    srand(time(NULL));
	game->current = rand() % 2 == 0 ? 'X' : 'O';
	game->state = PLAYING;
	game->grid = malloc(sizeof(char *) * rows);
	if (!game->grid)
		return (0);
	i = 0;
	while (i < rows)
	{
		game->grid[i] = malloc(sizeof(char) * columns);
		if (!game->grid[i])
		{
			free_grid(game->grid, i);
			game->grid = NULL;
			return (0);
		}
		ft_memset(game->grid[i], '.', columns);
		i++;
	}
	return (1);
}

int	drop_piece(t_game *game, int col, char piece)
{
	int	row;

	row = game->rows - 1;
	while (row >= 0 && game->grid[row][col] != '.')
		row--;
	if (row >= 0)
		game->grid[row][col] = piece;
	game->moves_count++;
	if (row < game->temp_top_row)
		game->temp_top_row = row;
	if (col > game->temp_max_col)
		game->temp_max_col = col;
	if (col < game->temp_min_col)
		game->temp_min_col = col;
	return (row);
}
