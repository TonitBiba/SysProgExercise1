/** 
 * Copyright (C) 2020 Tonit Biba All rights reserved
 * University of Prishtina, Prishtine, Kosove. tonit.biba@hotmail.com
 *
 * @file  main.c
 *
 * @brief Implements the main function 
 * 
 * @author Tonit Biba (tonit.biba@hotmail.com)
 * @date   $Date: Sht 30 Maj 2020 09:52:49.PD CEST $
 */

#define _POSIX_SOURCE

#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "option.h"
#include "str_serialize.h"
#include "patient.h"

int main(int argc, char *argv [])
{
  Option_t    option;
  int         status = 0;
  char       *personal_number = NULL;
  char       *age = NULL;
  char       *name = NULL;
  char       *surname = NULL;
  char       *address = NULL;
  char       *test_date = NULL;
  Patient_t   patient_write;
  Patient_t   patient_read;

  option_init (&option);
  
  if ((char) option_proc (argc, argv, &option) == -1)
    {
      option_free (&option);
      return EXIT_FAILURE;
    }

  if ((option.fp = fopen (option.f_name, "a+")) == NULL)
    {
      printf ("\nError opening the file: '%s' [Error string: '%s']",
              option.f_name, strerror (errno));
      option_free (&option);
      return -1;
    }
  

  if (option.append == 1)
    {
      personal_number = Get_Attr("personal number", option.nr_personal);

      name = Get_Attr("name", option.name);

      surname = Get_Attr("surname", option.surname);

      address = Get_Attr("address", option.address);

      age = Get_Attr("age", option.age);

      test_date = Get_Attr("test date", option.test_date);

      if(Patient_init(personal_number, name, surname, age, address, test_date, &patient_write)==0){
          printf ("\nError while initilizing patient with data.\n");
          (void) option_free (&option);
          return -1;
      }

      if(Patient_write(option.fp, &patient_write) == 0){
        printf ("\nError writing the patient in file");
          (void) option_free (&option);
          return -1;
      }
      
      Patient_free(&patient_write);
    }

  if (option.list == 1)
    {
      int patientNo = 0;
          printHeader();

      do
        {
          patientNo++;
          status = Patient_read (option.fp, &patient_read);
          switch (status)
          {
            case -1:
              perror ("Error allocating memory");
              (void) option_free (&option);
              return -1;
            break;

            case 0:
            break;

            default:
              printf ("* %d.  |%-20s|%-20s|%-20s|%-20s|%-10s|%s *\n", patientNo, patient_read.nr_personal.p_str, patient_read.name.p_str, patient_read.surname.p_str, patient_read.address.p_str, patient_read.age.p_str, patient_read.test_date.p_str);
              break;
            }
            Patient_free(&patient_read);
        } while (status >0);
        printFooter(patientNo-1);
    }

if(option.nr_personal == NULL){
  free(personal_number);
}

if(option.name == NULL){
  free(name);
}

if(option.surname == NULL){
  free(surname);
}

if(option.age == NULL){
  free(age);
}

if(option.address == NULL){
  free(address);
}

if(option.test_date == NULL){
  free(test_date);
}
  (void) option_free (&option);

  printf ("\nThank you!\nTonit Biba\n");
   
  return 0;
}