#include <netinet/ip_icmp.h>
#include "icmp.h"
#include "print.h"

/**
 *param const unsigned char *bytes
 * -> Fonction qui gère la partie ICMP : affichage du type, du code et dans certains cas : l'id, checksum et le num de seq
 */ 

void handle_icmp(const unsigned char *bytes) {
    struct icmphdr *icmp_hdr = (struct icmphdr *)bytes;
    print1("ICMP    ");

    switch(icmp_hdr->type) {
        case ICMP_ECHOREPLY:
            print1("Echo Reply");
            break;
        case ICMP_DEST_UNREACH:
            print1("Destination Unreachable");
            break;
        case ICMP_SOURCE_QUENCH:
            print1("Source Quench");
            break;
        case ICMP_REDIRECT:
            print1("Redirect (change route)");
            break;
        case ICMP_ECHO:
            print1("Echo Request");
            break;
        case ICMP_TIME_EXCEEDED:
            print1("Time Exceeded");
            break;
        case ICMP_PARAMETERPROB:
            print1("Parameter Problem");
            break;
        case ICMP_TIMESTAMP:
            print1("Timestamp Request");
            break;
        case ICMP_TIMESTAMPREPLY:
            print1("Timestamp Reply");
            break;
        case ICMP_INFO_REQUEST:
            print1("Information Request");
            break;
        case ICMP_INFO_REPLY:
            print1("/* Information Reply");
            break;
        case ICMP_ADDRESS:
            print1("Address Mask Request");
            break;
        case ICMP_ADDRESSREPLY:
            print1("Address Mask Reply");
            break;
        default:
            print1("Unknown type");
    }

    printf1(" (%u)", icmp_hdr->type);
    printf1(" | Code %u", icmp_hdr->code);
    if(icmp_hdr->type == ICMP_ECHO || icmp_hdr->type == ICMP_ECHOREPLY)
        printf1("| Id %u | Checksum %u | Seq %u", icmp_hdr->un.echo.id, icmp_hdr->checksum, icmp_hdr->un.echo.sequence);

    print1("\n");
}
