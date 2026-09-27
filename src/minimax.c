#include <limits.h>
#include "connect4.h"

static	int score_counts(int ai_count, int opp_count, int empty_count)
{
	int	score = 0;

	if (ai_count == 3 && empty_count == 1)
		score += 50;
	else if (ai_count == 2 && empty_count == 2)
		score += 10;
	if (opp_count == 3 && empty_count == 1)
		score -= 50;
	return (score);
}

static int	window_delta(t_game *game, int start_row, int start_col,
	int row_step, int col_step, char piece)
{
	int		ai_count = 0;
	int		opp_count = 0;
	int		empty_count = 0;
	int		i = 0;
	char	cell;

	while (i < 4)
	{
		cell = game->grid[start_row + i * row_step][start_col + i * col_step];
		if (cell == 'X')
			ai_count++;
		else if (cell == 'O')
			opp_count++;
		else
			empty_count++;
		i++;
	}
	if (piece == 'X')
		return (score_counts(ai_count, opp_count, empty_count) - score_counts(ai_count - 1, opp_count, empty_count + 1));
	return (score_counts(ai_count, opp_count, empty_count) - score_counts(ai_count, opp_count - 1, empty_count + 1));
}

int	move_score_delta(t_game *game, int row, int col, char piece)
{
	int	delta = 0;
	int	shift = 0;
	int	left_col;
	int	top_row;
	int	bottom_row;

	while (shift < 4)
	{
		left_col = col - shift;
		top_row = row - shift;
		bottom_row = row + shift;
		if (left_col >= 0 && left_col + 3 < game->columns)
			delta += window_delta(game, row, left_col, 0, 1, piece);
		if (top_row >= 0 && top_row + 3 < game->rows)
			delta += window_delta(game, top_row, col, 1, 0, piece);
		if (top_row >= 0 && top_row + 3 < game->rows
			&& left_col >= 0 && left_col + 3 < game->columns)
			delta += window_delta(game, top_row, left_col, 1, 1, piece);
		if (bottom_row < game->rows && bottom_row - 3 >= 0
			&& left_col >= 0 && left_col + 3 < game->columns)
			delta += window_delta(game, bottom_row, left_col, -1, 1, piece);
		shift++;
	}
	if (piece == 'X' && col == game->columns / 2)
		delta += 2;
	return (delta);
}


int	evaluate_board(t_game *game)
{
	return (game->score);
}

static t_zone	save_zone(t_game *game)
{
	t_zone	zone;

	zone.top_row = game->temp_top_row;
	zone.min_col = game->temp_min_col;
	zone.max_col = game->temp_max_col;
	zone.score = game->score;
	return (zone);
}

void	remove_piece(t_game *game, int row, int col, t_zone zone)
{
	game->moves_count--;
	game->grid[row][col] = '.';
	game->temp_top_row = zone.top_row;
	game->temp_min_col = zone.min_col;
	game->temp_max_col = zone.max_col;
	game->score = zone.score;
}

int	minimax(t_game *game, int depth, int alpha, int beta, bool is_ia_turn, int row, int col)
{
	int	eval;
	int max_eval;
	int min_eval;
	int	i = 0;
	int	center_col = game->columns / 2;
	t_zone	zone;
	t_state current_state = check_connects(game, col, row);
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
		while (i < game->columns)
		{
			col = center_col + (1 - 2 * (i % 2)) * (i + 1) / 2;
			if (col >= game->temp_min_col - 3 && col <= game->temp_max_col + 3
				&& game->grid[0][col] == '.')
			{
				zone = save_zone(game);
				row = drop_piece(game, col, 'X');
				eval = minimax(game, depth - 1, alpha, beta, 0, row, col);
				remove_piece(game, row, col, zone);

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
		while (i < game->columns)
		{
			col = center_col + (1 - 2 * (i % 2)) * (i + 1) / 2;
			if (col >= game->temp_min_col - 3 && col <= game->temp_max_col + 3
				&& game->grid[0][col] == '.')
			{
				zone = save_zone(game);
				row = drop_piece(game, col, 'O');
				eval = minimax(game, depth - 1, alpha, beta, 1, row, col);
				remove_piece(game, row, col, zone);

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

void	set_zone(t_game *game, int max_depth)
{
	int	r;
	int	c;

	game->top_row = game->rows;
	game->min_col = game->columns - 1;
	game->max_col = 0;
	r = 0;
	while (r < game->rows)
	{
		c = 0;
		while (c < game->columns)
		{
			if (game->grid[r][c] != '.')
			{
				if (r < game->top_row)
					game->top_row = r;
				if (c < game->min_col)
					game->min_col = c;
				if (c > game->max_col)
					game->max_col = c;
			}
			c++;
		}
		r++;
	}
	game->top_row -= max_depth;
	game->temp_max_col = game->max_col;
	game->temp_min_col = game->min_col;
	game->temp_top_row = game->top_row;
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
	t_zone	zone;

	set_zone(game, max_depth);
	if (game->moves_count == 0)
		return (center_col);
	
	while (i < game->columns)
	{
		col = center_col + (1 - 2 * (i % 2)) * (i + 1) / 2;
		if (col >= game->min_col - 3 && col <= game->max_col + 3
			&& game->grid[0][col] == '.')
		{
			zone = save_zone(game);
			row = drop_piece(game, col, 'X');
			score = minimax(game, max_depth - 1, best_score, INT_MAX, 0, row, col);
			remove_piece(game, row, col, zone);
			if (score > best_score)
			{
				best_score = score;
				best_col = col;
			}
		}
		i++;
	}
	while (best_score == INT_MIN && game->grid[0][best_col] != '.')
		best_col++;
	return best_col;
}
