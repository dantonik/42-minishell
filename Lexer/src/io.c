#include "inc/minishell.h"

char	*read_file(const char *filename)
{
	FILE	*fp;
	char	*line;
	char	*buffer;
	size_t	len;
	ssize_t	read;

	line = NULL;
	len = 0;
	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		printf("Could not read file `%s`\n", filename);
		exit (1);
	}
	buffer = (char *)calloc(1, sizeof(char));
	buffer[0] = '\0';
	while ((read = getline(&line, &len, fp)) != -1)
	{
		buffer = (char *)realloc(buffer, (strlen(buffer)+strlen(line)+1) * sizeof(char));
		strcat(buffer, line);
	}
	fclose(fp);
	if (line)
		free (line);
	return (buffer);
}