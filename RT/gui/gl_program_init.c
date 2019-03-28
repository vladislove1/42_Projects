/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_program_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:04:46 by liza              #+#    #+#             */
/*   Updated: 2019/02/21 22:06:11 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

GLuint	gl_compile_shader(const char *str, GLuint type)
{
	GLuint	vertex;
	int		success;
	char	info_log[512];

	vertex = glCreateShader(type);
	glShaderSource(vertex, 1, &str, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, info_log);
		ft_putendl("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
		ft_putendl(info_log);
		return (0);
	}
	return (vertex);
}

GLuint	gl_compile_program(const char *vertex, const char *fragment)
{
	GLuint	id;
	int		success;
	char	info_log[512];
	GLint	vertex_id;
	GLint	fragment_id;

	id = glCreateProgram();
	if (!(vertex_id = gl_compile_shader(vertex, GL_VERTEX_SHADER)) ||
		!(fragment_id = gl_compile_shader(fragment, GL_FRAGMENT_SHADER)))
		return (0);
	glAttachShader(id, vertex_id);
	glAttachShader(id, fragment_id);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, info_log);
		ft_putendl("ERROR::SHADER::PROGRAM::LINKING_FAILED");
		ft_putendl(info_log);
		return (0);
	}
	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);
	return (id);
}
