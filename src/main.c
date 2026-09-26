#include "connect4.h"

static void	remove_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

int	check_answer(char *response, t_game *game)
{
	int	col;

	remove_newline(response);
	if (!is_number(response))
	{
		ft_putendl_fd("Please enter a number !", 2, true);
		return (0);
	}
	col = ft_atoi(response);
	if (col < 1 || col > game->columns)
	{
		ft_putendl_fd("You need to be in the range of columns", 2, true);
		return (0);
	}
	if (game->grid[0][col - 1] != '.')
	{
		ft_putendl_fd("This column is full !", 2, true);
		return (0);
	}
	return (1);
}

bool check_connects(t_game *game, int x, int y)
{
	char piece = game->grid[y][x];
	int i = 0;
	while(i < 4)
	{
		if ((y + i < 0 || y + i >= game->rows || x < 0 || x >= game->columns || game->grid[y + i][x] != piece))
			break;
		if (i == 3)
			return true;
		i++;
	}
	i = 0;
	while(i < 4)
	{
		if ((y - i < 0 || y - i >= game->rows || x - i< 0 || x- i >= game->columns || game->grid[y - i][x - i] != piece))
			break;
		if (i == 3)
			return true;
		i++;
	}
	i = 0;
	while(i < 4)
	{
		if ((y < 0 || y >= game->rows || x + i< 0 || x + i >= game->columns || game->grid[y][x + i] != piece))
			break;
		if (i == 3)
			return true;
		i++;
	}
	i = 0;
	while(i < 4)
	{
		if ((y + i < 0 || y + i >= game->rows || x - i < 0 || x - i >= game->columns || game->grid[y + i][x - i] != piece))
			break;
		if (i == 3)
			return true;
		i++;
	}


	return false;
}


bool is_finished(t_game *game)
{
	int x = 0;
	int y = 0;

	while(x < game->columns)
	{
		y = 0;
		while(y < game->rows)
		{
			if (game->grid[y][x] != '.' && check_connects(game, x, y))
				return true;
			y++;
		}
		x++;
	}
	return false;
}
bool	get_placement(t_game *game, bool player)
{
	char	*response;
	int		col;

	col = -1;
	while (col == -1)
	{
		ft_putendl_fd("Place a piece between 1-", 1, false);
		ft_putnbr_fd(game->columns, 1);
		ft_putendl_fd(": ", 1, false);
		response = get_next_line(0);
		if (!response)
		{
			ft_putendl_fd("", 1, true);
			return (false);
		}
		if (check_answer(response, game))
			col = ft_atoi(response) - 1;
		free(response);
	}
	drop_piece(game, col, player ? 'X' : 'O');
	return (true);
}

void finish_line(bool player)
{
	ft_putendl_fd("Player ", 1, false);
	ft_putendl_fd(player ? "O" : "X", 1, false);
	ft_putendl_fd(" Won !", 1, true);
}

int	main(int ac, char **av)
{
	t_game	game;
	bool player = true;
	if (!check_args(ac, av))
		return (1);
	if (!init_game(&game, ft_atoi(av[1]), ft_atoi(av[2])))
	{
		ft_putendl_fd("Error: grid allocation failed !", 2, true);
		return (1);
	}
	if (ac == 4)
	{
		draw_gui_grid(&game);
		if (!is_finished(&game))
			return 1;
		player = !player;
	}
	else
	{
		while(!is_finished(&game))
		{
			draw_grid(&game);
			if (!get_placement(&game, player))
				break ;
			player = !player;
		}
		draw_grid(&game);
	}
	finish_line(player);
	free_game(&game);
	return (0);
}
