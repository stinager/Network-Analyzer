#include <stdio.h>
#include <netinet/in.h>
#include "ethernet.h"
#include <netinet/ip.h>
#include "ip.h"
#include "udp.h"
#include "tcp.h"
#include "print.h"
#include "icmp.h"

/**
 *param int32_t ip : adresse IP que l'on veut afficher
 * -> Afficher l'adresse IP sous la forme conventionnelle
 */
void print_ip_addr(int32_t ip) {
    int32_t bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
    printf("%d.%d.%d.%d ", bytes[0], bytes[1], bytes[2], bytes[3]);
}

static struct iphdr *ip_hdr;

/**
 * -> Dans le cas verbosity=1 : on affiche seulement les adresses IP Source et Destination
 * On fait appel à cette fonction dans bootp.c, dns.c et telnet.c par exemple
 */ 

void print_ips_from_last_header_v1() {
    if(verbosity == 1) {
        printf("[");
        print_ip_addr(ip_hdr->saddr);
        printf(" -> ");
        print_ip_addr(ip_hdr->daddr);
        printf("] ");
    }
}

/**
 *param const unsigned char *bytes 
 * -> Fonction qui gère la partie IP et appelle la fonction 
 *    qui correspond au type de protocole (ICMP, UDP, TCP, ...) pour la suite de l'analyse.
 */

void handle_ip(const unsigned char *bytes) {
    ip_hdr = (struct iphdr *)bytes;
    printf1("    IPv%d    ", ip_hdr->version); print_ip_addr2(ip_hdr->saddr);
    print2(" -> "); print_ip_addr2(ip_hdr->daddr);
    printf3("| Ihl : %u | Tos : %u | ", ip_hdr->ihl, ip_hdr->tos);
    uint16_t len = ntohs(ip_hdr->tot_len);
    printf2("| Len : %u | ", len);
    printf2("ID : %u | ", ip_hdr->id);
    printf3("Foff : %u | ttl : %u | ", ip_hdr->frag_off, ip_hdr->ttl);
    printf3("Protocol : 0x%x | ", ip_hdr->protocol);
    printf3("Checksum : 0x%x ", ip_hdr->check);

    const u_char *ip_hdr_end = bytes + 4 * ip_hdr->ihl;

    while(bytes < ip_hdr_end) {
        bytes++;
    }
    print2("\n");

    if(ip_hdr->protocol == 0x01) {
        handle_icmp(bytes);
    }
    else if(ip_hdr->protocol == 0x11) {
        handle_udp(bytes);
    }
    else if(ip_hdr->protocol == 0x06) {
        handle_tcp(bytes, len - sizeof(struct iphdr));
    }
    else if(ip_hdr->protocol == 0x84) {
        printf("    SCTP\n");
      
    }
    else {
        printf("    ???     Unsupported transport protocol 0x%x\n\n", ip_hdr->protocol);
    }
}
