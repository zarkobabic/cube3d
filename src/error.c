/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:29:21 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/06 01:57:35 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <stdio.h>

void	error_exit(t_env *env, const char *message, t_error_code error_code)
{
	env_destroy(env);
	perror(message);
	exit(error_code);
}
