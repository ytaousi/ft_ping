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
    ◦ sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
    
    ◦ recvmsg(int socket, struct msghdr *message, int flags);
    
    ◦ gettimeofday(struct timeval *restrict tp, void *restrict tzp);
    
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
#include <signal.h>

#define IP 5
#define HOSTNAME 2
#define FQDN 3

typedef struct  iovec_s
{
	void *   iov_base;      /* [XSI] Base address of I/O memory region */
	size_t   iov_len;       /* [XSI] Size of region iov_base points to */
}               iovec_t;

typedef struct  msghdr_s
{
	void            *msg_name;      /* [XSI] optional address */
	socklen_t       msg_namelen;    /* [XSI] size of address */
	iovec_t         *msg_iov;       /* [XSI] scatter/gather array */
	int             msg_iovlen;     /* [XSI] # elements in msg_iov */
	void            *msg_control;   /* [XSI] ancillary data, see below */
	socklen_t       msg_controllen; /* [XSI] ancillary data buffer len */
	int             msg_flags;      /* [XSI] flags on received message */
}               msghdr_t;

typedef struct  icmphdr_s
{
    u_int8_t type;
    u_int8_t code;
    u_int16_t checksum;
    union
    {
        struct
        {
            u_int16_t id;
            u_int16_t sequence;
        } echo;
        unsigned int gateway;
        // struct
        // {
        //     u_int16_t __unused;
        //     u_int16_t mtu;
        // } frag;
    } un;
}               icmphdr_t;
 
typedef struct  iphdr_s
{
    u_int ip_headerlength;
    u_int ip_version;
    u_char ip_tos;
    u_short ip_total_length;
    u_short ip_id;
    u_short ip_offset;
    u_char ip_ttl;
    u_char ip_protocol;
    u_short ip_checksum;
    struct in_addr ip_srcaddr;
    struct in_addr ip_destaddr;
}               iphdr_t;

void ft_check_options(char **av, int *verbose, char *src_addr, char *dst_addr)
{
    (void)av;
    (void)verbose;
    (void)src_addr;
    (void)dst_addr;
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

u_short ft_get_checksum(unsigned short* addr, int len)
{
    (void)addr;
    (void)len;
    return (0);
}

icmphdr_t *ft_build_icmp_header(void)
{
    icmphdr_t *icmp_header;

    icmp_header = (icmphdr_t *)malloc(sizeof(icmphdr_t));
    if (icmp_header == NULL)
        return (NULL);
    icmp_header->type = ICMP_ECHO; // type 8 for ICMP_ECHO and type 0 for ICMP_REPLY
    icmp_header->code = 0;
    icmp_header->un.echo.id = getuid();
    icmp_header->un.echo.sequence = 0;
    icmp_header->checksum = ft_get_checksum((unsigned short *)icmp_header, sizeof(icmphdr_t));// in_cksum(), in4_cksum(), in6_cksum()
    return (icmp_header);
}

iphdr_t *ft_build_ip_header(char *src_addr, char *dst_addr)
{
    iphdr_t *ip_header;

    ip_header = (iphdr_t *)malloc(sizeof(iphdr_t));
    if (ip_header == NULL)
        return (NULL);
    ip_header->ip_version = 4;
    ip_header->ip_headerlength = 5;
    ip_header->ip_tos = 0;
    ip_header->ip_total_length = sizeof(iphdr_t) + sizeof(icmphdr_t);
    ip_header->ip_id = 0;
    ip_header->ip_offset = 0;
    ip_header->ip_ttl = 64;
    ip_header->ip_protocol = IPPROTO_ICMP;
    ip_header->ip_checksum = ft_get_checksum((unsigned short *)ip_header, sizeof(iphdr_t)); // in_cksum(), in4_cksum(), in6_cksum()
    inet_pton(AF_INET, src_addr, &ip_header->ip_srcaddr.s_addr);
    inet_pton(AF_INET, dst_addr, &ip_header->ip_destaddr.s_addr);
    return (ip_header);
}

void ft_send_echo_request(void)
{

}

void ft_catch_echo_reply(void)
{
    
}

void ft_sigint_handler(int sig)
{
    if (sig == SIGINT)
    {
        ;
    }
}

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

void ft_get_round_trip_time(void)
{
       
}

int main(int ac, char **av)
{
    int                 verbose = 0;
    int                 sockfd = -1;
    socklen_t           address_length;
    struct sockaddr_in  connection_address;
    int                 received_size = 0;
    icmphdr_t           *icmp_header;
    iphdr_t             *ip_header;
    char                dst_addr[20] = "127.0.0.1";// google.com 172.217.17.14
    char                src_addr[20] = "10.0.2.15";// my ip address
    struct msghdr       *message_header;
    struct iovec        buffer;


    if (ac < 2 || ac > 5)
    {
        printf("usage: ft_ping [-v] [-h sweep_increment] destination\n");
        exit(1);
    }
    else
    {
        ft_check_options(av, &verbose, src_addr, dst_addr);
        // if(getuid() != 0)
        // {
        //     printf("root privileges needed for this type of command\n");
        //     exit(1);
        // }
        signal(SIGINT, &ft_sigint_handler);
        bzero(&connection_address, sizeof(connection_address));
        sockfd = ft_init_socket();
        if (sockfd == -1)
        {
            printf("ft_init_socket() failed\n");
            exit(1);
        }
        connection_address.sin_family = AF_INET;
        inet_pton(AF_INET, dst_addr, &connection_address.sin_addr); // this line should be tested
        if ((ip_header = ft_build_ip_header(src_addr, dst_addr)) == NULL)
        {
            printf("ft_build_ip_header() failed\n");
            exit(1);
        }
        ft_print_ip_header(ip_header);
        printf("\n");
        if ((icmp_header = ft_build_icmp_header()) == NULL)
        {
            printf("ft_build_icmp_header() failed\n");
            exit(1);
        }
        ft_print_icmp_header(icmp_header);
        printf("\n");
        sendto(sockfd, ip_header, ip_header->ip_total_length, 0, (struct sockaddr *)&connection_address, sizeof(struct sockaddr));
        printf("Sent %d byte packet to %s\n", ip_header->ip_total_length , dst_addr);
        address_length = sizeof(connection_address);
        bzero(&buffer, sizeof(buffer));
        bzero(&message_header, sizeof(message_header));
        buffer.iov_base = malloc(1024);
        buffer.iov_len = 1024;
        message_header->msg_name = &connection_address;
        message_header->msg_namelen = address_length;
        message_header->msg_iov = &buffer;
        message_header->msg_iovlen = 1;
        received_size = recvmsg(sockfd, message_header, 0);
        printf("Received %d byte packet from %s\n", received_size, dst_addr);

        // ft_send_echo_request();
        // ft_catch_echo_reply();
    }
    return 0;
}