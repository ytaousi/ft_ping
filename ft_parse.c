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
    g_ping_packet->help = -1;
    g_ping_packet->packet.ip = NULL;
    g_ping_packet->packet.hdr = NULL;
}


void ft_check_options(int nb_arguments, char **av, t_ping_packet *g_ping_packet)
{
    (void)nb_arguments;
    (void)av;
    (void)g_ping_packet;

}