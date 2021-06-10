#include "../minishell.h"

void	keep_exp(t_monna *lisa, char *str)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	while (lisa->my_env[i] && ft_strcmp(lisa->my_env[i], str) == 0)
	{
		if (strcmp(lisa->my_env[i], str) == 0)
			check = 1;
		i++;
	}
	if (check != 1)
		ft_copy_massive_env(lisa, str);
}

int	len_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

int	search_per_env(t_monna *lisa, char *str, int len)
{
	int	i;

	i = 0;
	while(lisa->my_env[i])
	{

		if (ft_strncmp(lisa->my_env[i], str, len) == 0)
		{
			free(lisa->my_env[i]);
			lisa->my_env[i] = ft_strdup(str);
			return (0);
		}
		i++;
	}
	return (1);
}

void	err_exp(t_monna *lisa, char *s)
{
	printf("Monnalisa: export: `%s': not a valid identifier\n", s);
}

void	print_sort_env(t_monna *lisa)
{
	int	i;
	int	j;

	i = 0;
	while (lisa->my_env[i])
	{
		printf("declare -x ");
		if (strchr(lisa->my_env[i], 61) != NULL)
		{
			j = 0;
			while(lisa->my_env[i][j] != '=')
			{
				printf("%c", lisa->my_env[i][j]);
				j++;
			}
			printf("=");
			printf("\"%s\"\n", strchr_boss(lisa->my_env[i], '='));
		}
		else
			printf("%s\n", lisa->my_env[i]);
		i++;
	}
}

void sort_env(t_monna *lisa)
{
	int		i = 0;
	int		s_i = 0;
	char	*temp;
	int		len = 0;

	while (lisa->my_env[len])
		len++;
	while(i < len - 1)
	{
		s_i = 0;
		while(s_i < len - 1)
		{
			if(ft_strcmp(lisa->my_env[s_i],lisa->my_env[s_i + 1]) > 0)
			{
				temp = lisa->my_env[s_i + 1];
				lisa->my_env[s_i + 1] = lisa->my_env[s_i];
				lisa->my_env[s_i] = temp;
			}
			s_i++;
		}
		i++;
	}
	print_sort_env(lisa);
}

int	ft_export(t_monna *l, int *i)
{
	int		t;
	char	*s;

	*i += 1;
	if (search_arg(l, i) == 0)
		sort_env(l);
	else if (ft_isalpha(*l->tokens[*i]) == 0
		&& ft_strcmp(l->tokens[*i], "_") != 0)
		err_exp(l, l->tokens[*i]);
	else
	{
		if (strchr(l->tokens[*i], 61) != NULL)
		{
			t = search_per_env(l, l->tokens[*i], len_arg(l->tokens[*i]));
			if (t == 1)
				ft_copy_massive_env(l, l->tokens[*i]);
		}
		else
			keep_exp(l, l->tokens[*i]);
	}
	l->flag_command = 0;
	while (l->tokens[*i] && ft_operators_2(l->tokens[*i]))
		*i += 1;
	l->flag_error = 0;
	return (0);
}
