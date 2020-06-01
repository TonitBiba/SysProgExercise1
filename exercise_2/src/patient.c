/** 
 * Copyright (C) 2020 Tonit Biba All rights reserved
 * University of Prishtina, Prishtine, Kosove. tonit.biba@hotmail.com
 *
 * @file  patient.c
 *
 * @brief Implements functions for the patient with Covid-19 
 * 
 * @author Tonit Biba (tonit.biba@hotmail.com)
 * @date   $Date: Sht 30 Maj 2020 09:52:49.PD CEST $
 */

#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#include "str_serialize.h"
#include "patient.h"


/***************************************************************************//** 
 * @brief Initialize a Person_t object
 *
 * @param[in,out] fp    - file pointer TODO documentation
 * @param[in]     c_str - the input CString_t
 *
 * @retval 0  in case an error was occured.
 * @retval 1 if patient is initialized successfully.
 ******************************************************************************/
int Patient_init(const char *nr_personal, const char *name, const char *surname, const char *age, const char *address, const char *test_date, Patient_t *const patient)
{
    if(nr_personal==0 || name == NULL || surname == NULL || age == NULL || address == NULL || test_date == NULL)
    {
        return 0;
    }

    patient->nr_personal.p_str = NULL;
    patient->name.p_str = NULL;
    patient->surname.p_str = NULL;
    patient->age.p_str = NULL;
    patient->address.p_str = NULL;
    patient->test_date.p_str = NULL;

  if(str_init (nr_personal, &patient->nr_personal) == 0)
  {
      perror("Initianization of nr_personal attribute failed!");
      Patient_free(patient);
      return 0;
  }

  if(str_init (name, &patient->name) == 0)
  {
      perror("Initianization of name attribute failed!");
      Patient_free(patient);
      return 0;
  }

  if(str_init (surname, &patient->surname) == 0)
  {
      perror("Initianization of surname attribute failed");
      Patient_free(patient);
      return 0;
  }

  if(str_init (address, &patient->address) == 0)
  {
      perror("Initianization of address attribute failed");
      Patient_free(patient);
      return 0;
  }

  if(str_init (age, &patient->age) == 0)
  {
      perror("Initianization of age attribute failed");
      Patient_free(patient);
      return 0;
  }

  if(str_init (test_date, &patient->test_date) == 0)
  {
      perror("Initianization of test date attribute failed");
      Patient_free(patient);
      return 0;
  }

    return 1;
}

/***************************************************************************//** 
 * @brief Release an object of type Person_t
 *
 * @param[in,out]     Person_t person - the object to be released
 *
 *
 * @retval void
 ******************************************************************************/
void Patient_free(Patient_t *const patient)
{
    if(patient->nr_personal.p_str != NULL)
    {
        free(patient->nr_personal.p_str);
        patient->nr_personal.p_str = NULL;
    }

    if(patient->name.p_str != NULL)
    {
        free(patient->name.p_str);
        patient->name.p_str = NULL;
    }

    if(patient->surname.p_str != NULL)
    {
        free(patient->surname.p_str);
        patient->surname.p_str = NULL;
    }

    if(patient->address.p_str != NULL)
    {
        free(patient->address.p_str);
        patient->address.p_str = NULL;
    }

    if(patient->age.p_str != NULL)
    {
        free(patient->age.p_str);
        patient->age.p_str = NULL;
    }

    if(patient->test_date.p_str != NULL)
    {
        free(patient->test_date.p_str);
        patient->test_date.p_str = NULL;
    }
}

int Patient_write (FILE *fp, /*@null@*/ const Patient_t *const patient)
{
  int status = 0;
  int length = 0;

  if (patient == NULL)
    {
      return status;
    }

  length = htonl(patient->nr_personal.length);

  status = (int) fwrite ((const void *) &length, (size_t) 1, (size_t) SER_INT_LEN, fp);

  status = (int) fwrite ((const void *) patient->nr_personal.p_str, (size_t) 1, (size_t) patient->nr_personal.length, fp);

  length = htonl(patient->name.length);

  status = (int) fwrite ((const void *) &length, (size_t) 1, (size_t) SER_INT_LEN, fp);

  status = (int) fwrite ((const void *) patient->name.p_str, (size_t) 1, (size_t) patient->name.length, fp);

  length = htonl(patient->surname.length);

  status = (int) fwrite ((const void *) &length, (size_t) 1, (size_t) SER_INT_LEN, fp);

  status = (int) fwrite ((const void *) patient->surname.p_str, (size_t) 1, (size_t) patient->surname.length, fp);

  length = htonl(patient->address.length);

  status = (int) fwrite ((const void *) &length, (size_t) 1, (size_t) SER_INT_LEN, fp);

  status = (int) fwrite ((const void *) patient->address.p_str, (size_t) 1, (size_t) patient->address.length, fp);

  length = htonl(patient->age.length);

  status = (int) fwrite ((const void *) &length, (size_t) 1, (size_t) SER_INT_LEN, fp);

  status = (int) fwrite ((const void *) patient->age.p_str, (size_t) 1, (size_t) patient->age.length, fp);

  length = htonl(patient->test_date.length);

  status = (int) fwrite ((const void *) &length, (size_t) 1, (size_t) SER_INT_LEN, fp);

  status = (int) fwrite ((const void *) patient->test_date.p_str, (size_t) 1, (size_t) patient->test_date.length, fp);

  if (status == 0)
    {
       printf ("\nError writing person name to the file");
    }

  return status;
}

int Patient_read  (FILE *fp, /*@null@*/ Patient_t *const patient)
{
  int   s_len  = 0;
  int   status = 0;

  if (fp == NULL || patient == NULL) 
    {
      return status;
    }
/*Personal number*/
  status = fread ( (void *) &s_len, (size_t) 1, (size_t) SER_INT_LEN, fp);
  
  patient->nr_personal.length = ntohl(s_len);

  patient->nr_personal.p_str = (char *) malloc ((size_t) patient->nr_personal.length + 1);
  
  if (patient->nr_personal.p_str == NULL)
    {
      printf ("\nError allocating memory");
      return SER_ALLOC_ERROR;
    }
  
  status = fread ( (void *) patient->nr_personal.p_str, (size_t) 1, (size_t) patient->nr_personal.length, fp);

  patient->nr_personal.p_str [patient->nr_personal.length] = '\0';

  if (status == 0)
    {
      return status;
    }

  /*Name*/
  status = fread ( (void *) &s_len, (size_t) 1, (size_t) SER_INT_LEN, fp);

  patient->name.length = ntohl(s_len);

  patient->name.p_str = (char *) malloc ((size_t) patient->name.length + 1);
  
  if (patient->name.p_str == NULL)
    {
      printf ("\nError allocating memory");
      return SER_ALLOC_ERROR;
    }
  
  status = fread ( (void *) patient->name.p_str, (size_t) 1, (size_t) patient->name.length, fp);

  patient->name.p_str [patient->name.length] = '\0';
  
  if (status == 0)
    {
      printf ("\nError reading from file");
    }

/*surname*/
  status = fread ( (void *) &s_len, (size_t) 1, (size_t) SER_INT_LEN, fp);
  
  patient->surname.length = ntohl(s_len);

  patient->surname.p_str = (char *) malloc ((size_t) patient->surname.length + 1);
  
  if (patient->surname.p_str == NULL)
    {
      printf ("\nError allocating memory");
      return SER_ALLOC_ERROR;
    }
  
  status = fread ( (void *) patient->surname.p_str, (size_t) 1, (size_t) patient->surname.length, fp);

  patient->surname.p_str [patient->surname.length] = '\0';
  
  if (status == 0)
    {
      printf ("\nError reading from file");
    }

/*address*/
  status = fread ( (void *) &s_len, (size_t) 1, (size_t) SER_INT_LEN, fp);
  
  patient->address.length = ntohl(s_len);

  patient->address.p_str = (char *) malloc ((size_t) patient->address.length + 1);
  
  if (patient->address.p_str == NULL)
    {
      printf ("\nError allocating memory");
      return SER_ALLOC_ERROR;
    }
  
  status = fread ( (void *) patient->address.p_str, (size_t) 1, (size_t) patient->address.length, fp);

  patient->address.p_str [patient->address.length] = '\0';
  
  if (status == 0)
    {
      printf ("\nError reading from file");
    }

/*age*/
  status = fread ( (void *) &s_len, (size_t) 1, (size_t) SER_INT_LEN, fp);
  
  patient->age.length = ntohl(s_len);

  patient->age.p_str = (char *) malloc ((size_t) patient->age.length + 1);
  
  if (patient->age.p_str == NULL)
    {
      printf ("\nError allocating memory");
      return SER_ALLOC_ERROR;
    }
  
  status = fread ( (void *) patient->age.p_str, (size_t) 1, (size_t) patient->age.length, fp);

  patient->age.p_str [patient->age.length] = '\0';
  
  if (status == 0)
    {
      printf ("\nError reading from file");
    }

/*test date*/
  status = fread ( (void *) &s_len, (size_t) 1, (size_t) SER_INT_LEN, fp);
  
  patient->test_date.length = ntohl(s_len);

  patient->test_date.p_str = (char *) malloc ((size_t) patient->test_date.length + 1);
  
  if (patient->test_date.p_str == NULL)
    {
      printf ("\nError allocating memory");
      return SER_ALLOC_ERROR;
    }
  
  status = fread ( (void *) patient->test_date.p_str, (size_t) 1, (size_t) patient->test_date.length, fp);

  patient->test_date.p_str [patient->test_date.length] = '\0';
  
  if (status == 0)
    {
      printf ("\nError reading from file");
    }

 if (status == 0)
    {
      if (feof (fp) != 0)
        {
          return SER_EOF;
        }
      else
        {
          printf ("\nError reading from file");
          return status;
        }
    }

  return status;
}