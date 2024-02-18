/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jifiguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:48:09 by jifiguer          #+#    #+#             */
/*   Updated: 2024/02/18 19:39:59 by jifiguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operaciones.h"

int	main(int argc, char *argv[])
{
	int		matrix[N][N] = {0};
	int		clues[4][N];
	int		clue_count;
	int		i;
	char	*clue_str;
	char	*clue_start;
	
	i = 0;
	clue_str = argv[1];
	clue_count = 0;
	clue_start = clue_str;
	if (argc != 2)
	{
		write(STDOUT_FILENO, "Por favor, introduce 16 pistas.\n", 31);
		return (1);
	}
	while (clue_str[i] != '\0')
	{
		if (clue_str[i] == ' ')
		{
			clue_str[i] = '\0';
			clues[clue_count / N][clue_count % N] = string_to_int(clue_start);
			clue_start = &clue_str[i + 1];
			clue_count++;
		}
		i++;
	}
	clues[clue_count / N][clue_count % N] = string_to_int(clue_start);
	if (solve(matrix, clues, 0, 0))
	{
		swap_matrix_values(matrix);
		print_matrix(matrix);
	}
	else
		write(STDOUT_FILENO, "Error.\n", 6);
	return (0);
}
