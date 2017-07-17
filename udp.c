#include <ctype.h>
#include <netinet/udp.h>
#include "udp.h"
#include "print.h"
#include "bootp.h"
#include "dns.h"

extern void handle_bootp(const unsigned char *);

/**
 *param const unsigned char *bytes : 
 * -> Fonction qui gère la partie UDP et appelle la fonction 
 *    qui correspond au type de protocole (BOOTP,DNS, ...) pour la suite de l'analyse 
 *    et affiche le contenu en héxadécimal puis en ascii.
 */

void handle_udp(const unsigned char *bytes) {
    struct udphdr *udp_hdr = (struct udphdr *)bytes;
    u_short source = ntohs(udp_hdr->source), dest = ntohs(udp_hdr->dest);
    printf2("        UDP     %u -> %u | Len %u | Checksum %u\n",
           source, dest, ntohs(udp_hdr->len), ntohs(udp_hdr->check));

    bytes += sizeof(struct udphdr);

    if(source == 53 || dest == 53) {
        handle_dns(bytes);
        print_hex3(bytes, ntohs(udp_hdr->len));
        print_ascii3(bytes, ntohs(udp_hdr->len));
	
    }
    else if(source == IPPORT_BOOTPS || dest == IPPORT_BOOTPS) {
        handle_bootp(bytes);
        print_hex3(bytes, ntohs(udp_hdr->len));
        print_ascii3(bytes, ntohs(udp_hdr->len));
    }
    else if(source == IPPORT_BOOTPC || dest == IPPORT_BOOTPC) {
        handle_bootp(bytes);
        print_hex3(bytes, ntohs(udp_hdr->len));
        print_ascii3(bytes, ntohs(udp_hdr->len));
    }
    else if(source == 137 || dest == 137) {
        print1("            NETBIOS Name Service \n\n");
        print_hex3(bytes, ntohs(udp_hdr->len));
        print_ascii3(bytes, ntohs(udp_hdr->len));
    }
    else {
        printf1("            ???     Unsupported UDP protocol with ports %u -> %u\n\n" ,ntohs(udp_hdr->source),ntohs(udp_hdr->dest) );
    }
}
