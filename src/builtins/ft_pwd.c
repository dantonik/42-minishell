/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 01:25:46 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/25 16:14:43 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;
	int		len;

	pwd = getcwd(NULL, MAXPATHLEN);
	if (pwd != NULL)
	{
		len = ft_strlen(pwd);
		write(1, pwd, len);
		write(1, "\n", 1);
		free(pwd);
		return (0);
	}
	return (1);
}
