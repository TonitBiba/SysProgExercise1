/**
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  main.c
 *
 * @brief Implements the main function
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 19, 15:39:59 WEST 2019 $
 */

#define _POSIX_SOURCE

#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "opt.h"

#define BUFF_LEN (1024)

int main(int argc, char *argv [])
{
  char        buff [BUFF_LEN];
  applOption  aoObj;
  /*int         status = 0;
  int         count  = 1;
  char       *w_str  = NULL; 
*/
  opt_init (&aoObj);

  if ((char) opt_proc (argc, argv, &aoObj) == OPT_PROC_ERROR)
    {
      opt_free (&aoObj);
      return EXIT_FAILURE;
    }

  printf ("\nThe file '%s' is opening ... ", aoObj.f_name);
  
  if ((aoObj.fp = fopen (aoObj.f_name, "a+")) == NULL)
  {
      printf ("\nError opening the file: '%s' [Error string: '%s']",
              aoObj.f_name, strerror (errno));
      opt_free (&aoObj);
      return -1;
    }

   printf (" done");

    return 0;
}
