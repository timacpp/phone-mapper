#ifndef MAPTEL_H
#define MAPTEL_H

#ifdef __cplusplus
#include <iostream>
#include <cstdio>

extern "C" {
    namespace jnp1 {
#else
#include <stdio.h>
#endif
        /* Maximum length of a telephone number. */
        const size_t TEL_NUM_MAX_LEN = 22;

        /* Creates a dictionary and returns its unique identifier */
        unsigned long maptel_create(void);

        /* Deletes a dictionary of specified identifier */
        void maptel_delete(unsigned long id);

        /* Inserts or overwrites number change history to a dictionary.*/
        void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst);

        /* Erases number change history from a dictionary */
        void maptel_erase(unsigned long id, char const *tel_src);

        /* Extracts last number of change history from a dictionary and writes to a tel_dst. */
        void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len);

#ifdef __cplusplus
    }
}
#endif

#endif // MAPTEL_H
