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

#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "str_serialize.h"

/***************************************************************************//** 
 * @brief Returns the number of characters in a given string
 *
 * @param[in] str - input string
 *
 * @retval number of characters
 ******************************************************************************/
int str_len (const char *str)
{
  register int count  = 0;

  if (str != NULL)
    {
      while (*str++ != '\0')
        {
          count++;
        }
    }

  return count;
}

/***************************************************************************//** 
 * @brief Initialize a CString_t object
 *
 * @param[in,out] fp    - file pointer
 * @param[in]     c_str - the input CString_t
 *
 * @retval 0  in case an error was occured
 * @retval >0 number of bytes that have been allocated for the string object
 ******************************************************************************/
int str_init (const char *str, CString_t *const c_str)
{
  char *l_ptr = NULL;
  
  if (c_str == NULL || str == NULL)
    {
      return 0;
    }

  c_str->length = str_len (str);
  l_ptr         = (char *) malloc (c_str->length +1);

  if (l_ptr == NULL)
    {
      perror ("Memory allocation failed");
      return 0;
    }
  
  c_str->p_str = l_ptr;

  while (*str != '\0')
    {
      *l_ptr++ = *str++;
    }

  l_ptr = '\0';

  return c_str->length;
}

/***************************************************************************//** 
 * @brief Writes an input string into the file 
 *
 * First the four (4) bytes will be written indicating the length of the
 * string to be written, and then the string itself will be written.
 *
 * @param[in,out] fp    - file pointer
 * @param[in]     c_str - the input CString_t
 *
 * @retval 0  in case an error was occured
 * @retval >0 number of bytes written in the file
 ******************************************************************************/
int str_write (FILE *fp, const CString_t *const c_str)
{
  int status = 0;
  int length = 0;

  if (c_str == NULL || c_str->p_str == NULL)
    {
      return status;
    }

  
  length = htonl(c_str->length);

  status = (int) fwrite ((const void *) &length, (size_t) 1, 
                         (size_t) SER_INT_LEN, fp);

  if (status == 0)
    {
       printf ("\nError writing length of string '%s' to the file", c_str->p_str);
       return status;
    }

  status = (int) fwrite ((const void *) c_str->p_str, (size_t) 1, 
                         (size_t) c_str->length, fp);

  if (status == 0)
    {
       printf ("\nError writing string '%s' to the file", c_str->p_str);
    }

  return status;
}

/***************************************************************************//** 
 * @brief Reads an string from the file 
 *
 * First the four (4) bytes will be read, which indicate the length of the
 * string to be read, and then the string itself will be read.
 *
 * @param[in,out] fp  - file pointer
 * @param[out]    dst - pointer to the newly allocated string 
 *
 * @retval 0             in case an error was occured
 * @retval SER_MEM_ERROR error allocating memory was occured
 * @retval SER_EOF       end of file is reached
 * @retval >0            number of bytes read out from the file
 ******************************************************************************/
int str_read (FILE *fp, /*@null@*/ CString_t *const dst)
{
  int   s_len  = 0;
  int   status = 0;
  char *ptr    = NULL;

  if (fp == NULL || dst == NULL) 
    {
      return status;
    }

  status = fread ( (void *) &s_len, (size_t) 1,
                   (size_t) SER_INT_LEN, fp);

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
  
  dst->length = ntohl(s_len);

  ptr = (char *) malloc ((size_t) dst->length + 1);
  
  if (ptr == NULL)
    {
      printf ("\nError allocating memory");
      return SER_ALLOC_ERROR;
    }
  
  status = fread ( (void *) ptr, (size_t) 1,
                   (size_t) dst->length, fp);

  ptr [dst->length] = '\0';
  
  if (status == 0)
    {
      printf ("\nError reading from file");
    }
  
  dst->length = s_len;
  dst->p_str  = ptr;
  return status;
}