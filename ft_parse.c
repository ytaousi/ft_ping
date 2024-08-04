#include "./ft_ping.h"

void ft_init_structure(t_ping_packet *g_ping_packet)
{
    g_ping_packet = malloc(sizeof(t_ping_packet));
    if (g_ping_packet == NULL)
    {
        printf("Error Allocating ping_packet_struct\n");
        exit(1);
    }
        
    g_ping_packet->verbose = -1;
    g_ping_packet->packet.ip = NULL;
    g_ping_packet->packet.hdr = NULL;
}


void ft_check_options(int nb_arguments, char **av, t_ping_packet *g_ping_packet)
{
    int i;

    i = 0;
    if (nb_arguments == 1)
    {
        if (av[1][0] == '-')
        {
            if (strlen(av[1]) != 2)
            {
                printf("usage: ft_ping [-? help] [-v verbose] destination\n");
                ft_free_packet(g_ping_packet);
                exit(1);
            }
            else
            {
                if (av[1][1] == '?')
                {
                    ft_display_help();
                    if (g_ping_packet != NULL)
                        ft_free_packet(g_ping_packet);
                    exit(0);
                }
                else if (av[1][1] == 'v')
                {
                    g_ping_packet->verbose = 1;
                    // invalid option since we still need the dest adress
                }
                else
                {
                    printf("usage: ft_ping [-? help] [-v verbose] destination\n");
                    ft_free_packet(g_ping_packet);
                    exit(1);
                }

            }
        }
        else if (isdigit(av[1][0]))
        {
            if (ft_check_valid_ip(av[1]) == -1)
            {
                printf("usage: ft_ping [-? help] [-v verbose] destination\n");
                ft_free_packet(g_ping_packet);
                exit(1);
            }
        }
        else
        {
            printf("usage: ft_ping [-? help] [-v verbose] destination\n");
            ft_free_packet(g_ping_packet);
            exit(1);
        }
    }
    else if (nb_arguments == 2)
    {
        if ((av[1][0] == '-' && strlen(av[1]) == 2) || (av[2][0] == '-' && strlen(av[2]) == 2))
        {
            if (av[1][1] == '?' || av[2][1] == '?')
            {
                ft_display_help();
                if (g_ping_packet != NULL)
                    ft_free_packet(g_ping_packet);
                exit(0);
            }
        }
    }
    else
    {
        print("For Now lets go for 1 or 2 parameters\n");
        ft_free_packet(g_ping_packet);
        exit(0);
    }
}

int ft_check_valid_ip(char *string)
{
    (void)string;
    return (0);
}