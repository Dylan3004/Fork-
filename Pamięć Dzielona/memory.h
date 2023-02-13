#ifndef MEMORY_H
#define MEMORY_H

    int stworz_pamiec(const char *name);
    int otworz_pamiec(const char *name);
    int ustaw_dlogosc(int fd , off_t length);
    int zamknij_pamiec(int fd);
    int usun_pamiec(const char *name);
    void *zmapuj (int desc, size_t a);


#endif