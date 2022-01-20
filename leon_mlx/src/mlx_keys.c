/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_keys.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 21:06:45 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/05 16:06:46 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

bool	mlx_is_key_down(t_mlx *mlx, t_keys key)
{
	return (glfwGetKey(mlx->window, key) == GLFW_PRESS);
}
