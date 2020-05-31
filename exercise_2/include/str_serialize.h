/** 
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  str_serialize.h
 *
 * @brief Implements functions for the string file serialization 
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 20, 15:27:59 WEST 2019 $
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

 
