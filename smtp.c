#include <string.h>
#include "http.h"
#include "print.h"
#include "ip.h"
#include "smtp.h"
#include "ascii.h"

/**
 *param const unsigned char *bytes, uint16_t frame_len
 * -> Fonction qui gère la partie SMTP : affichage du type de message et détails sur le contenu 
 */
void handle_smtp(const unsigned char *bytes, uint16_t frame_len) {
    print_ips_from_last_header_v1();

    if(strncmp("SMTP", bytes, 5) == 0
       || strncmp("MAIL", bytes, 4) == 0
       || strncmp("RCPT", bytes, 4) == 0
       || strncmp("DATA", bytes, 4) == 0
       || strncmp("HELO", bytes, 4) == 0
       || strncmp("AUTH", bytes, 4) == 0
       || strncmp("STARTTLS", bytes, 9) == 0
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
        print1("                [... SMTP Content...]\n");
    }

}
