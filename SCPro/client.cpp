#include "client.h"

paillier_ciphertext_t* EncDistance(int w_x, int w_y, int t_x, int t_y, char *hexPubKey){
    w_x = w_x / 10;
    w_y = w_y / 10;
    t_x = t_x / 10;
    t_y = t_y / 10;
    int d = (w_x - t_x) * (w_x - t_x) + (w_y - t_y) * (w_y - t_y);
    const long n = 1024;
    //generate keys from hex
    paillier_pubkey_t* pubKey;
    pubKey = paillier_pubkey_from_hex(hexPubKey);
    paillier_plaintext_t* m;
    m = paillier_plaintext_from_ui(d);
    paillier_ciphertext_t* ctxt;
    ctxt = paillier_enc(NULL, pubKey, m, paillier_get_rand_devurandom);
    return ctxt;
}
