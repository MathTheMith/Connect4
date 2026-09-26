#include "connect4.h"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define LIGHT_BLUE "\033[0;94m"
# define RESET "\033[0m"
#define WIN_COLOR "\033[1;32m"

static void   print_border(int columns)
{
      int     i;
      ft_putendl_fd(LIGHT_BLUE, 1, false);
      ft_putendl_fd("+", 1, false);
      i = 0;
      while (i++ < columns)
              ft_putendl_fd("---+", 1, false);
      ft_putendl_fd("", 1, true);
      ft_putendl_fd(RESET, 1, false);
}

static void print_cell(char *piece, char *color)
{
	ft_putendl_fd(color, 1, false);
	ft_putendl_fd(piece, 1, false);
	ft_putendl_fd(RESET, 1, false);
}

static void print_nb_columns(int columns)
{
	int i = 1;
	while (i < columns + 1)
	{
		ft_putendl_fd("  ", 1, false);
		ft_putnbr_fd(i, 1);
		ft_putendl_fd(" ", 1, false);
		i++;
	}
	ft_putendl_fd("\n", 1, true);
}

static bool	is_winning_cell(t_game *game, int col, int row)
{
	int	i;

	if (game->state != WIN_X && game->state != WIN_O)
		return (false);
	i = 0;
	while (i < 4)
	{
		if (game->win_pos.x + i * game->win_pos.dx == col
			&& game->win_pos.y + i * game->win_pos.dy == row)
			return (true);
		i++;
	}
	return (false);
}

void draw_grid(t_game *game)
{
	int i = 0;
	int j = 0;

	print_border(game->columns);

	while(j < game->rows)
	{
		i = 0;
		ft_putendl_fd(LIGHT_BLUE, 1, false);
		ft_putendl_fd("| ", 1, false);

		while(i < game->columns)
		{
		    ft_putendl_fd(LIGHT_BLUE, 1, false);
			if (is_winning_cell(game, i, j))
				print_cell(game->grid[j][i] == 'X' ? "X" : "O", WIN_COLOR);
			else if(game->grid[j][i] == 'X' || game->grid[j][i] == 'O')
				print_cell(game->grid[j][i] == 'X' ? "X" : "O",
					game->grid[j][i] == 'X' ? RED : YELLOW);
			else
				ft_putendl_fd(".", 1, false);
			i++;
			ft_putendl_fd(LIGHT_BLUE, 1, false);
			ft_putendl_fd(" | ", 1, false);
	      ft_putendl_fd(RESET, 1, false);
		}
		j++;
		ft_putendl_fd("\n", 1, false);
		print_border(game->columns);
	}
	print_nb_columns(game->columns);

}
