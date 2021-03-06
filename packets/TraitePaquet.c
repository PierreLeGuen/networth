#include <stdio.h>
#include "TraitePaquet.h"
#include <string.h>
#include "../utils/primitives.h"
#include "packetChecker.h"


Paquet traitePaquet(Host AnHost, char *buffer) {
    bool isModeConnecte = false;
    Host srcHost = {0};
    Host destHost = {0};
    Paquet recvPacket = {0};

    sscanf(buffer, "%d,%d,%d,%d,%d,%2050[^\n]s", &recvPacket.containsMsg, &srcHost.HOST_NUMBER, &destHost.HOST_NUMBER,
           &recvPacket.slotReserve, (int *) &recvPacket.CRC, (char *) &recvPacket.MESSAGE);

    if (recvPacket.containsMsg) {
        if (AnHost.HOST_NUMBER == destHost.HOST_NUMBER) {
            if (recvPacket.CRC != 0) {
                isModeConnecte = true;
            }
            printf("--- JE SUIS LE DESTINATAIRE --- \n");
            if (isModeConnecte) {
                int recvCrc = 0;
                recvCrc = crc16((const unsigned char *) &recvPacket.MESSAGE, strlen(recvPacket.MESSAGE));
                if (recvCrc == recvPacket.CRC) {
                    printf("--- MODE AVEC DÉTECTION D'ERREUR CRC : CORRECT ---\n");
                    printf("-- CRC attendu : %d, CRC reçu : %d\n", recvPacket.CRC, recvCrc);
                    printf("-- MESSAGE : %*s \n\n", 10, recvPacket.MESSAGE);
                } else {
                    printf("--- MODE AVEC DÉTECTION D'ERREUR CRC : FAUX ---\n");
                    printf("-- CRC attendu : %d, CRC reçu : %d\n", recvPacket.CRC, recvCrc);
                    printf("-- MESSAGE : %*s \n\n", 10, recvPacket.MESSAGE);

                }
            } else {
                printf("--- MODE SANS DÉTECTION D'ERREUR ---\n");
                printf("-- MESSAGE : %*s \n\n", 10, recvPacket.MESSAGE);
            }
        //Fonction permettnt de lire un message en broadcast.
        } else if (destHost.HOST_NUMBER==-1 && srcHost.HOST_NUMBER != AnHost.HOST_NUMBER){
            if (recvPacket.CRC != 0) {
                isModeConnecte = true;
            }
            printf("--- BROADCAST --- \n");
            if (isModeConnecte) {
                int recvCrc = 0;
                recvCrc = crc16((const unsigned char *) &recvPacket.MESSAGE, strlen(recvPacket.MESSAGE));
                if (recvCrc == recvPacket.CRC) {
                    printf("--- MODE AVEC DÉTECTION D'ERREUR CRC : CORRECT ---\n");
                    printf("-- CRC attendu : %d, CRC reçu : %d\n", recvPacket.CRC, recvCrc);
                    printf("-- MESSAGE : %*s \n\n", 10, recvPacket.MESSAGE);
                } else {
                    printf("--- MODE AVEC DÉTECTION D'ERREUR CRC : FAUX ---\n");
                    printf("-- CRC attendu : %d, CRC reçu : %d\n", recvPacket.CRC, recvCrc);
                    printf("-- MESSAGE : %*s \n\n", 10, recvPacket.MESSAGE);

                }
            } else {
                printf("--- MODE SANS DÉTECTION D'ERREUR ---\n");
                printf("-- MESSAGE : %*s \n\n", 10, recvPacket.MESSAGE);
            }
            envoie(AnHost.PRISE_EMISSION, buffer, strlen(buffer));
        }else if (srcHost.HOST_NUMBER == AnHost.HOST_NUMBER){
            memset(buffer, '\0', sizeof(buffer));
        }
        else {
            printf("--- PAS DESTINATAIRE ---\n");
            printf("DESTINATAIRE : %*d\n\n", 10, destHost.HOST_NUMBER);
            printf("--- ROUTAGE ---\n");
            envoie(AnHost.PRISE_EMISSION, buffer, strlen(buffer));
        }
    }
    return (recvPacket);
}
