#ifndef LIB_1_H
#define LIB_1_H


sem_t *otworz_semafor(const char* name);
sem_t *stworz_semafor(const char* name);
void zamknij_semafor(sem_t* sem_t);
void wartosc_semafora(sem_t* sem, int *sval);
void upusc_semafor(sem_t *sem);
void podnies_semafor(sem_t *sem);
void usun_semafor(const char *name);
int otworz_pamiec(const char *name);
int stworz_pamiec(const char *name);
int ustaw_dlogosc(int fd , off_t length);
int zamknij_pamiec(int fd);
int usun_pamiec(const char *name);
void *zmapuj (int desc, size_t a);

#endif
