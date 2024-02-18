#include "operaciones.h"

int	string_to_int(char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i] != '\0')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
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
	int	maxTop;
    int	maxBottom;
    int	maxLeft;
    int	maxRight;
    int countTop;
    int	countBottom;
    int	countLeft;
    int	countRight;
    int j;
	int i = 0;
	while (i < N) 
	{

		maxTop = 0;
		maxBottom = 0;
		maxLeft = 0;
		maxRight = 0;
		countTop = 0;
		countBottom = 0;
		countLeft = 0;
		countRight = 0;
		j = 0;
		while (j < N) {
			if (matrix[i][j] > maxTop) 
			{
				maxTop = matrix[i][j];
				countTop++;
			}
			if (matrix[i][N-j-1] > maxBottom) 
			{
                maxBottom = matrix[i][N-j-1];
                countBottom++;
            }
            if (matrix[j][i] > maxLeft)
			{
                maxLeft = matrix[j][i];
                countLeft++;
            }
            if (matrix[N-j-1][i] > maxRight)
			{
                maxRight = matrix[N-j-1][i];
                countRight++;
            }
            j++;
        }
        if (clues[0][i] != countTop || clues[1][i] != countBottom || clues[2][i] != countLeft || clues[3][i] != countRight) {
            return (0);
        }
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