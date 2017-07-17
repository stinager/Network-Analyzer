#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <getopt.h>
#include "ethernet.h"
#include "ip.h"

int verbosity = 1;
char errbuf[PCAP_ERRBUF_SIZE]; // Message d'erreur

// Fonction qui permet de gérer les erreurs relatives à pcap
void abort_pcap(const char *error) {
    perror(error);
    fprintf(stderr, "%s\n", errbuf);
    exit(EXIT_FAILURE);
}

/*Fonction qui permet de numéroter les paquets capturés et fait appel à la fonction qui gère la partie ethernet */

void packet_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    static int packet_count = 0;
    int i=0;
    printf("\n--(");
    int number_len = printf("%d)", packet_count++);
    for(i = 3 + number_len; i <= 80; i++) putchar('-');
    putchar('\n');

    handle_ethernet(bytes);
}
/*
 * brief : Fonction main qui éxécute l'analyse des trames en internet
 * ou appelle en boucle la fonction qui parse les trames d'un fichier
 */
int main(int argc, char **argv) {
    char *device = NULL; // when capturing live
    char *capture_file = NULL; // when reading capture file
    pcap_t *capture;
    bpf_u_int32 ip;
    bpf_u_int32 mask = PCAP_NETMASK_UNKNOWN;
    const char *filter = "";
    struct bpf_program bpf_program;

    int option;
    while((option = getopt(argc, argv, "hi:o:f:v:")) != -1) {
        switch(option) {
            case 'h':
                fprintf(stderr, "usage: %s [-v verbosity] [-f filter] [-i interface]|[-o capture_file]\n", argv[0]);
                exit(EXIT_SUCCESS);
       // L'interface que l'on souhaite écouter
            case 'i':
                device = optarg;
                break;
	// Le fichier à décoder
            case 'o':
                capture_file = optarg;
                break;
            case 'f':
	// Filtrage 
                filter = optarg;
                printf("using \"%s\" as BPF filter\n", filter);
                break;
	// Niveau de verbosité souhaité (par défault : 1)
            case 'v':
                verbosity = atoi(optarg);
                if(verbosity < 1 || verbosity > 3) {
                    fprintf(stderr, "invalid verbosity level %d\n", verbosity);
                    exit(EXIT_FAILURE);
                }
                break;
            default: break;
        }
    }

    if(device != NULL && capture_file != NULL) {
        fprintf(stderr, "Error: you must choose between live capture or capture file\n");
        exit(EXIT_FAILURE);
    }

    if(capture_file == NULL) {
        if(device == NULL && (device = pcap_lookupdev(errbuf)) == NULL) {
            abort_pcap("pcap_lookupdev");
        }
        printf("\nUsing device %s for capture ( IP addr : ", device);

        if(pcap_lookupnet(device, &ip, &mask, errbuf) != 0) {
            abort_pcap("pcap_lookupnet");
        }

        print_ip_addr(ip); printf(" | Mask addr : "); print_ip_addr(mask); printf(")\n");

        if((capture = pcap_open_live(device, 1500, 0, 100, errbuf)) == NULL) {
            abort_pcap("pcap_open_live");
        }
    }
    else {
	// Dans le cas où un fichier est fourni, on le traite
        if((capture = pcap_open_offline(capture_file, errbuf)) == NULL) {
            abort_pcap("pcap_open_offline");
        }
    }

    if(pcap_compile(capture, &bpf_program, filter, 0, mask) != 0) {
        abort_pcap("pcap_compile");
    }

    if(pcap_setfilter(capture, &bpf_program) != 0) {
        abort_pcap("pcap_setfilter");
    }

    pcap_freecode(&bpf_program);

    pcap_loop(capture, -1, &packet_handler, NULL);

    return EXIT_SUCCESS;
}
