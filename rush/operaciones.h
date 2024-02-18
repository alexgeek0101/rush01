#ifndef _OPERACIONES_H
#define _OPERACIONES_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define N 4

int	string_to_int(char *str);
void	initializes(int *max_position, int *count_position);
int	is_valid(int matrix[N][N], int row, int col, int num);
void	print_matrix(int matrix[N][N]);
int	check_clues(int matrix[N][N], int clues[4][N]);
void	swap_matrix_values(int matrix[N][N]);
int	solve(int matrix[N][N], int clues[4][N], int row, int col);

#endif