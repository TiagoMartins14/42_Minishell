/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:43:34 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/08 20:05:19 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*set_shlvl(char *envp)
{
	int		val;
	char	*temp;
	char	*envp_copy;

	val = ft_atoi(envp + 6) + 1;
	temp = ft_itoa(val);
	envp_copy = ft_strjoin("SHLVL=", temp);
	free(temp);
	return (envp_copy);
}

/* Makes a copy of the original envp */
char	**envp_dup(char **envp, int i)
{
	int		val;
	char	**envp_copy;

	val = 1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", 5))
			val = 0;
	}
	envp_copy = (char **)malloc(sizeof(char *) * (i + 1 + val));
	if (!envp_copy)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", 5))
			envp_copy[i] = set_shlvl(envp[i]);
		else
			envp_copy[i] = ft_strdup(envp[i]);
	}
	if (val == 1)
		envp_copy[i++] = ft_strjoin("SHLVL=", "1");
	envp_copy[i] = NULL;
	return (envp_copy);
}

/* Updates de envp_copy variable to reflect any changes made to it */
char	**update_envp_copy(t_mshell *init, char ***env_copy, int i, t_env *node)
{
	node = init->env_table;
	while (node && i++ >= 0)
		node = node->next;
	ft_free_smatrix(*env_copy);
	(*env_copy) = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	node = init->env_table;
	while (++i >= 0 && node)
	{
		(*env_copy)[i] = ft_strdup(node->var);
		if (node->visibility == 1 && node->var[ft_strlen(node->var) - 1] != '~')
			(*env_copy)[i] = ft_strupdate((*env_copy)[i], "~");
		if (node->content)
		{
			(*env_copy)[i] = ft_strupdate((*env_copy)[i], "=");
			(*env_copy)[i] = ft_strupdate((*env_copy)[i], node->content);
		}
		node = node->next;
	}
	(*env_copy)[i] = NULL;
	return (*env_copy);
}
