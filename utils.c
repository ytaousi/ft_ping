#include "./ft_ping.h"

void ft_print_ip_header(iphdr_t *ip_header)
{
    printf("********** IP HEADER **********\n");
    printf("ip_header->ip_headerlength = %d bytes\n", ip_header->ip_headerlength);
    printf("ip_header->ip_version = %d\n", ip_header->ip_version);
    printf("ip_header->ip_tos = %d\n", ip_header->ip_tos);
    printf("ip_header->ip_total_length = %d bytes\n", ip_header->ip_total_length);
    printf("ip_header->ip_id = %d\n", ip_header->ip_id);
    printf("ip_header->ip_offset = %d\n", ip_header->ip_offset);
    printf("ip_header->ip_ttl = %d\n", ip_header->ip_ttl);
    printf("ip_header->ip_protocol = %d\n", ip_header->ip_protocol);
    printf("ip_header->ip_checksum = %d\n", ip_header->ip_checksum);
    char src[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &ip_header->ip_srcaddr, src, INET_ADDRSTRLEN);
    printf("ip_header->ip_srcaddr = %s\n", src);
    
    char dest[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &ip_header->ip_destaddr, dest, INET_ADDRSTRLEN);
    printf("ip_header->ip_destaddr = %s\n", dest);
    printf("********** IP HEADER **********\n");
}

void ft_print_icmp_header(icmphdr_t *icmp_header)
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
    if (sig = SIGINT)
    {
        
    }
}