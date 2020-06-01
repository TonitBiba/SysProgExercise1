/** 
 * Copyright (C) 2020 Tonit Biba All rights reserved
 * University of Prishtina, Prishtine, Kosove. tonit.biba@hotmail.com
 *
 * @file  opt.h
 *
 * @brief Implements functions for the patient with Covid-19 
 * 
 * @author Tonit Biba (tonit.biba@hotmail.com)
 * @date   $Date: Sht 30 Maj 2020 09:52:49.PD CEST $
 */

#ifndef _OPT_H
#define _OPT_H 1_

#include <stdio.h>

/* defines different option macros */
#define OPT_FILE         (char) 0x01
#define OPT_APPEND       (char) 0x02
#define OPT_LIST         (char) 0x04
#define OPT_MAX_NUM      (char) 0x04

/* defines option's pattern */
#define OPT_PATTERN      "f:ahlp:n:s:m:c:d:"

/* define OPTION STATUS */
#define OPT_SPECIFIED    (char) 0x01
#define OPT_NOTSPECIFIED (char) 0x02

/* define the processing status of the passed options and arguments */
#define OPT_SUCCESS      (char) 0x01
#define OPT_PROC_ERROR   (char) 0x02
#define OPT_MALLOCERROR  (char) 0x04
#define OPT_NULLPOINTER  (char) 0x08

/* define application structure */
typedef struct _applOption
{
  char  append;
  char  list;
  char  *nr_personal;
  char  *name;
  char  *surname;
  char  *age;
  char  *address;
  char  *test_date;
  char *f_name;
  FILE *fp;
  
} applOption;

/* public interface functions */
void opt_init     (/*@out@*/applOption *aoObj);
void opt_free     (/*@out@*/applOption *aoObj);
int  opt_proc     (         int         argc, char *argv[], /*@out@*/applOption *aoObj);
int  opt_strclone (/*@out@*/char      **dest, const char *src);
void opt_usage    (   const char       *name);

#endif /* _OPT_H */