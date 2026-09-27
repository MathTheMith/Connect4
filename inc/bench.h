#ifndef BENCH_H
# define BENCH_H

/*
** Search statistics hooks, only active when compiled with -D BENCH
** (bench/bench.py does it). In the normal build every macro is a no-op.
*/
# ifdef BENCH
#  define BENCH_HOOKS 1
#  define BENCH_MAX_DEPTH 64

typedef struct s_bench
{
	unsigned long	leaves;
	unsigned long	interior;
	unsigned long	legal;
	unsigned long	explored;
	unsigned long	cutoffs;
	unsigned long	first_cutoffs;
	unsigned long	explored_at[BENCH_MAX_DEPTH];
}	t_bench;

extern t_bench	g_bench;

void	bench_interior(t_game *game, int depth);
void	bench_cutoff(int depth);

#  define BENCH_LEAF() (g_bench.leaves++)
#  define BENCH_INTERIOR(game, depth) bench_interior(game, depth)
#  define BENCH_CHILD(depth) \
	(g_bench.explored++, g_bench.explored_at[(depth) % BENCH_MAX_DEPTH]++)
#  define BENCH_CUTOFF(depth) bench_cutoff(depth)
# else
#  define BENCH_LEAF() ((void)0)
#  define BENCH_INTERIOR(game, depth) ((void)0)
#  define BENCH_CHILD(depth) ((void)0)
#  define BENCH_CUTOFF(depth) ((void)0)
# endif

#endif
