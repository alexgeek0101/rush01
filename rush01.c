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

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define N 4
#define TOP 0
#define BOTTOM 1
#define LEFT 2
#define RIGHT 3

void	initializes(int *max_position, int *count_position)
{
	int	i;

	i = 0;
	while (i < N)
	{
		max_position[i] = 0;
		count_position[i] = 0;
	}
}

int	is_valid(int matrix[N][N], int row, int col, int num)
{
	int	i;

	i = 0;
	while (i < N)
	{
		if (matrix[row][i] == num || matrix[i][col] == num)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	print_matrix(int matrix[N][N])
{
	int		i;
	int		j;
	char	num_char;

	i = 0;
	while (i < N)
	{
		j = 0;
		while (j < N)
		{
			num_char = matrix[i][j] + '0';
			write(STDOUT_FILENO, &num_char, 1);
			if (j != N - 1)
				write(STDOUT_FILENO, " ", 1);
			j++;
		}
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

int	check_clues(int matrix[N][N], int clues[4][N])
{
	int	max_position[4];
	int	count_position[4];
	int	j;
	int	i;

	i = 0;
	while (i < N)
	{
		initializes(max_position, count_position);
		j = 0;
		while (j < N)
		{
			if (matrix[i][j] > max_position[TOP])
			{
				max_position[TOP] = matrix[i][j];
				count_position[TOP] += 1;
			}
			if (matrix[i][N - j - 1] > max_position[BOTTOM])
			{
				max_position[BOTTOM] = matrix[i][N - j - 1];
				count_position[BOTTOM] += 1;
			}
			if (matrix[j][i] > max_position[LEFT])
			{
				max_position[LEFT] = matrix[j][i];
				count_position[LEFT] += 1;
			}
			if (matrix[N - j - 1][i] > max_position[RIGHT])
			{
				max_position[RIGHT] = matrix[N - j - 1][i];
				count_position[RIGHT] += 1;
			}
			j++;
		}
		if (((clues[0][i] != count_position[TOP]) || clues[1][i] != count_position[BOTTOM])
			|| ((clues[2][i] != count_position[LEFT]) || clues[3][i] != count_position[RIGHT]))
			return (0);
		i++;
	}
	return (1);
}

void	swap_matrix_values(int matrix[N][N])
{
	int	temp;

	temp = matrix[0][1];
	matrix[0][1] = matrix[1][0];
	matrix[1][0] = temp;
	temp = matrix[0][2];
	matrix[0][2] = matrix[2][0];
	matrix[2][0] = temp;
	temp = matrix[0][3];
	matrix[0][3] = matrix[3][0];
	matrix[3][0] = temp;
	temp = matrix[1][2];
	matrix[1][2] = matrix[2][1];
	matrix[2][1] = temp;
	temp = matrix[1][3];
	matrix[1][3] = matrix[3][1];
	matrix[3][1] = temp;
	temp = matrix[2][3];
	matrix[2][3] = matrix[3][2];
	matrix[3][2] = temp;
}

int	solve(int matrix[N][N], int clues[4][N], int row, int col)
{
	int	next_row;
	int	next_col;
	int	num;

	if (row == N)
	{
		if (check_clues(matrix, clues))
			return (1);
		else
			return (0);
	}
	num = 1;
	while (num <= N)
	{
		if (is_valid(matrix, row, col, num))
		{
			matrix[row][col] = num;
			if (col == N -1)
			{
				next_row = row +1;
				next_col = 0;
			}
			else
			{
				next_row = row;
				next_col = col +1;
			}
			if (solve(matrix, clues, next_row, next_col))
				return (1);
			matrix[row][col] = 0;
		}
		num++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int		matrix[N][N];
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
			clues[clue_count / N][clue_count % N] = atoi(clue_start);
			clue_start = &clue_str[i + 1];
			clue_count++;
		}
		i++;
	}
	clues[clue_count / N][clue_count % N] = atoi(clue_start);
	if (solve(matrix, clues, 0, 0))
	{
		swap_matrix_values(matrix);
		print_matrix(matrix);
	}
	else
		write(STDOUT_FILENO, "Error.\n", 6);
	return (0);
}
