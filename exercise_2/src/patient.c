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
#include <arpa/inet.h>

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
int Patient_init(const int nr_personal, const char *name, const char *surname, const int age, const char *address, const char *test_date, Patient_t *const patient)
{
    if(nr_personal==0 || name == NULL || surname == NULL || age ==0 || address == NULL || test_date == NULL)
    {
        return 0;
    }

    patient->nr_personal = nr_personal;
    patient->name = NULL;
    patient->surname = NULL;
    patient->age = age;
    patient->address = NULL;
    patient->test_date = NULL;
    return 1;
}

int Patient_write (FILE *fp, /*@null@*/ const Patient_t *const patient)
{
    int status = 0;
    int personal_number = 0;

    if(patient == NULL)
    {
        return status;
    }

    personal_number = htonl(patient->nr_personal);

    status = (int) fwrite ((const void *) &personal_number, (size_t) 1, (size_t) SER_INT_LEN, fp);

    return status;
}