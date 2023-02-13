#ifndef BIBLIOTEKA_H
#define BIBLIOTEKA_H

sem_t *stworz_semafor(const char* name);
sem_t *otworz_semafor(const char* name);
void zamknij_semafor(sem_t* sem_t);
void wartosc_semafora(sem_t* sem, int *sval);
void upusc_semafor(sem_t *sem);
void podnies_semafor(sem_t *sem);
void usun_semafor(const char *name);

#endif
