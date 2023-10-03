#include "./ft_ping.h"

void ft_check_options(int nb_argments, char **av)
{
    int i;

    i = 1
    while (i < nb_arguments)
    {
        if (av[i][0] == '-')
        {
            if (av[i][1] == '?')
            {
                // help option
                g_ping_packet->help = 1;
            }
            else if (av[i][1] == 'v')
            {
                // verbose option
                g_ping_packet->verbose = 1;
            }
            else
            {
                printf("usage: ft_ping [-? help] [-v verbose] destination\n");
                exit(1);
            }
        }
        else
        {
			
        }
    }

}