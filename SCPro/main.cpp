#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include "time.h"
#include "SCServer.h"
#include "client.h"
#include "PSP.h"
using namespace std;
int TOTAL = 10000;
char rndp[992000], sump[992000];
int main()
{
    float client_t = 0, PSP_t = 0, SCS_t = 0, PSP_SCS_t = 0;
    int start = 0, end = 0;
    FILE *fp;
    int num = 0;
    char line[100];
    char Lx[10], Ly[10];
    fp = fopen("./data/xy_LA.txt", "r");
    int pos = 0;
    srand(time(NULL));
    char pk[257], sk[257];
    //generate keys in the SCServer
    keygen(pk, sk, 1024);
    while(fgets(line, 100, fp) != NULL){
        printf("------------pre proceed:%d----------\n", num);
        sscanf(line, "%*s%*s%s%s", Lx, Ly);
        //encrypt in the client
        int x = atoi(Lx);
        int y = atoi(Ly);
        start = clock();
        paillier_ciphertext_t* ct = EncDistance(141922, 42333, x, y, pk);
        end = clock();
        client_t += end - start;
        //PSP
        //pick a random integer
        start = clock();
        int rnd = rand()%1000000;
        paillier_ciphertext_t* encryptedSum = AddRnd(ct, pk, rnd);
        sprintf(&rndp[pos], "%08x", -rnd);
        end = clock();
        PSP_t += end - start;
        //SCServer
        start = clock();
        SCSDec(encryptedSum, sk, pk, &sump[pos]);
        end = clock();
        SCS_t += end - start;
        pos += 8;
        num += 1;
        if(num == TOTAL){
            break;
        }
    }
    fclose(fp);
    //SCServer-PSP
    printf("----Start MinGC in SCServer-PSP----\n");
    struct timeval st, ed;
    gettimeofday( &st, NULL );
    int min = MinGC(rndp, sump, num);
    gettimeofday( &ed, NULL );
    PSP_SCS_t =  1000000 * (ed.tv_sec-st.tv_sec)+ ed.tv_usec-st.tv_usec;
    if (min < 0){
        printf("please wait the port closed...\n");
    }
    else{
        FILE *flog = fopen("./log/log.txt", "a");
        fprintf(flog, "Client Time:%f\n", client_t/CLOCKS_PER_SEC);
        fprintf(flog, "PSP Time:%f\n", PSP_t/CLOCKS_PER_SEC);
        fprintf(flog, "SCServer Time:%f\n", SCS_t/CLOCKS_PER_SEC);
        fprintf(flog, "PSP-SCServer Time:%f\n\n", PSP_SCS_t/CLOCKS_PER_SEC);
        fclose(flog);
        printf("Client Time:%f\n", client_t/CLOCKS_PER_SEC);
        printf("PSP Time:%f\n", PSP_t/CLOCKS_PER_SEC);
        printf("SCServer Time:%f\n", SCS_t/CLOCKS_PER_SEC);
        printf("PSP-SCServer Time:%f\n", PSP_SCS_t/CLOCKS_PER_SEC);
        printf("min identifier:%d\n", min);
    }
    return 0;
}

