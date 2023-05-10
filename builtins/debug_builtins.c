#include "../minishell.h"

void	print_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
	{
		printf("array does not exist\n");
		return ;
	}
	if (!*array)
	{
		printf("empty array\n");
		return ;
	}
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}