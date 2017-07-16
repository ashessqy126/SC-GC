#ifndef SCSERVER_H
#define SCSERVER_H
#ifndef P_H
#define P_H
#include "paillier.h"
#endif
void keygen(char *PubKey, char *Privkey, const long n);
void SCSDec(paillier_ciphertext_t* c, char *hexPrvKey, char *hexPubKey, char *dstr);
int MinGC(char *rndp, char *distancep, int num);
int check_hsb(int num, char *buffer);
#endif // SCSERVER_H
