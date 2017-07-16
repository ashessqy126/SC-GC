#ifndef CLIENT_H
#define CLIENT_H
#ifndef P_H
#define P_H
#include "paillier.h"
#endif
paillier_ciphertext_t* EncDistance(int w_x, int w_y, int t_x, int t_y, char *hexPubKey);
#endif
