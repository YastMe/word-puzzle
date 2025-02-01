/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_puzzle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeltran <abeltran@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:45:12 by abeltran          #+#    #+#             */
/*   Updated: 2025/01/31 17:26:37 by abeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	in_array(int *order, int j, size_t i)
{
	size_t	k;

	k = 0;
	while (k < i)
	{
		if (order[k] == j)
		{
			return (1);
		}
		k++;
	}
	return (0);
}

char	**sort_list(int *order, char **words, size_t N)
{
	size_t	i;
	char	**sorted;

	if (!order || !words || N == 0 || order[0] == -1)
		return (printf("Error: No solution found\n"), NULL);
	sorted = (char **)malloc(sizeof(char *) * N);
	i = 0;
	while (i < N)
	{
		if (order[i] == -1)
		{
			free(sorted);
			return (NULL);
		}
		sorted[i] = words[order[i]];
		i++;
	}
	return (sorted);
}

static void	inner_while(size_t sizes[2], int *counters, char **words,
	int *order)
{
	char	aux;

	while (counters[0] < (int)sizes[0])
	{
		if (in_array(order, counters[0], sizes[1]))
		{
			counters[0]++;
			continue ;
		}
		if (sizes[1] > 0)
		{
			counters[3] = order[sizes[1] - 1];
			aux = words[counters[3]][strlen(words[counters[3]]) - 1];
		}
		else
			aux = 0;
		if (sizes[1] == 0 || (words[counters[0]][0] == aux))
		{
			order[sizes[1]] = counters[0];
			counters[2] = 1;
			sizes[1]++;
			break ;
		}
		counters[0]++;
	}
}

char	**ft_word_puzzle(size_t N, char **words)
{
	int		counters[4];
	int		order[100000];
	size_t	sizes[2];

	sizes[0] = N;
	memset(order, -1, sizeof(int) * N);
	sizes[1] = 0;
	while (sizes[1] < N)
	{
		printf("sizes[1]: %zu\n", sizes[1]);
		if (order[sizes[1]] != -1)
		{
			counters[1] = order[sizes[1]] + 1;
			order[sizes[1]] = -1;
		}
		else
			counters[1] = 0;
		counters[2] = 0;
		counters[0] = counters[1];
		inner_while(sizes, counters, words, order);
		if (!counters[2])
			order[sizes[1]--] = -1;
	}
	return (sort_list(order, words, N));
}

int	main(int argc, char **argv)
{
	char	**sorted;
	int		i;
	int		j;

	if (argc < 2)
		return (printf("Error: No arguments\n"), 0);
	else if (argc < 3 || argc > 100001)
		return (printf("Error: Arguments are not correct\n"), 0);
	i = 0;
	while (argv[++i])
	{
		if (strlen(argv[i]) < 1 || strlen(argv[i]) > 100)
			return (printf("Error: Arguments are not correct\n"), 0);
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < 'a' || argv[i][j] > 'z')
				return (printf("Error: Arguments are not correct\n"), 0);
	}
	sorted = ft_word_puzzle(--argc, &argv[1]);
	if (!sorted)
		return (printf("Error: No solution found\n"), 0);
	i = 0;
	while (sorted[i])
		printf("%s\n", sorted[i++]);
	return (free(sorted), 0);
}
