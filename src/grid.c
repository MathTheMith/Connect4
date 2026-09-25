#include "connect4.h"

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
