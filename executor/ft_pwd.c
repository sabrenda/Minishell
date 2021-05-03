#include "../minishell.h"

int ft_pwd(t_monna *lisa, int *count)
{
	char *s1;

	s1 = getcwd(NULL, 0);
	ft_putendl_fd(s1, 1);
	lisa->flag_command = 0;
	*count += 1;
	while (lisa->tokens[*count] && ft_operators(lisa->tokens[*count])) //пропускаем аргрументы если есть после env, так как по сабжу без них надо
		*count += 1;
	lisa->flag_error = 0;
	return (0);
}
