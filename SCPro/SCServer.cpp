#include "SCServer.h"
#include <string.h>
#include <stdio.h>
#include <pthread.h>
char buffer[124000];
char cmd[992000];
void keygen(char *PubKey, char *Privkey, const long n){
     paillier_prvkey_t* secKey;
     paillier_pubkey_t* pubKey;
     paillier_keygen(n, &pubKey, &secKey, paillier_get_rand_devurandom);
     FILE *fp1 = fopen("privkey.txt", "w");
     FILE *fp2 = fopen("pubkey.txt", "w");
     char* hexSecKey = paillier_prvkey_to_hex(secKey);
     char* hexPubKey = paillier_pubkey_to_hex(pubKey);
     fwrite(hexSecKey, 1, strlen(hexSecKey), fp1);
     fwrite(hexPubKey, 1, strlen(hexPubKey), fp2);
     fclose(fp1);
     fclose(fp2);
     strcpy(PubKey, hexPubKey);
     strcpy(Privkey, hexSecKey);
}
void SCSDec(paillier_ciphertext_t* c, char *hexPrvKey, char *hexPubKey, char *decstr){
    paillier_pubkey_t* pubKey;
    pubKey = paillier_pubkey_from_hex(hexPubKey);
    paillier_prvkey_t* prvKey;
    prvKey = paillier_prvkey_from_hex(hexPrvKey, pubKey);
    paillier_plaintext_t* dec;
    dec = paillier_dec(NULL, pubKey, prvKey, c);
    gmp_sprintf(decstr, "%Z08x", dec);
}
int MinGC(char *rndp, char *distancep, int num){
    FILE* fp;
    sprintf(cmd, "./TinyGarble --alice --scd_file ./scd/MinGC.scd -p 9999 --input %s --clock_cycles %d", distancep, num);
    popen(cmd, "r");
    sprintf(cmd, "./TinyGarble --bob --scd_file ./scd/MinGC.scd -p 9999 --input %s --clock_cycles %d", rndp, num);
    fp = popen(cmd, "r");
    fgets(buffer, 124000, fp);
    if(strlen(buffer) == 0){
          return -1;
    }
    else{
         buffer[strlen(buffer) - 1] = '\0';
         return check_hsb(num, buffer);
    }
    return 0;
}
int check_hsb(int num, char *buffer){
    int strn = strlen(buffer);
    int pos = 0;
    while(buffer[pos]=='0' && pos < strn){
        pos++;
    }
    if(buffer[pos] == '0'){
        return 0;
    }
    else{
        int tmp = buffer[pos] - '0';
        if(tmp & 8){
            return num - (strn - pos) * 4;
        }
        else if(tmp & 4){
            return num - (strn - pos) * 4 + 1;
        }
        else if(tmp & 2){
            return num - (strn - pos) * 4 + 2;
        }
        else if(tmp & 1){
            return num - (strn - pos) * 4 + 3;
        }
    }
    return 0;
}
