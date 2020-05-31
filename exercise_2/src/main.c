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

#define BUFF_LEN (1024)

int main(int argc, char *argv [])
{
  char        buff [BUFF_LEN];
  applOption  aoObj;
  int         status = 0;
  char       *personal_number;
  int         age = 0;
  char       *name;
  char       *surname;
  char       *address;
  char       *test_date;
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
      if(aoObj.nr_personal == -1){
        printf("\nType the patient personal number: ");
        fgets (&buff[0], BUFF_LEN, stdin);
        buff[strcspn(buff, "\n")] = '\0';
        char* tmp = malloc(strlen(buff) + 1); 
        if (tmp == NULL)
        {
          return -1;
        }
        strcpy(tmp, buff);
        personal_number = tmp;
      }
      
      if(aoObj.name == NULL){
        printf("\nType the patient name: ");
        fgets (&buff[0], BUFF_LEN, stdin);
        buff[strcspn(buff, "\n")] = '\0';
        char* tmp = malloc(strlen(buff) + 1); 
        if (tmp == NULL)
        {
          return -1;
        }
        strcpy(tmp, buff);
        name = tmp;
      }
    
     if(aoObj.surname == NULL){
        printf("\nType the patient surname: ");
        fgets (&buff[0], BUFF_LEN, stdin);
        buff[strcspn(buff, "\n")] = '\0';
        char* tmp = malloc(strlen(buff) + 1); 
        if (tmp == NULL)
        {
          return -1;
        }
        strcpy(tmp, buff);
        surname = tmp;
      }

      if(aoObj.address == NULL){
        printf("\nType the patient address: ");
        fgets (&buff[0], BUFF_LEN, stdin);
        buff[strcspn(buff, "\n")] = '\0';
        char* tmp = malloc(strlen(buff) + 1); 
        if (tmp == NULL)
        {
          return -1;
        }
        strcpy(tmp, buff);
        address = tmp;
      }

      if(aoObj.age == -1){
        printf("\nType the patient age: ");
        fgets (&buff[0], BUFF_LEN, stdin);
        buff[strcspn(buff, "\n")] = '\0';
        char* tmp = malloc(strlen(buff) + 1); 
        if (tmp == NULL)
        {
          return -1;
        }
        strcpy(tmp, buff);
        age = atoi(tmp);
        printf("Mosha :%d", age);
      }

      if(aoObj.test_date == NULL){
        printf("\nType the patient test date for Covid: ");
        fgets (&buff[0], BUFF_LEN, stdin);
        buff[strcspn(buff, "\n")] = '\0';
        char* tmp = malloc(strlen(buff) + 1); 
        if (tmp == NULL)
        {
          return -1;
        }
        strcpy(tmp, buff);
        test_date = tmp;
      } 


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

      /*printf("\n%s\n", &patient->name.p_str);

      if (str_write (aoObj.fp, &cw_str) == 0)
        {
          printf ("\nError writing the string '%s' to the file", w_str);
          (void) opt_free (&aoObj);
          return -1;cr_str
    }*/
    }

  if (aoObj.list == (char) OPT_SPECIFIED)
    {
      /* list all strings */
      printf ("\n\nThe content of the file: \n");
      do
        {
          status = Patient_read (aoObj.fp, &patient_read);

          switch (status)
          {
            case SER_ALLOC_ERROR:
              perror ("Error allocating memory");
              (void) opt_free (&aoObj);
              return -1;
            break;

            default:
              printf ("\t%s", patient.nr_personal.p_str);
              break;
            }
        } while (status >0);
    }

  /* release all resources */ 
  (void) opt_free (&aoObj);
  
  printf ("\nThank you!\n");
   
  return 0;
}