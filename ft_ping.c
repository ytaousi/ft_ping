/*

the main goal is to re write the ping commandin C :
    ◦ the ping command is used to test the reachability of a host on an IP network.
    ◦ the ping command sends ICMP ECHO_REQUEST packets to network hosts.
    ◦ the ping command waits for ICMP ECHO_RESPONSE packets from the host.
    ◦ the ping command displays the round-trip time for messages sent and received.
    ◦ we will manage only the option -v and -h.
       ◦ -h : Specify the number of bytes to increment the size of ICMP payload after each sweep when sending sweeping pings, the default value is 1.
       ◦ -v : Verbose output, ICMP packets other than ECHO_RESPONSE that are received are listed.

this is the list of the allowed functions :
    ◦ ssize_t sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
    
    ◦ ssize_t recvmsg(int socket, struct msghdr *message, int flags);
    
    ◦ int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
    
    ◦ const char *inet_ntop(int af, const void * restrict src, char * restrict dst, socklen_t size);
    
    ◦ int inet_pton(int af, const char * restrict src, void * restrict dst);
    
    ◦ signal / alarm / usleep.
    ◦ socket / setsockopt.
    ◦ getpid / getuid.
    ◦ getaddrinfo / getnameinfo / freeaddrinfo.
    ◦ strerror / gai_strerror.
    ◦ printf and its family.
    ◦ exit.

the program will take only one argument either a hostname or an IP address :
    ◦ if the argument is a hostname, the program will resolve it to an IP address.
    ◦ if the argument is an IP address, the program will use it directly.

first we need to parse av[1]


*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <ctype.h>

#define IP 5
#define HOSTNAME 2
#define FQDN 3

// is this valid data type ? 
typedef struct  icmphdr_s
{
    unsigned int type;
    unsigned int code;
    unsigned int checksum;
    union
    {
        struct
        {
            unsigned int id;
            unsigned int sequence;
        } echo;
        unsigned int gateway;
        // struct
        // {
        //     unsigned int __unused;
        //     unsigned int mtu;
        // } frag;
    } un;
}               icmphdr_t;

// is this valid data type ? 
typedef struct  iphdr_s
{
    unsigned int ip_headerlength;
    unsigned int ip_version;
    unsigned char ip_tos;
    unsigned short ip_total_length;
    unsigned short ip_id;
    unsigned short ip_offset;
    unsigned char ip_ttl;
    unsigned char ip_protocol;
    unsigned short ip_checksum;
    struct in_addr ip_srcaddr;
    struct in_addr ip_destaddr;
}               iphdr_t;

void ft_check_options(char **av, int *verbose)
{
    (void)av;
    (void)verbose;
}

int ft_init_socket()
{
    int					sock;
    const int           on = 1;

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); //  SOCK_RAW provide access to internal network protocols and interfaces, it is available only to the SUPER-USER.
	if (sock < 0)
    {
        printf("socket() failed\n");
        exit(1);
    }
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &on, sizeof (on)) == -1) 
    {
        printf("setsockopt() failed\n");
        exit(1);
    }
	return (sock);
}

int ft_build_icmp_header(icmphdr_t *icmp_header)
{
    // need to allocate enough memory for the icmp header before filling the structure 
    icmp_header = (icmphdr_t *)malloc(sizeof(icmphdr_t));
    if (icmp_header == NULL)
    {
        printf("allocation failed\n");
        return (-1);
    }
    icmp_header->type = ICMP_ECHO; // type 8 for ICMP_ECHO and type 0 for ICMP_REPLY
    icmp_header->code = 0;
    icmp_header->un.echo.id = getuid();
    icmp_header->un.echo.sequence = 0;
    icmp_header->checksum = 0; // in_cksum(), in4_cksum(), in6_cksum()
    return (0);
}

int ft_build_ip_header(iphdr_t *ip_header)
{
    ip_header = (iphdr_t *)malloc(sizeof(iphdr_t));
    if (ip_header == NULL)
    {
        printf("allocation failed\n");
        return (-1);
    }
    ip_header->ip_version = 4;
    ip_header->ip_headerlength = 5;
    ip_header->ip_tos = 0;
    ip_header->ip_total_length = 0; // htons(sizeof(iphdr_t) + sizeof(icmphdr_t));
    ip_header->ip_id = 0;
    ip_header->ip_offset = 0;
    ip_header->ip_ttl = 64;
    ip_header->ip_protocol = IPPROTO_ICMP;
    ip_header->ip_checksum = 0; // in_cksum(), in4_cksum(), in6_cksum()
    ip_header->ip_srcaddr.s_addr = inet_pton(AF_INET, , );
    ip_header->ip_destaddr.s_addr = inet_pton(AF_INET, , );
    return (0);
}

void ft_send_echo_request()
{
    
}

void ft_catch_echo_reply()
{
    
}

int main(int ac, char **av)
{
    int                 verbose = 0;
    int                 sockfd = -1;
    socklen_t           address_length;
    struct sockaddr_in  connection_address;
    icmphdr_t           icmp_header;
    iphdr_t             ip_header;


    if (ac < 2 || ac > 5)
    {
        printf("usage: ft_ping [-v] [-h sweep_increment] destination\n");
        exit(1);
    }
    else
    {
        ft_check_options(av, &verbose);
        if(getuid() != 0)
        {
            printf("root privileges needed for this type of socket\n");
            exit(1);
        }
        bzero(&connection_address, sizeof(connection_address));
        address_length = sizeof(connection_address);
        sockfd = ft_init_socket();
        connection_address.sin_family = AF_INET;
        connection_address.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", &connection_address.sin_addr); // this line should be tested

        if (ft_build_ip_header(&ip_header) == -1)
        {
            printf("ft_build_ip_header() failed\n");
            exit(1);
        }
        if (ft_build_icmp_header(&icmp_header) == -1)
        {
            printf("ft_build_icmp_header() failed\n");
            exit(1);
        }
        // ft_send_echo_request();
        // ft_catch_echo_reply();
    }
    return 0;
}