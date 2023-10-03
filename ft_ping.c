/*

the main goal is to re write the ping command in C :
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

#include "ft_ping.h"

int main(int ac, char **av)
{
    if (ac < 2 || ac > 5)
    {
        printf("usage: ft_ping [-? help] [-v verbose] destination\n");
        exit(1);
    }
    ft_init_structure();
    ft_check_options(ac, av);
	signal(SIGINT, ft_sig_handler);
    ft_send_ping_packet();
    return 0;
}