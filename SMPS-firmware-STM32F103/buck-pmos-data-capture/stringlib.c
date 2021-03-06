/* STM32F1 Power Management String Library Functions

Initial 30 November 2013
*/

/*
 * This file is part of the battery-management-system project.
 *
 * Copyright 2013 K. Sarkies <ksarkies@internode.on.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "stringlib.h"

/*--------------------------------------------------------------------------*/
/** @brief Convert an ASCII decimal string to an integer

The conversion stops without error when the first non-numerical character
is encountered.

@param[in] char* buffer: externally defined buffer with the string.
@returns int32_t: integer value to be converted to ASCII form.
*/

int32_t asciiToInt(char* buffer)
{
    int32_t number = 0;
    while ((*buffer >= '0') && (*buffer <= '9'))
    {
        number = number*10+(*buffer - '0');
        buffer++;
    }
    return number;
}
/*--------------------------------------------------------------------------*/
/** @brief Convert an Integer to ASCII decimal form

The output is a variable length string up to 10 characters.

@param[in] int32_t value: integer value to be converted to ASCII form.
@param[in] char* buffer: externally defined buffer to hold the result. Length
                         at least 11.
*/

void intToAscii(int32_t value, char* buffer)
{
    uint8_t nr_digits = 0;
    uint8_t i = 0;
    char temp_buffer[25];

/* Add minus sign if negative, and form absolute */
    if (value < 0)
    {
        buffer[nr_digits++] = '-';
        value = value * -1;
    }
/* Stop if value is zero */
    if (value == 0) buffer[nr_digits++] = '0';
    else
    {
/* Build string in reverse */
        while (value > 0)
        {
            temp_buffer[i++] = "0123456789"[value % 10];
            value /= 10;
        }
/* Copy across correcting the order */
        while (i > 0)
        {
            buffer[nr_digits++] = temp_buffer[--i];
        }
    }
    buffer[nr_digits] = 0;
}
/*--------------------------------------------------------------------------*/
/** @brief Convert an Integer to 16 bit ASCII hex form

The output is a fixed length 4 character string.

@param[in] int32_t value: integer value to be printed.
@param[in] char* buffer: externally defined buffer to hold the result. Length
                         at least 5.
*/

void intToHex(int32_t value, char* buffer)
{
    uint8_t i;

    for (i = 0; i < 4; i++)
    {
        buffer[i] = "0123456789ABCDEF"[value & 0xF];
        value >>= 4;
    }
    buffer[4] = 0;
}

/*--------------------------------------------------------------------------*/
/** @brief Append a string to another

@param[in] char* string: original string, returned after appending.
@param[in] char* appendage: string to be appended to end.
*/

void stringAppend(char* string, char* appendage)
{
    uint8_t i=0;
    uint8_t j=stringLength(string);
    while (appendage[i] > 0)
    {
        string[j++] = appendage[i++];
    }
    string[j] = 0;
}
/*--------------------------------------------------------------------------*/
/** @brief String Copy

@param[in] char* string: copied string, returned.
@param[in] char* original: original string to be copied.
*/

void stringCopy(char* string, char* original)
{
    uint8_t i=0;
    while (original[i] > 0)
    {
        string[i] = original[i];
        i++;
    }
    string[i] = 0;
}
/*--------------------------------------------------------------------------*/
/** @brief Compute string length

@param[in] char* string: string to be measured for length.
@returns int16_t: length of string.
*/

uint16_t stringLength(char* string)
{
    uint8_t i=0;
    while (string[i] > 0) i++;
    return i;
}

/*--------------------------------------------------------------------------*/
/** @brief Equality of Strings

@param[in] char* string1: 
@param[in] char* string2: 
@returns uint8_t: 1 if strings are equal, 0 otherwise.
*/

uint16_t stringEqual(char* string1,char* string2)
{
    while (*string1 > 0)
    {
        if (*string1 != *string2) return 0;
        string1++;
        string2++;
    }
    return 1;
}


