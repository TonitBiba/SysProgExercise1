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

#ifndef _PATIENT_H
#define _PATIENT_H 1

#include <stdio.h>

#include <str_serialize.h>

#define SER_EOF         -2
#define SER_ALLOC_ERROR -1
#define SER_INT_LEN      4

typedef struct _Patient
{
    CString_t  nr_personal;
    CString_t  name;
    CString_t  surname;
    CString_t  age;
    CString_t  address;
    CString_t  test_date;
} Patient_t;

int Patient_init(const char *nr_personal, const char *name, const char *surname, const char *age, const char *address, const char *test_date, Patient_t *const patient);

void Patient_free(Patient_t *const patient);

int Patient_write (FILE *fp, /*@null@*/ const Patient_t *const patient);

int Patient_read  (FILE *fp, /*@null@*/ Patient_t *const patient);

void printHeader();

char *Get_Attr(const char *attr_name, char *arg);

int Write_Attr(FILE *fp, /*@null@*/ const CString_t *const arg);

#endif /* _PATIENT_H */