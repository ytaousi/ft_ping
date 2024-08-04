#include "./ft_ping.h"

void ft_print_ip_header(struct iphdr *ip_header)
{
    printf("********** IP HEADER **********\n");
    printf("ip_header->ip_headerlength = %d bytes\n", ip_header->ihl);
    printf("ip_header->ip_version = %d\n", ip_header->version);
    printf("ip_header->ip_tos = %d\n", ip_header->tos);
    printf("ip_header->ip_total_length = %d bytes\n", ip_header->tot_len);
    printf("ip_header->ip_id = %d\n", ip_header->id);
    printf("ip_header->ip_offset = %d\n", ip_header->frag_off);
    printf("ip_header->ip_ttl = %d\n", ip_header->ttl);
    printf("ip_header->ip_protocol = %d\n", ip_header->protocol);
    printf("ip_header->ip_checksum = %d\n", ip_header->check);
    char src[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &ip_header->saddr, src, INET_ADDRSTRLEN);
    printf("ip_header->ip_srcaddr = %s\n", src);
    
    char dest[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &ip_header->daddr, dest, INET_ADDRSTRLEN);
    printf("ip_header->ip_destaddr = %s\n", dest);
    printf("********** IP HEADER **********\n");
}

void ft_print_icmp_header(struct icmphdr *icmp_header)
{
    printf("********** ICMP HEADER **********\n");
    printf("icmp_header->type = %d\n", icmp_header->type);
    printf("icmp_header->code = %d\n", icmp_header->code);
    printf("icmp_header->un.echo.id = %d\n", icmp_header->un.echo.id);
    printf("icmp_header->un.echo.sequence = %d\n", icmp_header->un.echo.sequence);
    printf("icmp_header->checksum = %d\n", icmp_header->checksum);
    printf("********** ICMP HEADER **********\n");
}

void ft_sig_handler(int sig)
{
    if (sig == SIGINT)
    {
        ;
    }
}

void ft_display_help(void)
{

    
}

void ft_free_packet(t_ping_packet *g_ping_packet)
{
    if (g_ping_packet->packet.ip != NULL)
        free(g_ping_packet->packet.ip);
    if (g_ping_packet->packet.hdr != NULL)
        free(g_ping_packet->packet.hdr);
    if (g_ping_packet != NULL)
        free(g_ping_packet);
}