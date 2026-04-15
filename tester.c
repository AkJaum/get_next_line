#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "get_next_line.h"

static int	is_txt_file(const char *name)
{
	size_t	len;

	len = strlen(name);
	if (len < 4)
		return (0);
	return (strcmp(name + (len - 4), ".txt") == 0);
}

static char	*find_txt_file(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*found;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	found = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (is_txt_file(entry->d_name))
		{
			found = strdup(entry->d_name);
			break ;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (found);
}

static void	print_line_output(int call, const char *line)
{
	size_t	len;

	len = strlen(line);
	printf("Chamada %d (output): %s", call, line);
	if (len == 0 || line[len - 1] != '\n')
		printf("\n");
}

int	main(void)
{
	char	*txt_file;
	char	*line;
	int		fd;
	int		call;

	printf("Esse projeto foi feito como parte do curriculo academico de João Gabriel.\n");
	printf("A GNL é uma função que retorna uma linha por chamada a partir de uma file descriptor.\n");
	printf("Este tester mostra cada chamada da get_next_line e o respectivo output.\n");
	printf("A execucao percorre o arquivo inteiro e mostra o retorno de cada chamada.\n\n");
	txt_file = find_txt_file();
	if (!txt_file)
	{
		printf("Erro: nenhum arquivo .txt encontrado na raiz do projeto.\n");
		return (1);
	}
	fd = open(txt_file, O_RDONLY);
	if (fd < 0)
	{
		printf("Erro: nao foi possivel abrir o arquivo '%s'.\n", txt_file);
		free(txt_file);
		return (1);
	}
	printf("Arquivo de teste: %s\n\n", txt_file);
	call = 1;
	line = get_next_line(fd);
	while (line)
	{
		print_line_output(call, line);
		free(line);
		call++;
		line = get_next_line(fd);
	}
	printf("Chamada %d (output): NULL\n", call);
	close(fd);
	free(txt_file);
	return (0);
}
