# Network-Analyzer
School project 

Utilisation du code :

Pour générer l'éxécutable : Taper make pour générer l'executable 
Pour lancer le programme : 
Taper ./all -i <interface> -v<1 2 ou 3> -o <nom du fichier> -f <filtre> 

Mais ce n'est pas obligatoire de taper toutes les options, dans ce cas là les paramètres par défault seront appliqués. 

Réalisation :

On a la présence des quatres options -i -o -v -f fonctionnelles :
-o : Permet de lire un fichier pcap et de décoder les trames (utile pour le test de protocoles précis) 
-i : Permet pour choisir l'interface que l'on écoute 
-v : Permet de choisir la verbosité (1 : très concis par défault)
-f : Permet de filtrer 

Les protocoles suivants on été traités : 
_ Ethernet
_ IP
_ UDP
_ TCP 
_ ICMP
_ ARP
_ BOOTP et DHCP
_ DNS
_ HTTP(S)
_ FTP (serveur et client)
_ SMTP(S)
_ Telnet 
_ POP/IMAP (détection et affichage héxa/ascii)
