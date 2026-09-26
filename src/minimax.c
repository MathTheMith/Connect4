#include <limits.h>
#include "connect4.h"


static	int score_window(char window[4])
{
	int	score = 0;
	int	ai_count = 0;
	int	opp_count = 0;
	int	empty_count = 0;
	int	i = 0;

	while (i < 4)
	{
		if (window[i] == 'X')
			ai_count++;
		else if (window[i] == 'O')
			opp_count++;
		else
			empty_count++;
	i++;
	}

	if (ai_count == 3 && empty_count == 1)
		score += 50;
	else if (ai_count == 2 && empty_count == 2)
		score += 10;
	if (opp_count == 3 && empty_count == 1)
		score -= 50;
	return (score);
}


int	evaluate_board(t_game *game)
{
	int		score = 0;
	int		center_col = game->columns / 2;
	int		r;
	int		c;
	int		i;
	char	window[4];

	r = 0;
	while (r < game->rows)
	{
		if (game->grid[r][center_col] == 'X')
			score += 2;
		r++;
	}

	r = 0;
	while (r < game->rows)
	{
		c = 0;
		while (c < game->columns - 3)
		{
			i = 0;
			while (i < 4)
			{
				window[i] = game->grid[r][c + i];
				i++;
			}
			score += score_window(window);
			c++;
		}
		r++;
	}

	c = 0;
	while (c < game->columns)
	{
		r = 0;
		while (r < game->rows - 3)
		{
			i = 0;
			while (i < 4)
			{
				window[i] = game->grid[r + i][c];
				i++;
			}
			score += score_window(window);
			r++;
		}
		c++;
	}

	r = 0;
    while (r < game->rows - 3)
    {
        c = 0;
        while (c < game->columns - 3)
        {
            i = 0;
            while (i < 4)
			{
                window[i] = game->grid[r + i][c + i];
				i++;
			}
            score += score_window(window);
            c++;
        }
        r++;
    }

    r = 3;
    while (r < game->rows)
    {
        c = 0;
        while (c < game->columns - 3)
        {
            i = 0;
            while (i < 4)
			{
                window[i] = game->grid[r - i][c + i];
				i++;
			}
            score += score_window(window);
            c++;
        }
        r++;
    }

	return (score);
}

void	remove_piece(t_game *game, int row, int col)
{
	game->grid[row][col] = '.';
}

int	minimax(t_game *game, int depth, int alpha, int beta, bool is_ia_turn, int row, int col)
{
	int	eval;
	int max_eval;
	int min_eval;
	int	i = 0;
	int	center_col = game->columns / 2;

	t_state current_state = check_connects(game, row, col);
	if (current_state == WIN_X)
		return (10000 + depth);
	if (current_state == WIN_O)
		return (-10000 - depth);
	if (current_state == DRAW)
		return (0);
	if (depth == 0)
		return (evaluate_board(game));

	if (is_ia_turn)
	{
		max_eval = alpha;
		col = 0;
		while (i < game->columns)
		{
			col = center_col + (1 - 2 * (i % 2)) * (i + 1) / 2;
			if (game->grid[0][col] == '.')
			{
				row = drop_piece(game, col, 'X');
				eval = minimax(game, depth - 1, alpha, beta, 0, row, col);
				remove_piece(game, row, col);

				if (eval > max_eval)
					max_eval = eval;
				if (eval > alpha)
					alpha = eval;
				if (beta <= alpha)
					break;
			}
			i++;
		}
		return (max_eval);
	}
	else
	{
		min_eval = INT_MAX;
		col = 0;
		while (i < game->columns)
		{
			col = center_col + (1 - 2 * (i % 2)) * (i + 1) / 2;
			if (game->grid[0][col] == '.')
			{
				row = drop_piece(game, col, 'O');
				eval = minimax(game, depth - 1, alpha, beta, 1, row, col);
				remove_piece(game, row, col);

				if (eval < min_eval)
					min_eval = eval;
				if (eval < beta)
					beta = eval;
				if (beta <= alpha)
					break;
			}
			i++;
		}
		return (min_eval);
	}
}

int	get_best_move(t_game *game, int max_depth)
{
	int	best_score = INT_MIN;
	int	best_col = 0;
	int	score;
	int	col = 0;
	int	row;
	int	i = 0;
	int	center_col = game->columns / 2;

	while (i < game->columns)
	{
		col = center_col + (1 - 2 * (i % 2)) * (i + 1) / 2;
		if (game->grid[0][col] == '.')
		{
			row = drop_piece(game, col, 'X');
			score = minimax(game, max_depth - 1, INT_MIN, INT_MAX, 0, row, col);
			remove_piece(game, row, col);
			if (score >= best_score)
			{
				best_score = score;
				best_col = col;
			}
		}
		i++;
	}
	return best_col;
}
