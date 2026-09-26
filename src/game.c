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

bool	get_placement(t_game *game)
{
	char	*response;
	int		col;

	col = -1;
	while (col == -1)
	{
		ft_putendl_fd("Your turn, place a piece between 1-", 1, false);
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
	game->state = check_connects(game, col, drop_piece(game, col, game->current));
	return (true);
}

void	print_result(t_game *game)
{
	if (game->state == WIN_X)
		ft_putendl_fd("The AI won !", 1, true);
	else if (game->state == WIN_O)
		ft_putendl_fd("You won !", 1, true);
	else if (game->state == DRAW)
		ft_putendl_fd("It's a draw !", 1, true);
}

void	ai_play(t_game *game)
{
	int	col;

	ft_putendl_fd("AI is thinking...", 1, true);
	col = get_best_move(game, 3);
	game->state = check_connects(game, col, drop_piece(game, col, game->current));
	ft_putendl_fd("AI played column ", 1, false);
	ft_putnbr_fd(col + 1, 1);
	ft_putendl_fd("", 1, true);
	game->current = (game->current == 'X') ? 'O' : 'X';
}

void	play_terminal(t_game *game)
{
	while (game->state == PLAYING)
	{
		draw_grid(game);
		if (game->current == 'O')
		{
			if (!get_placement(game))
				game->state = QUIT;
			game->current = (game->current == 'X') ? 'O' : 'X';		
		}
		if (game->current == 'X' && game->state == PLAYING)
			ai_play(game);
	}
	if (game->state != QUIT)
		draw_grid(game);
}
