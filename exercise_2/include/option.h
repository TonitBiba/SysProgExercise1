/** 
 * Copyright (C) 2020 Tonit Biba All rights reserved
 * University of Prishtina, Prishtine, Kosove. tonit.biba@hotmail.com
 *
 * @file  option.h
 *
 * @brief Implements functions for the patient with Covid-19 
 * 
 * @author Tonit Biba (tonit.biba@hotmail.com)
 * @date   $Date: Sht 30 Maj 2020 09:52:49.PD CEST $
 */

#ifndef _OPTION_H
#define _OPTION_H 1_

#include <stdio.h>

#define OPT_PATTERN      "f:ahlp:n:s:m:c:d:"

/* define application structure */
typedef struct _Option
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
  
} Option_t;

/* public interface functions */
void option_init     (/*@out@*/Option_t *aoObj);
void option_free     (/*@out@*/Option_t *aoObj);
int  option_proc     (         int         argc, char *argv[], /*@out@*/Option_t *aoObj);
void option_usage    (   const char       *name);

#endif /* _OPTION_H */