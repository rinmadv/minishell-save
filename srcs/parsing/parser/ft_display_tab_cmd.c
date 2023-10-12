
#include "minishell.h"
#include "minishell_louis.h"

void	ft_display_tab_cmd(t_data *data)
{
	int	i;
	int	j;
	char	*str;

	i = 0;
	while (i < data->nb_command)
	{
		printf(GREEN"cmd %d\n"NC, i);
		j = 0;
		while (data->cmd[i] && data->cmd[i]->cmd_args[j] && data->cmd[i]->cmd_args[j][0])
		{
			printf("arg[%d], ", j);
			str = data->cmd[i]->cmd_args[j];
			printf("%p, ", str);
			printf("str [0] %c, ", str[0]);
			printf("str [1] %c, ", str[1]);
			printf("str [2] %c, ", str[2]);
			printf("size allocated : %lu\n", strlen(data->cmd[i]->cmd_args[j]));
			j++;
		}
		printf("cmd[%d] arg[%d] : %p\n", i, j, data->cmd[i]->cmd_args[j]);
		printf("\n");
		i++;
	}
}
