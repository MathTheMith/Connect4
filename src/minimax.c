#include <limits.h>
#include "connect4.h"

int	is_col_full(char **grid, int col);
int	check_win(char **grid, int player);

int	evaluate_board(t_game *game)
{
	return (0);
}

int	place_piece(t_game *game, int col, char piece)
{
	int	row;

	row = game->rows - 1;
	while (row >= 0)
	{
		if (game->grid[row][col] == '.')
		{
			game->grid[row][col] = piece;
			return (row);
		}
		row--;
	}
	return (-1);
}

void	remove_piece(t_game *game, int row, int col)
{
	game->grid[row][col] = '.';
}

int	minimax(t_game *game, int depth, int alpha, int beta, int is_ia_turn)
{
	;
}

int	get_best_move(t_game *game, int max_depth)
{
	int	best_score;
	int	best_col;
	int	score;
	int	col;
	int	row;

	best_score = INT_MIN;
	best_col = 0;
	col = 0;
	while (col < game->columns)
	{
		if (!is_col_full(game->grid, col))
		{
			row = place_piece(game->grid, col, 'X');
			score = minimax(game, max_depth - 1, INT_MIN, INT_MAX, 0);
			remove_piece(game->grid, row, col);
			if (score >= best_score)
			{
				best_score = score;
				best_col = col;
			}
		}
		col++;
	}
	return best_col;
}
