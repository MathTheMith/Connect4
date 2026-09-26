#include <limits.h>
#include "connect4.h"

bool	is_col_full(t_game *game, int col);
bool	is_board_full(t_game *game);
bool	check_win(t_game *game, int player);

int	evaluate_board(t_game *game)
{
	return (0);
}

void	remove_piece(t_game *game, int row, int col)
{
	game->grid[row][col] = '.';
}

int	minimax(t_game *game, int depth, int alpha, int beta, bool is_ia_turn)
{
	int	col;
	int	row;
	int	eval;
	int max_eval;
	int min_eval;

	if (check_win(game, 'X'))
		return (10000);
	if (check_win(game, '0'))
		return (-10000);
	if (is_board_full(game))
		return (0);
	if (depth == 0)
		return (evaluate_board(game));

	if (is_ia_turn)
	{
		max_eval = INT_MIN;
		col = 0;
		while (col < game->columns)
		{
			if (!is_col_full(game->grid, col))
			{
				row = drop_piece(game->grid, col, 'X');
				eval = minimax(game, depth - 1, alpha, beta, 0);
				remove_piece(game->grid, row, col);

				if (eval > max_eval)
					max_eval = eval;
				if (eval > alpha)
					alpha = eval;
				if (beta <= alpha)
					break;
			}
			col++;
		}
		return (max_eval);
	}
	else
	{
		min_eval = INT_MIN;
		col = 0;
		while (col < game->columns)
		{
			if (!is_col_full(game->grid, col))
			{
				row = drop_piece(game->grid, col, '0');
				eval = minimax(game, depth - 1, alpha, beta, 1);
				remove_piece(game->grid, row, col);

				if (eval < min_eval)
					min_eval = eval;
				if (eval < beta)
					beta = eval;
				if (beta <= alpha)
					break;
			}
			col++;
		}
		return (min_eval);
	}
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
			row = drop_piece(game->grid, col, 'X');
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
