#include <string.h>
#include "ftp.h"
#include "print.h"
#include "ip.h"

/**
 *param const unsigned char *bytes
 * -> Fonction qui gère la partie FTP : affichage des méthodes.
 */ 

void handle_ftp(const unsigned char *bytes) {
    print_ips_from_last_header_v1();

    if(strncmp("FTP", bytes, 3) == 0
       || strncmp("USER", bytes, 4) == 0
       || strncmp("PASS", bytes, 4) == 0
       || strncmp("ACCT", bytes, 4) == 0
       || strncmp("PORT", bytes, 4) == 0
       || strncmp("PASV", bytes, 4) == 0
       || strncmp("DELE", bytes, 4) == 0
       || strncmp("LIST", bytes, 4) == 0
       || strncmp("HELP", bytes, 4) == 0
       || strncmp("NOOP", bytes, 4) == 0
       || strncmp("QUIT", bytes, 4) == 0) {

        while(*bytes != '\n')
            putchar1(*bytes++);

        putchar('\n');
        bytes++;

        while(strncmp("\r\n", bytes, 2) != 0) { // print headers (<==> until we have double \n)
            print3("        ");

            while(*bytes != '\n')
                putchar3(*bytes++);

            putchar3('\n');
            bytes++;
        }
    }
    else {
        print1("                [... FTP Content...]\n");
    }

}
