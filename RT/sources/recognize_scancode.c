/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_scancode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 23:19:57 by liza              #+#    #+#             */
/*   Updated: 2018/09/15 18:27:13 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				reset_motion(int *motion, int scancode)
{
	if (scancode == SDL_SCANCODE_W || scancode == SDL_SCANCODE_S)
		*motion &= ~(3);
	else if (scancode == SDL_SCANCODE_A || scancode == SDL_SCANCODE_D)
		*motion &= ~(3 << 2);
	else if (scancode == SDL_SCANCODE_Z || scancode == SDL_SCANCODE_X)
		*motion &= ~(3 << 4);
	else if (scancode == SDL_SCANCODE_Q || scancode == SDL_SCANCODE_E)
		*motion &= ~(3 << 6);
	else if (scancode == SDL_SCANCODE_RIGHT || scancode == SDL_SCANCODE_LEFT)
		*motion &= ~(3 << 8);
	else if (scancode == SDL_SCANCODE_DOWN || scancode == SDL_SCANCODE_UP)
		*motion &= ~(3 << 10);
}

void				recognize_motion(int *motion, int scancode)
{
	int				byte;

	reset_motion(motion, scancode);
	byte = 1;
	if (scancode == SDL_SCANCODE_S || scancode == SDL_SCANCODE_D ||
		scancode == SDL_SCANCODE_X || scancode == SDL_SCANCODE_E ||
		scancode == SDL_SCANCODE_LEFT || scancode == SDL_SCANCODE_UP)
		byte = 2;
	if (scancode == SDL_SCANCODE_W || scancode == SDL_SCANCODE_S)
		*motion |= byte;
	else if (scancode == SDL_SCANCODE_A || scancode == SDL_SCANCODE_D)
		*motion |= (byte << 2);
	else if (scancode == SDL_SCANCODE_Z || scancode == SDL_SCANCODE_X)
		*motion |= (byte << 4);
	else if (scancode == SDL_SCANCODE_Q || scancode == SDL_SCANCODE_E)
		*motion |= (byte << 6);
	else if (scancode == SDL_SCANCODE_RIGHT || scancode == SDL_SCANCODE_LEFT)
		*motion |= (byte << 8);
	else if (scancode == SDL_SCANCODE_DOWN || scancode == SDL_SCANCODE_UP)
		*motion |= (byte << 10);
	else if (scancode == SDL_SCANCODE_R)
		*motion |= (1 << 12);
	else if (scancode == SDL_SCANCODE_G)
		*motion |= (1 << 13);
}

void				recognize_mode(int *mode, int scancode)
{
	int				camera_mode;
	int				color_sheme;

	camera_mode = *mode >> 4;
	color_sheme = *mode & 0x0f;
	if (scancode == SDL_SCANCODE_HOME)
		camera_mode += 1;
	else if (scancode == SDL_SCANCODE_END)
		camera_mode += 4;
	else if (scancode == SDL_SCANCODE_PAGEUP)
		color_sheme += 1;
	else if (scancode == SDL_SCANCODE_PAGEDOWN)
		color_sheme += 6;
	*mode = ((camera_mode % 5) << 4) | ((color_sheme % 7) & 0x0f);
}
