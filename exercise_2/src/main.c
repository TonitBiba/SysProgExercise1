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
#include "str_serialize.h"
#include "patient.h"

int main(int argc, char *argv [])
{
  applOption  aoObj;
  int         status = 0;
  char       *personal_number = NULL;
  char       *age = NULL;
  char       *name = NULL;
  char       *surname = NULL;
  char       *address = NULL;
  char       *test_date = NULL;
  Patient_t   patient;
  Patient_t   patient_read;

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

  if (aoObj.append == (char) OPT_SPECIFIED)
    {
      personal_number = Get_Attr("personal number", aoObj.nr_personal);

      name = Get_Attr("name", aoObj.name);

      surname = Get_Attr("surname", aoObj.surname);

      address = Get_Attr("address", aoObj.address);

      age = Get_Attr("age", aoObj.age);

      test_date = Get_Attr("test date", aoObj.test_date);

      if(Patient_init(personal_number, name, surname, age, address, test_date, &patient)==0){
          printf ("\nError while initilizing patient with data.");
          (void) opt_free (&aoObj);
          return -1;
      }

      printf("%s", patient.name.p_str);

      if(Patient_write(aoObj.fp, &patient) == 0){
        printf ("\nError writing the patient in file");
          (void) opt_free (&aoObj);
          return -1;
      }
    }

  if (aoObj.list == (char) OPT_SPECIFIED)
    {
      /* list all strings */
      printf ("\n\nList of tested patients: \n");
      int patientNo = 0;
          printHeader();

      do
        {
          patientNo++;
          status = Patient_read (aoObj.fp, &patient_read);
          switch (status)
          {
            case SER_ALLOC_ERROR:
              perror ("Error allocating memory");
              (void) opt_free (&aoObj);
              return -1;
            break;

            case 0:
            break;

            default:
              printf ("%d. \t%s \t\t%s \t\t%s \t\t%s \t%s \t%s\n", patientNo, patient_read.nr_personal.p_str, patient_read.name.p_str, patient_read.surname.p_str, patient_read.address.p_str, patient_read.age.p_str, patient_read.test_date.p_str);
              break;
            }
        } while (status >0);
    }

  (void) opt_free (&aoObj);
  
  printf ("\nThank you!\n");
   
  return 0;
}