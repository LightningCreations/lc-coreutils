//
// Created by chorm on 2020-07-06.
//

#ifndef LCNIX_SELECT_HASH_H
#define LCNIX_SELECT_HASH_H

#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern"C" {
#endif


void register_known_hash(const char *name, size_t outSz, void(*apply)(char[], FILE *));

void register_sha_hashes(void);

#ifdef __cplusplus
};
#endif

#endif //LCNIX_SELECT_HASH_H
