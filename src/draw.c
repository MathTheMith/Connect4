#include "connect4.h"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
# define RESET "\033[0m"

static void   print_border(int columns)
{
      int     i;
      
      ft_putendl_fd("+", 1, false);
      i = 0;
      while (i++ < columns)
              ft_putendl_fd("---+", 1, false);
      ft_putendl_fd("", 1, true);
}

static void print_cell(char *piece, char *color)
{
	ft_putendl_fd(color, 1, false);
	ft_putendl_fd(piece, 1, false);
	ft_putendl_fd(RESET, 1, false);
}

void draw_grid(t_game *game)
{
	int i = 0;
	int j = 0;

	print_border(game->columns);

	while(j < game->rows)
	{
		i = 0;
		ft_putendl_fd("| ", 1, false);
		while(i < game->columns)
		{
			if(game->grid[j][i] == 'X' || game->grid[j][i] == 'O')
				print_cell(game->grid[j][i] == 'X' ? "X" : "O",
					game->grid[j][i] == 'X' ? RED : YELLOW);
			else
				ft_putendl_fd(".", 1, false);
			i++;
			ft_putendl_fd(" | ", 1, false);
		}
		j++;
		ft_putendl_fd("\n", 1, false);
		print_border(game->columns);
	}
	ft_putendl_fd("\n", 1, false);

}
