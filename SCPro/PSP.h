#ifndef PSP_H
#define PSP_H
#ifndef P_H
#define P_H
#include "paillier.h"
#endif
int getrnd();
paillier_ciphertext_t* AddRnd(paillier_ciphertext_t *d_c, char *hexPubKey, int rnd);
#endif // PSP_H
