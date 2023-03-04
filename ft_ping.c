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


void ft_check_options(char **av, int *verbose)
{
    
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

void ft_build_icmp_header(void)
{
    
}

void ft_build_ip_header(void)
{
    
}

void ft_send_echo_request()
{
    
}

void ft_catch_echo_reply()
{
    
}

int main(int ac, char **av)
{
    int verbose = 0;
    //int sockfd = -1;

    if (ac < 2 || ac > 5)
    {
        printf("usage: ft_ping [-v] [-h sweep_increment] destination\n");
        exit(1);
    }
    else
    {
        ft_check_options(av, &verbose);
        // sockfd = ft_init_socket();
        // ft_build_icmp_header();
        // ft_build_ip_header();
        // ft_send_echo_request();
        // ft_catch_echo_reply();
    }
    return 0;
}