#include "PSP.h"
#include <time.h>
#include <stdlib.h>
int getrnd(){
    srand(time(NULL));
    int rnd = rand()%10000000;
    return rnd;
}

paillier_ciphertext_t* AddRnd(paillier_ciphertext_t *d_c, char *hexPubKey, int rnd){
    paillier_pubkey_t* pubKey;
    pubKey = paillier_pubkey_from_hex(hexPubKey);
    paillier_plaintext_t* m;
    m = paillier_plaintext_from_ui(rnd);
    paillier_ciphertext_t* ctxt;
    ctxt = paillier_enc(NULL, pubKey, m, paillier_get_rand_devurandom);
    paillier_ciphertext_t* encryptedSum = paillier_create_enc_zero();
    // Sum the encrypted values by multiplying the ciphertexts
    paillier_mul(pubKey, encryptedSum, ctxt, d_c);
    return encryptedSum;
}
