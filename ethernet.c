#include <stdio.h>
#include <netinet/in.h>
#include "ethernet.h"
#include "ip.h"
#include "print.h"
#include "arp.h"


/**
 *param u_int8_t ether_addr[ETH_ALEN] : adresse MAC que l'on veut afficher
 * -> Afficher l'adresse MAC sous la forme conventionnelle
 */
void print_ether_address(u_int8_t ether_addr[ETH_ALEN]) {
    printf("%02x:%02x:%02x:%02x:%02x:%02x",
           ether_addr[0], ether_addr[1], ether_addr[2],
           ether_addr[3], ether_addr[4], ether_addr[5]);
}

/**
 *param  u_int16_t type : packet type ID field  
 * -> Permet l'affichage du type de protocole dans la fonction "void handle_ethernet" 
 */
void print_ether_type(u_int16_t type) {
    if(verbosity >= 2) {
        switch (type) {
            case ETHERTYPE_PUP:
                print2("PUP");
                break;          /* Xerox PUP */
            case ETHERTYPE_SPRITE:
                print2("SPRITE");
                break;        /* Sprite */
            case ETHERTYPE_IP:
                print2("IP");
                break;        /* IP */
            case ETHERTYPE_ARP:
                print2("ARP");
                break;        /* Address resolution */
            case ETHERTYPE_REVARP:
                print2("REVARP");
                break;        /* Reverse ARP */
            case ETHERTYPE_AT:
                print2("AT");
                break;        /* AppleTalk protocol */
            case ETHERTYPE_AARP:
                print2("AARP");
                break;        /* AppleTalk ARP */
            case ETHERTYPE_VLAN:
                print2("VLAN");
                break;        /* IEEE 802.1Q VLAN tagging */
            case ETHERTYPE_IPX:
                print2("IPX");
                break;        /* IPX */
            case ETHERTYPE_IPV6:
                print2("IPV6");
                break;        /* IP protocol version 6 */
            case ETHERTYPE_LOOPBACK:
                print2("LOOPBACK");
                break;        /* used to test interfaces */
            default:
                printf2("UNKNOWN (0x%x)", type);
                break;
        }
    }
 if((verbosity == 1) && type==ETHERTYPE_IPV6)
	print1("    IPV6\n");
	
}

/**
 *param const unsigned char *bytes 
 * -> Fonction qui gère la partie Ethernet et appelle la fonction 
 *    qui correspond au type de protocole (IP, ARP,...) pour la suite de l'analyse.
 */
void handle_ethernet(const unsigned char *bytes) {
    struct ether_header *eth_hdr = (struct ether_header *)bytes;
    eth_hdr->ether_type = ntohs(eth_hdr->ether_type);
    print2("ETHERNET   "); print_ether_address2(eth_hdr->ether_shost);
    print2(" -> "); print_ether_address2(eth_hdr->ether_dhost);
    print2(", "); print_ether_type(eth_hdr->ether_type);
    print2("\n");

    bytes += sizeof(struct ether_header);

    switch(eth_hdr->ether_type) {
        case ETHERTYPE_IP: return handle_ip(bytes);
        case ETHERTYPE_ARP: return handle_arp(bytes);
        case ETHERTYPE_REVARP: return handle_arp(bytes);
        default: return;
    }
}
