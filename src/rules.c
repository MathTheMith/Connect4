#include "connect4.h"

t_state check_connects(t_game *game, int x, int y)
{
	char piece = game->grid[y][x];
	int i = 0;
	while(i < 4)
	{
		if ((y + i < 0 || y + i >= game->rows || x < 0 || x >= game->columns || game->grid[y + i][x] != piece))
			break;
		if (i == 3)
		{
			game->win_pos.dx = 0;
			game->win_pos.dy = 1;
			game->win_pos.x = x;
			game->win_pos.y = y;
			if (game->grid[y][x] == 'X')
				return (WIN_X);
			return (WIN_O);
		}
		i++;
	}
	i = 0;
	while(i < 4)
	{
		if ((y - i < 0 || y - i >= game->rows || x - i< 0 || x- i >= game->columns || game->grid[y - i][x - i] != piece))
			break;
		if (i == 3)
		{
			game->win_pos.dx = -1;
			game->win_pos.dy = -1;
			game->win_pos.x = x;
			game->win_pos.y = y;
			if (game->grid[y][x] == 'X')
				return (WIN_X);
			return (WIN_O);
		}
		i++;
	}
	i = 0;
	while(i < 4)
	{
		if ((y < 0 || y >= game->rows || x + i< 0 || x + i >= game->columns || game->grid[y][x + i] != piece))
			break;
		if (i == 3)
		{
			game->win_pos.dx = 1;
			game->win_pos.dy = 0;
			game->win_pos.x = x;
			game->win_pos.y = y;
			if (game->grid[y][x] == 'X')
				return (WIN_X);
			return (WIN_O);
		}
		i++;
	}
	i = 0;
	while(i < 4)
	{
		if ((y + i < 0 || y + i >= game->rows || x - i < 0 || x - i >= game->columns || game->grid[y + i][x - i] != piece))
			break;
		if (i == 3)
		{
			game->win_pos.dx = -1;
			game->win_pos.dy = 1;
			game->win_pos.x = x;
			game->win_pos.y = y;
			if (game->grid[y][x] == 'X')
				return (WIN_X);
			return (WIN_O);
		}
		i++;
	}

	return PLAYING;
}

t_state	get_game_state(t_game *game)
{
	int	x;
	int	y;
	bool full;

	full = true;
	x = 0;
	while (x < game->columns)
	{
		y = 0;
		while (y < game->rows)
		{
			if (game->grid[y][x] != '.' && check_connects(game, x, y) != PLAYING)
			{
				if (game->grid[y][x] == 'X')
					return (WIN_X);
				return (WIN_O);
			}
			if (game->grid[y][x] == '.')
				full = false;
			y++;
		}
		x++;
	}
	if (full)
		return (DRAW);
	return (PLAYING);
}
