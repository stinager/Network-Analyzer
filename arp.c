#include <net/if_arp.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include "arp.h"
#include "print.h"
#include "ethernet.h"
#include "ip.h"

/**
 *param const unsigned char *bytes 
 * -> Fonction qui gère la partie ARP, affiche du flag : (Request, Reply)
 */

void handle_arp(const unsigned char *bytes) {
    struct arphdr *arp_hdr = (struct arphdr *)bytes;
    arp_hdr->ar_op = ntohs(arp_hdr->ar_op);
    print1("    ARP     ");

    switch(arp_hdr->ar_op) {
        case ARPOP_REQUEST: print1("Request"); break;
        case ARPOP_REPLY: print1("Reply"); break;
        case ARPOP_RREQUEST: print1("R-request"); break;
        case ARPOP_RREPLY: print1("R-reply"); break;
        default: printf1("Opcode %u", arp_hdr->ar_op); break;
    }

    bytes += sizeof(struct arphdr);

    // Verification si on a bien Ethernet et IPv4
    if(arp_hdr->ar_hln == 6 && arp_hdr->ar_pln == 4) {
        print1(" : ");
        print_ether_address1((u_int8_t *) bytes);
        bytes += 6;
        print1(" (");
        print_ip_addr1(*(int32_t *) bytes);
        bytes += 4;
        print1(") -> ");
        print_ether_address1((u_int8_t *) bytes);
        bytes += 6;
        print1(" (");
        print_ip_addr1(*(int32_t *) bytes);
        bytes += 4;
        print1(")");
    }
    print1("\n");
}
