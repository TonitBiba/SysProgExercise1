/** 
 * Copyright (C) 2020 Tonit Biba All rights reserved
 * University of Prishtina, Prishtine, Kosove. tonit.biba@hotmail.com
 *
 * @file  str_serialize.c
 *
 * @brief Implements functions for the string file serialization. This fajlli is identicial with file that has been send by prof. Idriz Smajli. 
 * Credits to prof. Idriz Smajli
 * 
 * @author IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Sht 30 Maj 2020 09:52:49.PD CEST $
 */

#ifndef _STR_SERIALIZE_H
#define _STR_SERIALIZE_H 1

#include <stdio.h>

#define SER_EOF         -2
#define SER_ALLOC_ERROR -1
#define SER_INT_LEN      4

typedef struct _CString
{
  int   length;
  char *p_str;
} CString_t;

int str_len   (          /*@null@*/ const char      *      str);
int str_init  (          /*@null@*/ const char      *      str, CString_t *const c_str);
int str_write (FILE *fp, /*@null@*/ const CString_t *const c_str);
int str_read  (FILE *fp, /*@null@*/       CString_t *const c_str);

#endif /* _STR_SERIALIZE_H */

 
