#include "../minishell.h"

void	err_cd(t_monna *lisa, int *count)
{
	struct stat	status;

	if (stat(lisa->tokens[*count], &status) == 0)
		printf("Monnalisa: cd: %s: Not a directory\n", lisa->tokens[*count]);
	else
		printf("Monnalisa: cd: %s: No such file or directory\n", lisa->tokens[*count]);

}

int	search_home(t_monna *lisa)
{
	int i;
	i = 0;
	while (lisa->my_env[i])
	{
		if (strncmp(lisa->my_env[i], "HOME=", 5) == 0)
		{
			chdir(strchr_boss(lisa->my_env[i], '='));
			return (0);
		}
		i++;
	}
	printf("Monnalisa: cd: HOME not set\n");
	return (1);
}

void	go_change_pat_pwd(t_monna *lisa, char *s)
{
	int i;

	i = 0;
	s = getcwd(NULL, 0);
	while (lisa->my_env[i])
	{
		if (strncmp(lisa->my_env[i], "PWD=", 4) == 0)
		{
			free(lisa->my_env[i]);
			lisa->my_env[i] = ft_strjoin("PWD=", s);
			free(s);
		}
		i++;
	}
}

void	change_oldpwd(t_monna *lisa, char *cur_k)
{
	int i;
	char *old;

	i = 0;
	while (lisa->my_env[i])
	{
		if (strncmp(lisa->my_env[i], "OLDPWD=", 7) == 0)
		{
			free(lisa->my_env[i]);
			lisa->my_env[i] = ft_strjoin("OLDPWD=", cur_k);
			return ;
		}
		i++;
	}
	// ft_free_mass(lisa->my_env);
	old = ft_strjoin("OLDPWD=", cur_k);
	ft_copy_massive_env(lisa, old);
	// если не нахожу, то strjoin добавляю oldpwd в env
}

int	ft_cd(t_monna *lisa, int *count) //енв
{
	char *s;
	char *cur_k;

	*count += 1;
	if (search_arg(lisa, count) == 0) // cd без параметров перемещает в $HOME и зависит от него
		search_home(lisa);
	else if (chdir(lisa->tokens[*count]) == 0) // не
	{
		cur_k = getcwd(NULL, 0);
		s = ft_strdup(lisa->tokens[*count]);
		go_change_pat_pwd(lisa, s);
		change_oldpwd(lisa, cur_k);
	}
	else
		err_cd(lisa, count);
	lisa->flag_command = 0;
	while (lisa->tokens[*count] && ft_operators(lisa->tokens[*count]) != 0) //пропускаем аргрументы если есть после env, так как по сабжу без них надо
		*count += 1;
	lisa->flag_error = 0;
	return (0);
}