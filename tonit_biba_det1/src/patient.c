/** 
 * Copyright (C) 2020 Tonit Biba All rights reserved
 * University of Prishtina, Prishtine, Kosove. tonit.biba@hotmail.com
 *
 * @file  patient.c
 *
 * @brief Implements functions for the patients tested with Covid-19 
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
#define BUFF_LEN (1024)


/***************************************************************************//** 
 * @brief Initialize the data structure which describes a Patient_t object
 *
 * This function initilizes the data structure that describes the specified 
 * patient structure
 * 
 * @param[in] nr_personal - char array of personal number
 * @param[in] name - char array of name
 * @param[in] surname - char array of surname
 * @param[in] age - char array of age
 * @param[in] address - char array of address
 * @param[in] test_date - char array of test_date
 * @param[in,out] fp    - file pointer in which will be written patient data
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
      perror("Initialization of nr_personal attribute failed!");
      Patient_free(patient);
      return 0;
  }

  if(str_init (name, &patient->name) == 0)
  {
      perror("Initialization of name attribute failed!");
      Patient_free(patient);
      return 0;
  }

  if(str_init (surname, &patient->surname) == 0)
  {
      perror("Initialization of surname attribute failed");
      Patient_free(patient);
      return 0;
  }

  if(str_init (address, &patient->address) == 0)
  {
      perror("Initialization of address attribute failed");
      Patient_free(patient);
      return 0;
  }

  if(str_init (age, &patient->age) == 0)
  {
      perror("Initialization of age attribute failed");
      Patient_free(patient);
      return 0;
  }

  if(str_init (test_date, &patient->test_date) == 0)
  {
      perror("Initialization of test date attribute failed");
      Patient_free(patient);
      return 0;
  }
    return 1;
}

/***************************************************************************//** 
 * @brief Release an object of type Patient_t
 *
 * @param[in,out] patient - the object to be released
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

/***************************************************************************//** 
 * @brief Writes the data structure which describes a Patient_t object
 *
 * This function writes the data structure that describes the specified 
 * patient structure
 * @param[in,out] fp - file pointer in which will be written patient data 
 * @param[in,out] patient - patient pointer which will be written 
 *
 * @retval 0  in case an error was occured.
 * @retval 1 if patient is written successfully.
 ******************************************************************************/
int Patient_write (FILE *fp, /*@null@*/ const Patient_t *const patient)
{
  int status = 0;

  if (patient == NULL)
    {
      return 0;
    }

  status = Write_Attr(fp, &patient->nr_personal);

  if (status == 0)
  {
    printf ("\nError writing personal number to the file");
    return 0;
  }

  status = Write_Attr(fp, &patient->name);

  if (status == 0)
  {
    printf ("\nError writing name to the file");
    return 0;
  }

  status = Write_Attr(fp, &patient->surname);

  if (status == 0)
  {
    printf ("\nError writing surname to the file");
    return 0;
  }

  status = Write_Attr(fp, &patient->address);

  if (status == 0)
  {
    printf ("\nError writing address to the file");
    return 0;
  }

  status = Write_Attr(fp, &patient->age);
  
  if (status == 0)
  {
    printf ("\nError writing age to the file");
    return 0;
  }

  status = Write_Attr(fp, &patient->test_date);

  if (status == 0)
  {
    printf ("\nError writing test date to the file");
    return 0;
  }
  return 1;
}

/***************************************************************************//** 
 * @brief Reades the data structure which describes a Patient_t object
 *
 * This function is used to read a line of file in format of Patient_t structure.
 * 
 * @param[in,out] fp - file pointer in which will be read patient data 
 * @param[in,out] patient - patient pointer which will be written 
 *
 * @retval -1 in case of memory allocation fail
 * @retval 0  in case an error was occured.
 * @retval 1 if patient is initialized successfully.
 * @retval 2 if is reached the end of file.
 ******************************************************************************/
int Patient_read  (FILE *fp, /*@null@*/ Patient_t *const patient)
{
  int   s_len  = 0;
  int   status = 0;

  if (fp == NULL || patient == NULL) 
    {
      return 0;
    }
  /*Personal number*/
  status = fread ( (void *) &s_len, (size_t) 1, (size_t) SER_INT_LEN, fp);
  
  patient->nr_personal.length = ntohl(s_len);

  patient->nr_personal.p_str = (char *) malloc ((size_t) patient->nr_personal.length + 1);
  
  if (patient->nr_personal.p_str == NULL)
    {
      printf ("\nError allocating memory");
      return -1;
    }
  
  status = fread ((void *) patient->nr_personal.p_str, (size_t) 1, (size_t) patient->nr_personal.length, fp);

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
      return -1;
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
      return -1;
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
      return -1;
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
      return -1;
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
      return -1;
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
          return 2;
        }
      else
        {
          printf ("\nError reading from file");
          return status;
        }
    }

  return 1;
}

/***************************************************************************//** 
 * @brief Writes the header of table for patient list  
 *
 * This functions writes the header of table in which will be displayed patients data.
 *
 * @retval void
 ******************************************************************************/
void printHeader()
{
  printf ("\n******************************************************************************************************************\n");
  printf ("*%-35s List of patients tested with Covid-19. %38s \n", "", "*");
  printf ("******************************************************************************************************************\n");
  printf ("* nr. |%-20s|%-20s|%-20s|%-20s|%-10s|%-20s\n", "Personal number", "Name", "Surname", "Address", "Age", "Test date  *");
}

/***************************************************************************//** 
 * @brief Writes the footer of table for patient list  
 *
 * This functions writes the footer of table in which will be displayed patients data.
 * @param[in] total - total number of patient in file.
 * @retval void
 ******************************************************************************/
void printFooter(const int total)
{
  printf ("******************************************************************************************************************\n");
  printf ("*%-35s Total number of patient tested with Covid-19 is %d. %26s \n", "", total, "*");
  printf ("******************************************************************************************************************\n");
}

/***************************************************************************//** 
 * @brief Initialize attribute of Patient_t structure
 *
 * This function initilizes the attribute of Patient_t structure with data from argument 
 * or from user input if it is not specified.
 * 
 * @param[in] attr_name - char array attribute name.
 * @param[in] arg - char array of argument if it is specified by user.
 *
 * @retval NULL in case of error.
 * @retval arg  in case of specified by user argument
 * @retval char* in case if it has been read by user input.
 ******************************************************************************/
char *Get_Attr(const char *attr_name, char *arg)
{
  if(arg != NULL){
    return arg;
  }
        
  char buff [BUFF_LEN];

  printf("\nType the patient %s: ", attr_name);
  fgets (&buff[0], BUFF_LEN, stdin);
  buff[strcspn(buff, "\n")] = '\0';
  char* tmp = malloc(strlen(buff) + 1); 
  if (tmp == NULL)
  {
    return NULL;
  }
  strcpy(tmp, buff);
  free(tmp);
  return tmp;
}

/***************************************************************************//** 
 * @brief Initialize attribute of Patient_t structure
 *
 * This function initilizes the attribute of Patient_t structure with data from argument 
 * or from user input if it is not specified.
 * 
 * @param[in] fp - fp pointer.
 * @param[in] arg - CString_t attribute which will be written to file.
 *
 * @retval number of files that are written in file.
 * @retval 0 in case of error.
 ******************************************************************************/
int Write_Attr(FILE *fp, /*@null@*/ const CString_t *const arg)
{
  int status = 0;
  int length = 0;

  length = htonl(arg->length);

  status = (int) fwrite ((const void *) &length, (size_t) 1, (size_t) SER_INT_LEN, fp);

  status = (int) fwrite ((const void *) arg->p_str, (size_t) 1, (size_t) arg->length, fp);

  return status;
}

/***************************************************************************//** 
 * @brief Release an char attribute
 *
 * @param[in] char - the char pointer to be released
 *
 * @retval void
 ******************************************************************************/
void Attribute_free(char *const attr)
{
    if(attr != NULL)
    {
        free(attr);
    }
}