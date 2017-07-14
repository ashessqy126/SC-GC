#include <iostream>
#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include "paillier.h"

using namespace std;

int main()
{
    const long n = 1024;
    //generate keys from files
    FILE *fp1 = fopen("privkey.txt", "r");
    FILE *fp2 = fopen("pubkey.txt", "r");
    paillier_prvkey_t* secKey;
    paillier_pubkey_t* pubKey;
    if(fp1 == NULL  || fp2 == NULL){
        paillier_keygen(n, &pubKey, &secKey, paillier_get_rand_devurandom);
         fp1 = fopen("privkey.txt", "w");
         fp2 = fopen("pubkey.txt", "w");
         char* hexSecKey = paillier_prvkey_to_hex(secKey);
         char* hexPubKey = paillier_pubkey_to_hex(pubKey);
         fwrite(hexSecKey, 1, strlen(hexSecKey), fp1);
         fwrite(hexPubKey, 1, strlen(hexPubKey), fp2);
         fclose(fp1);
         fclose(fp2);
    }
    else{
        char hexPubKey[100], hexPrivKey[100];
        fgets(hexPubKey, 100, fp1);
        fgets(hexPrivKey, 100, fp2);
        pubKey = paillier_pubkey_from_hex(hexPubKey);
        secKey = paillier_prvkey_from_hex(hexPrivKey, pubKey);
        fclose(fp1);
        fclose(fp2);
    }
    paillier_plaintext_t* m1, *m2;
    m1 = paillier_plaintext_from_ui(2);
    m2 = paillier_plaintext_from_ui(3);
    paillier_ciphertext_t* ctxt1;
    paillier_ciphertext_t* ctxt2;
    ctxt1 = paillier_enc(NULL, pubKey, m1, paillier_get_rand_devurandom);
    ctxt2 = paillier_enc(NULL, pubKey, m2, paillier_get_rand_devurandom);
    paillier_ciphertext_t* encryptedSum = paillier_create_enc_zero();
    // Sum the encrypted values by multiplying the ciphertexts
    paillier_mul(pubKey, encryptedSum, ctxt1, ctxt2);
    paillier_plaintext_t* dec;
    dec = paillier_dec(NULL, pubKey, secKey, encryptedSum);
    gmp_printf("Decrypted sum: %Zd\n", dec);
    return 0;
}

