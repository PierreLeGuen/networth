//
// Created by pierre on 08/03/19.
//

#include <stdio.h>
#include "TraitePaquet.h"
#include <string.h>
#include "primitives.h"
#include "packetChecker.h"


Paquet traitePaquet(Host AnHost, char *buffer) {
    bool isModeConnecte = false;
    Host srcHost = {0};
    Host destHost = {0};
    Paquet recvPacket = {0};

    sscanf(buffer, "%d,%d,%d,%d,%d,%2050[^\n]s", &recvPacket.containsMsg, &srcHost.HOST_NUMBER, &destHost.HOST_NUMBER,
           &recvPacket.AccuseReception, &recvPacket.CRC, &recvPacket.MESSAGE);

    if (recvPacket.containsMsg) {
        if (AnHost.HOST_NUMBER == destHost.HOST_NUMBER) {
            if (recvPacket.CRC != 0) {
                isModeConnecte = true;
            }
            printf("Je suis le destinataire. \n");
            if (isModeConnecte) {
                int recvCrc = 0;
                int AR[LONGUEUR_MESSAGE] = {0};

                recvCrc = crc16(&recvPacket.MESSAGE, strlen(recvPacket.MESSAGE));
                if (recvCrc == recvPacket.CRC) {
                    printf("Mode CONNECTE détecté. CRC : CORRECT\n");
                    printf("MSG : %*s \n\n", 20, recvPacket.MESSAGE);
                    // recvPacket.AccuseReception = 0;
                    // sprintf(buffer, "%d,%d,%d,%d,%s", destHost.HOST_NUMBER, srcHost.HOST_NUMBER, recvPacket.AccuseReception, recvPacket.CRC, recvPacket.MESSAGE);
                    // envoie(AnHost.PRISE_EMISSION, buffer, strlen(buffer));
                } else {
                    printf("Mode CONNECTE détecté. CRC : FAUX\n");
                    printf("CRC attendu : %d, CRC reçu : %d\n", recvPacket.CRC, recvCrc);
                    sprintf(buffer, "%d,%d,%d,%d,%s", destHost.HOST_NUMBER, srcHost.HOST_NUMBER,
                            recvPacket.AccuseReception,
                            recvPacket.CRC, recvPacket.MESSAGE);
                    // envoie(AnHost.PRISE_EMISSION, buffer, strlen(buffer));
                    // recoit(AnHost.PRISE_RECEPTION, buffer, sizeof(buffer) - 1);
                    // traitePaquet(AnHost, buffer);

                    //TODO Demander le renvoi du paquet
                }
            } else {
                printf("Mode NON CONNECTE détecté\n");
                printf("MSG : %*s \n\n", 20, recvPacket.MESSAGE);
            }
        } else {
            printf("Je ne suis PAS le destinataire. \n");
            printf("DEST : %*d\n\n", 20, destHost.HOST_NUMBER);
            printf("Routage vers destinataire\n");
            envoie(AnHost.PRISE_EMISSION, buffer, strlen(buffer));
        }
    } else {
        printf("TOKEN IS FREE\n");
    }
    return(recvPacket);
}