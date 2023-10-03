#include "ft_ping.h"

void ft_init_structure(void)
{
    g_ping_packet = malloc(sizeof(t_ping_packet));

    g_ping_packet->verbose = -1;
    g_ping_packet->help = -1;
}

void ft_send_ping_packet(void)
{

}

icmphdr_t *ft_build_icmp_header(void)
{
   
}

iphdr_t *ft_build_ip_header(char *src_addr, char *dst_addr)
{
    
}

u_short ft_get_checksum(unsigned short* addr, int len)
{
    (void)addr;
    (void)len;
    return (0);
}

void ft_get_round_trip_time(void)
{
       
}


int ft_init_socket()
{
    int					sock;
    const int           on = 1;

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP); //  SOCK_RAW provide access to internal network protocols and interfaces, it is available only to the SUPER-USER.
	if (sock < 0)
        return -1;
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &on, sizeof (on)) == -1) 
        return -1;
	return (sock);
}

void ft_send_echo_request(void)
{

}

void ft_catch_echo_reply(void)
{
    
}