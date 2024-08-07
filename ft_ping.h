#ifndef FT_PING_H
# define FT_PING_H

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

// typedef struct  iovec_s
// {
// 	void *   iov_base;      /* [XSI] Base address of I/O memory region */
// 	size_t   iov_len;       /* [XSI] Size of region iov_base points to */
// }               iovec_t;

// typedef struct  msghdr_s
// {
// 	void            *msg_name;      /* [XSI] optional address */
// 	socklen_t       msg_namelen;    /* [XSI] size of address */
// 	iovec_t         *msg_iov;       /* [XSI] scatter/gather array */
// 	int             msg_iovlen;     /* [XSI] # elements in msg_iov */
// 	void            *msg_control;   /* [XSI] ancillary data, see below */
// 	socklen_t       msg_controllen; /* [XSI] ancillary data buffer len */
// 	int             msg_flags;      /* [XSI] flags on received message */
// }               msghdr_t;

// typedef struct  icmphdr_s
// {
//     u_int8_t type;
//     u_int8_t code;
//     u_int16_t checksum;
//     union
//     {
//         struct
//         {
//             u_int16_t id;
//             u_int16_t sequence;
//         } echo;
//         unsigned int gateway;
//         struct
//         {
//             u_int16_t __unused;
//             u_int16_t mtu;
//         } frag;
//     } un;
// }               icmphdr_t;
 
// typedef struct  iphdr_s
// {
//     unsigned int ip_version;
//     unsigned int ip_headerlength;
//     unsigned char ip_tos;
//     unsigned short ip_total_length;
//     unsigned short ip_id;
//     unsigned short ip_offset;
//     unsigned char ip_ttl;
//     unsigned char ip_protocol;
//     unsigned short ip_checksum;
//     struct in_addr ip_srcaddr;
//     struct in_addr ip_destaddr;
// }               iphdr_t;

typedef struct	s_echo_packet
{
	struct iphdr	*ip;
	struct icmphdr	*hdr;
}				t_echo_packet;

typedef struct g_ping_packet
{
	t_echo_packet	packet;
	int				verbose;
}				t_ping_packet;



void ft_check_options(int ac, char **av, t_ping_packet *g_ping_packet);
int ft_check_valid_ip(char *string);

struct icmphdr *ft_build_icmp_header(void);
struct iphdr *ft_build_ip_header(char *src_addr, char *dst_addr);

unsigned short ft_get_checksum(unsigned short* addr, int len);
void ft_get_round_trip_time(void);

void ft_print_ip_header(struct iphdr *ip_header);
void ft_print_icmp_header(struct icmphdr *icmp_header);

void ft_init_structure(t_ping_packet *g_ping_packet);
int ft_init_socket(void);

void ft_send_ping_packet(t_ping_packet *g_ping_packet);
void ft_send_echo_request(void);
void ft_catch_echo_reply(void);
void ft_free_packet(t_ping_packet *g_ping_packet);

void ft_display_help(void);
void ft_sig_handler(int sig);
#endif