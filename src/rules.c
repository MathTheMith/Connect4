#include "connect4.h"

static int	count_side(t_game *game, int x, int y, int dx, int dy)
{
	char	piece;
	int		count;

	piece = game->grid[y][x];
	count = 0;
	x += dx;
	y += dy;
	while (y >= 0 && y < game->rows && x >= 0 && x < game->columns
		&& game->grid[y][x] == piece)
	{
		count++;
		x += dx;
		y += dy;
	}
	return (count);
}

static bool	check_axis(t_game *game, int x, int y, int dx, int dy)
{
	int	before;
	int	after;

	before = count_side(game, x, y, -dx, -dy);
	after = count_side(game, x, y, dx, dy);
	if (before + 1 + after < 4)
		return (false);
	game->win_pos.x = x - before * dx;
	game->win_pos.y = y - before * dy;
	game->win_pos.dx = dx;
	game->win_pos.dy = dy;
	return (true);
}

static bool	is_full(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->columns)
	{
		if (game->grid[0][x] == '.')
			return (false);
		x++;
	}
	return (true);
}

t_state	check_connects(t_game *game, int x, int y)
{
	if (check_axis(game, x, y, 1, 0) || check_axis(game, x, y, 0, 1)
		|| check_axis(game, x, y, 1, 1) || check_axis(game, x, y, 1, -1))
	{
		if (game->grid[y][x] == 'X')
			return (WIN_X);
		return (WIN_O);
	}
	if (is_full(game))
		return (DRAW);
	return (PLAYING);
}
