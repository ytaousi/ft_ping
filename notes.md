**ICMP PROTOCOL**
```
     it is the error and control message protocol used by IP and the Internet protocol family.  It may be accessed through a ``raw socket'' for network monitoring
     and diagnostic functions.  The proto parameter to the socket call to create an ICMP socket is obtained from getprotobyname(3).  ICMP sockets are connectionless,
     and are normally used with the sendto and recvfrom calls, though the connect(2) call may also be used to fix the destination for future packets (in which case
     the read(2) or recv(2) and write(2) or send(2) system calls may be used).

     Outgoing packets automatically have an IP header prepended to them (based on the destination address).  Incoming packets are received with the IP header and
     options intact.  Note that the ip_off and ip_len fields are in host byte order.  For more information about the IP header structure, see ip(4)
```

**ICMP PACKET DETAILS**
``` 
     An IP header without options is 20 bytes.  An ICMP ECHO_REQUEST packet contains an additional 8 bytes worth
     of ICMP header followed by an arbitrary amount of data.  When a packetsize is given, this indicated the
     size of this extra piece of data (the default is 56).  Thus the amount of data received inside of an IP
     packet of type ICMP ECHO_REPLY will always be 8 bytes more than the requested data space (the ICMP header).

     If the data space is at least eight bytes large, ping uses the first eight bytes of this space to include a
     timestamp which it uses in the computation of round trip times.  If less than eight bytes of pad are speci-
     fied, no round trip times are given.
```

**TTL DETAILS**
```
     The TTL value of an IP packet represents the maximum number of IP routers that the packet can go through
     before being thrown away.  In current practice you can expect each router in the Internet to decrement the
     TTL field by exactly one.

     The TCP/IP specification recommends setting the TTL field for IP packets to 64, but many systems use
     smaller values (4.3BSD uses 30, 4.2BSD used 15).

     The maximum possible value of this field is 255, and most UNIX systems set the TTL field of ICMP
     ECHO_REQUEST packets to 255.  This is why you will find you can ``ping'' some hosts, but not reach them
     with telnet(1) or ftp(1).

     In normal operation ping prints the ttl value from the packet it receives.  When a remote system receives a
     ping packet, it can do one of three things with the TTL field in its response:

     o   Not change it; this is what BSD systems did before the 4.3BSD-Tahoe release.  In this case the TTL
         value in the received packet will be 255 minus the number of routers in the round-trip path.

     o   Set it to 255; this is what current BSD systems do.  In this case the TTL value in the received packet
         will be 255 minus the number of routers in the path from the remote system to the pinging host.

     o   Set it to some other value.  Some machines use the same value for ICMP packets that they use for TCP
         packets, for example either 30 or 60.  Others may use completely wild values.
```

![](./Screen%20Shot%202023-02-25%20at%208.46.12%20AM.png)


**icmphdr structure**
```
struct icmphdr
{
  u_int8_t type;                /* message type */
  u_int8_t code;                /* type sub-code */
  u_int16_t checksum;
  union
  {
    struct
    {
      u_int16_t        id;
      u_int16_t        sequence;
    } echo;                        /* echo datagram */
    u_int32_t        gateway;        /* gateway address */
    struct
    {
      u_int16_t        __unused;
      u_int16_t        mtu;
    } frag;                        /* path mtu discovery */
  } un;
};
```