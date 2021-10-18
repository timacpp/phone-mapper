//
// Created by Katarzyna on 18/10/2021.
//

#ifndef PHONE_MAPPER_MAPTEL_H
#define PHONE_MAPPER_MAPTEL_H


#include <cstdio>

#ifdef __cplusplus
    extern "C" {
#endif

    // #define size_t jnp1::TEL_NUM_MAX_LEN 22

    // Kasia
    // Tworzy słownik i zwraca liczbę naturalną będącą jego identyfikatorem.
    unsigned long maptel_create(void);

    // Tima
    // Usuwa słownik o identyfikatorze id.
    void maptel_delete(unsigned long id);

    // Kasia
    // Wstawia do słownika o identyfikatorze id informację o zmianie numeru
    // tel_src na numer tel_dst. Nadpisuje ewentualną istniejącą informację.
    void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst);

    // Tima
    // Jeśli w słowniku o identyfikatorze id jest informacja o zmianie numeru
    // tel_src, to ją usuwa. W przeciwnym przypadku nic nie robi.
    void maptel_erase(unsigned long id, char const *tel_src);

    // Tima
    // Sprawdza, czy w słowniku o identyfikatorze id jest zapisana zmiana numeru
    // tel_src. Podąża ciągiem kolejnych zmian. Zapisuje zmieniony numer w tel_dst.
    // Jeśli nie ma zmiany numeru lub zmiany tworzą cykl, to zapisuje w tel_dst
    // numer tel_src. Wartość len to rozmiar przydzielonej pamięci wskazywanej
    // przez tel_dst.
    void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len);


#ifdef __cplusplus
    }
#endif

#endif //PHONE_MAPPER_MAPTEL_H
