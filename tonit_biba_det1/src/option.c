/** 
 * Copyright (C) 2020 Tonit Biba All rights reserved.
 * University of Prishtina, Prishtine, Kosove. tonit.biba@hotmail.com.
 *
 * @file  option.c
 *
 * @brief Implements functions for options and arguments procesing.
 * 
 * @author Tonit Biba (tonit.biba@hotmail.com)
 * @date   $Date: Sht 30 Maj 2020 09:52:49.PD CEST $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <getopt.h>
#include <unistd.h>
#include <libgen.h>

#include "option.h"

/***************************************************************************//** 
 * @brief Initializes the data structure describing the application options 
 *
 * This functions initializes the data structure that describes the specified
 * application options.
 *
 * @param[in,out] option - pointer to the application's options object
 *
 * @retval void
 ******************************************************************************/
void option_init  (/*@out@*/Option_t *option)
{
  if (option == NULL)
    {
      return;
    }
  
  option->append      = -1;
  option->list        = -1;
  option->nr_personal = NULL;
  option->name        = NULL;
  option->surname     = NULL;
  option->age         = NULL;
  option->address     = NULL;
  option->test_date   = NULL;
  option->f_name      = NULL;
  option->fp          = NULL;
}

/***************************************************************************//** 
 * @brief Frees the data structure describing the application options 
 *
 * This functions frees the data structure that describes the specified
 * application options
 *
 * @param[in,out] option - pointer to the application's options object
 *
 * @retval void
 ******************************************************************************/
void option_free  (/*@out@*/Option_t *option)
{
  if (option == NULL)
    {
      return;
    }
  
  if (option->f_name == NULL || option->fp == NULL)
    {
      return;
    }

  option->append      = -1;
  option->list        = -1;
  option->nr_personal = NULL;
  option->name = NULL;
  option->surname = NULL;
  option->age = NULL;
  option->address = NULL;
  option->test_date = NULL;
  option->f_name = NULL;

  if (option->fp != NULL)
    {
      (void) fclose (option->fp);
      option->fp = NULL;
    }
}

/***************************************************************************//** 
 * @brief Handles the passed options from main program
 *
 * This functions processes the arguments that are send from main program.
 * application options
 *
 * @param[in] argc - number of arguments that will be procesed
 * @param[int] argv - Two dimensional array of arguments. 
 * @param[in,out] option - pointer to the application's options object
 *
 * @retval -1 in case of not initilized Option_t structure
 * @retval 1 in case of success process
 ******************************************************************************/
int option_proc (int argc, char *argv [], /*@out@*/Option_t *option)
{
  int n_opt = 0;

  if (option == NULL)
    {
      return -1;
    }
  
  while ((n_opt = getopt (argc, argv, OPT_PATTERN)) != -1)
    {
      switch (n_opt)
        {
        case 'f':
          if(optarg == NULL){
              printf("File name is mandatory.");
              option_usage (argv [0]);
          }else{
              option->f_name = optarg;
          }
          break;

        case 'a':
          option->append = 1;
          break;
  
        case 'p':
          if(optarg == NULL){
              printf("Please specify personal number.");
              option_usage (argv [0]);
          }else{
              option->nr_personal = optarg;
          }
          break;
        
        case 'n':
          if(optarg == NULL){
              printf("Please specify name.");
              option_usage (argv [0]);
          }else{
              option->name = optarg;
          }
          break;

        case 's':
          if(optarg == NULL){
              printf("Please specify surname.");
              option_usage (argv [0]);
          }else{
              option->surname = optarg;
          }
          break;

        case 'm':
          if(optarg == NULL){
              printf("Please specify age.");
              option_usage (argv [0]);
          }else{
              option->age = optarg;
          }
          break;

        case 'c':
          if(optarg == NULL){
              printf("Please specify address.");
              option_usage (argv [0]);
          }else{
              option->address = optarg;
          }
          break;
        
        case 'd':
          if(optarg == NULL){
              printf("Please specify test date.");
              option_usage (argv [0]);
          }else{
              option->test_date = optarg;
          }
          break;
          
        case 'h':          
          option_usage (argv [0]);
          break;
          
        case 'l':
          option->list = 1;
          break;
          
        case '?':
          printf ("\nUnsupported option '%c'. Please refer synopsis for correct usage.", n_opt);
          option_usage (argv [0]);
          break;
          
        default:
          option_usage (argv [0]);          
        }
    }
  return 1;
}

/***************************************************************************//** 
 * @brief Writes the usage information  
 *
 * This functions writes the usage information in the stdout and exits with 
 * an error
 *
 * @param[in] app_name - the application name
 *
 * @retval void
 ******************************************************************************/
void option_usage (const char *app_name)
{
  char *a_name = basename ((char *) app_name);
  
  printf ("\n%s - System for managing patients with Covid-19\n", a_name);
  printf ("\nSYNOPSIS\n");
  printf ("\tcovid [OPTION] ... \n");
  printf ("\t -f arg, (mandatory) the file name \n");
  printf ("\t -a,     (optional) append a string to the file \n");
  printf ("\t -h,     (optional) print this message \n");
  printf ("\t -l,     (optional) list all patients stored in the file \n");
  printf ("\t -p arg, (optional) personal number \n");
  printf ("\t -n arg, (optional) patient name \n");
  printf ("\t -s arg, (optional) patient surname \n");
  printf ("\t -m arg, (optional) patient age \n");
  printf ("\t -c arg, (optional) patient current address \n");
  printf ("\t -d arg, (optional) test date \n\n");
  
  exit (EXIT_FAILURE);
}

