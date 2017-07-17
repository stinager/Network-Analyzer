#include <netinet/tcp.h>
#include <netinet/in.h>
#include "tcp.h"
#include "print.h"
#include "http.h"
#include "ftp.h"

extern void handle_telnet(const unsigned char *bytes, uint16_t frame_len);
extern void handle_http(const unsigned char *bytes);
extern void handle_smtp(const unsigned char *bytes, uint16_t frame_len);

static int flag_count;

/**
 *param const char *name
 * -> Fonction qui affiche un ou plusieurs flags en fonction du cas 
 */

void print_flag(const char *name) {
    if(flag_count > 0) {
        printf2(", %s", name);
    }
    else {
        print2(name);
    }
    flag_count++;
}

/**
 *param u_int8_t flags
 * -> Fonction qui détecte les flags présents et les affiche en faisant appel à la fonction ci-dessus "print_flag" 
 */

void print_flags(u_int8_t flags) {
    flag_count = 0;
    if(flags & TH_FIN) print_flag("FIN");
    if(flags & TH_SYN) print_flag("SYN");
    if(flags & TH_RST) print_flag("RST");
    if(flags & TH_PUSH) print_flag("PUSH");
    if(flags & TH_ACK) print_flag("ACK");
    if(flags & TH_URG) print_flag("URG");
}


/**
 *params const unsigned char *bytes, uint16_t segment_len 
 * -> Fonction qui gère la partie TCP et appelle la fonction 
 *    qui correspond au type de protocole (HTTP, Telnet, SMTP, ...) pour la suite de l'analyse et 
 *    affiche le contenu en héxadécimal puis en ascii dans chaque cas.
 */

void handle_tcp(const unsigned char *bytes, uint16_t segment_len) {
    struct tcphdr *tcp_hdr = (struct tcphdr *) bytes;
    tcp_hdr->th_sport = ntohs(tcp_hdr->th_sport);
    int size= (int)tcp_hdr->th_off;
    tcp_hdr->th_dport = ntohs(tcp_hdr->th_dport);
    printf2("        TCP     %u -> %u | [", tcp_hdr->th_sport, tcp_hdr->th_dport);
    print_flags(tcp_hdr->th_flags);
    print2("] ");
    printf2("| Data Offset %d | Seq %u | Ack %u | Window %u\n", size, ntohl(tcp_hdr->seq), ntohl(tcp_hdr->ack_seq), ntohs(tcp_hdr->window));

    int data_offset = 4 * tcp_hdr->th_off;
    const unsigned char *end = bytes + data_offset;
    bytes += sizeof(struct tcphdr);

    while(bytes < end) {
        uint8_t kind = *bytes++;

        uint8_t len = 0;
        if(kind != 0 && kind != 1)
            len = *bytes++;

        printf3("           | option %u: ", kind);
        switch(kind) {
            case 0: print3("End of options"); break;
            case 1: print3("No operation (NOP)"); break;
            case 2: printf3("MSS %u", (*(uint32_t*) bytes)); break;
            case 3: print3("Window scale"); break;
            case 4: print3("SACK permited"); break;
            case 5: print3("SACK"); break;
            case 8: print3("Timestamps"); break;
            default: print3("Unknown"); break;
        }
        print3("\n");

        // advance by the size of the option read
        if(kind != 0 && kind != 1)
            bytes += len - 2;
    }

    if(tcp_hdr->th_sport == 80 || tcp_hdr->th_dport == 80) {
	    printf1("              HTTP : Ports %u -> %u\n", tcp_hdr->th_sport, tcp_hdr->th_dport);
            handle_http(bytes);
	    print_hex3(bytes, segment_len- data_offset);
            print_ascii3(bytes, segment_len - data_offset);
    }
    else if(tcp_hdr->th_sport == 443 || tcp_hdr->th_dport == 443) {
	    printf1("              HTTPS : Ports %u -> %u\n", tcp_hdr->th_sport, tcp_hdr->th_dport);
	    handle_http(bytes);
	    print_hex3(bytes, segment_len- data_offset);
            print_ascii3(bytes, segment_len - data_offset);
	
	}
    else if(tcp_hdr->th_sport == 23 || tcp_hdr->th_dport == 23) {
            handle_telnet(bytes, segment_len - data_offset);
	    print_hex3(bytes, segment_len- data_offset);
            print_ascii3(bytes, segment_len - data_offset);
    }
    else if(tcp_hdr->th_sport == 587 || tcp_hdr->th_dport == 587) {
            printf1("              SMTPS : Ports %u -> %u\n", tcp_hdr->th_sport, tcp_hdr->th_dport);
            handle_smtp(bytes, segment_len - data_offset);
	    print_hex3(bytes, segment_len- data_offset);
            print_ascii3(bytes, segment_len - data_offset);
    }
    else if(tcp_hdr->th_sport == 25 || tcp_hdr->th_dport == 25) {
            printf1("              SMTP : Ports %u -> %u\n", tcp_hdr->th_sport, tcp_hdr->th_dport);
            handle_smtp(bytes, segment_len - data_offset);  
	    print_hex3(bytes, segment_len- data_offset);
            print_ascii3(bytes, segment_len - data_offset);  
    }   
    else if(tcp_hdr->th_sport == 22 || tcp_hdr->th_dport == 22){
	    printf1("              FTP : Envoi de données | Ports %u -> %u\n", tcp_hdr->th_sport, tcp_hdr->th_dport);
	    handle_http(bytes);
	    print_hex3(bytes, segment_len - data_offset);
            print_ascii3(bytes, segment_len - data_offset);
    }
    else if(tcp_hdr->th_sport == 21 || tcp_hdr->th_dport == 21){
	    printf1("              FTP : Envoi de requêtes | Ports %u -> %u\n", tcp_hdr->th_sport, tcp_hdr->th_dport);
	    handle_ftp(bytes);
	    print_hex3(bytes, segment_len - data_offset);
            print_ascii3(bytes, segment_len - data_offset);
    }
    else if(tcp_hdr->th_sport == 110 || tcp_hdr->th_dport == 110){
	    printf1("              POP3 : Ports %u -> %u\n", tcp_hdr->th_sport, tcp_hdr->th_dport);
	    print_hex3(bytes, segment_len - data_offset);
            print_ascii3(bytes, segment_len - data_offset);
    }
else if(tcp_hdr->th_sport == 143 || tcp_hdr->th_dport == 143){
	    printf1("              IMAP : Ports %u -> %u\n", tcp_hdr->th_sport, tcp_hdr->th_dport);
	    print_hex3(bytes, segment_len - data_offset);
            print_ascii3(bytes, segment_len - data_offset);
    }

    else {
        printf1("                ???  Unknown TCP application with ports %u -> %u\n", tcp_hdr->th_sport, tcp_hdr->th_dport);
    }
}
