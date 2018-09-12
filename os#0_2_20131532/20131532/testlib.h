#ifndef Header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "list.h"
#include "hash.h"

struct data_name{
	char name[40];
	struct list list;
};

typedef unsigned long elem_type;
struct bitmap
  {
    size_t bit_cnt;     /* Number of bits. */
    elem_type *bits;    /* Elements that represent bits. */
  };

struct bit_name{
	char name[40];
	struct bitmap * bitmap;
};
struct hash_name{
	char name[40];
	struct hash hash;
};

struct data_name list_name[10];
struct bit_name bit_name[10];
struct hash_name hash_name[10];


int list_num=0;
int bit_num=0;
int hash_num=0;
struct list* find_list_arg(char * str);
struct bitmap* find_bit_arg(char *str);
struct hash * find_hash_arg(char * str);
void active(char** input);
#endif
