#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define PING_PKT_SIZE 64
#define PING_SLEEP_RATE 1

// Checksum calculation
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (; len > 1; len -= 2)
        sum += *buf++;

    if (len == 1)
        sum += *(unsigned char*)buf;

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2)
        printf("Usage: %s <hostname/IP>\n", argv[0]);
        return 1;
    }

    int sockfd;
    struct sockaddr_in addr;
    struct hostent *host;

    char *ip = NULL;
    char *hostname = argv[1];

    if ((host = gethostbyname(hostname)) == NULL) {
        perror("gethostbyname");
        return 1;
    }

    ip = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);

    printf("PING %s (%s): %d bytes of data\n", hostname, ip, PING_PKT_SIZE);

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    char packet[PING_PKT_SIZE];
    memset(packet, 0, sizeof(packet));

    struct icmphdr *icmp = (struct icmphdr*) packet;
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = getpid();
    icmp->un.echo.sequence = i + 1;
    icmp->checksum = checksum(packet, sizeof(packet));

    struct timeval start, end;
    gettimeofday(&start, NULL);

    if (sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&addr, sizeof(addr)) <= 0) {
        perror("sendto");
    }

    char recv_buf[1024];
    struct sockaddr_in r_addr;
    socklen_t addr_len = sizeof(r_addr);

    recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&r_addr, &addr_len);

    gettimeofday(&end, NULL);

    struct iphdr *ip_hdr = (struct iphdr*)recv_buf;
    struct icmphdr *icmp_hdr = (struct icmphdr*)(recv_buf + ip_hdr->ihl * 4);

    double rtt = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;

    if (icmp_hdr->type == ICMP_ECHOREPLY) {
        printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.2f ms\n",
                PING_PKT_SIZE,
                inet_ntoa(r_addr.sin_addr),
                icmp_hdr->un.echo.sequence,
                ip_hdr->ttl,
                rtt);
    } else {
        printf("Received non-echo-reply packet\n");
    }


    close(sockfd);
    return 0;
}
