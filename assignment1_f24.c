/*******************************************************************************
 * Copyright (C) 2024 by <Student Name>
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. <Student Name> and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    assignment1_f24.c
 * @brief   
 *
 *
 * @author  Parth Patel
 * @date    09-02-2024
 *
 */
#include "assignment1_f24.h"

#define ERROR       0xFFFFFFFFU     // for any errors

/**
 * @brief      { function_description }
 *
 * @param[in]  num      { description }
 * @param[in]  nbits    { description }
 *
 * @return     { description_of_the_return_value }
 */
uint8_t rotate_right(uint8_t num, uint8_t nbits)
{
    nbits &= 7;  // reducing shifts for nbits>7

    uint8_t shifted = num >> nbits; // first normal right shift the number by n bits

    uint8_t remained_bits = num << (8- nbits); // then get back the ignored bits at the right position

    uint8_t final_value = shifted | remained_bits;

    return final_value;
}

/**
 * @brief      { function_description }
 *
 * @param[in/out]  str  { description }
 *
 * @return     { description_of_the_return_value }
 */

 
uint32_t binstr_to_uint(const char *str)
{
    if (!str || str[0] != '0' || str[1] != 'b') { //Error checker for null  string and '0b' 
        return 0xFFFFFFFF; // return Error
    }

    uint32_t value = 0;
    int i = 2;  // starting after '0b'
    int bit = 0;

    while (str[i]) {
        // Check if the current character is neither '0' nor '1'
        if (str[i] != '0' && str[i] != '1') {
            return 0xFFFFFFFF; // Invalid format
        }

        // Shift the result left by one bit to make room for the new bit
        value = value << 1;

        // Add the current bit (0 or 1) to the result
        value = value | (str[i] - '0');

        // Increase the bit count
        bit++;

        // Check if the bit count exceeds 32
        if (bit > 32) {
            return 0xFFFFFFFF; // Too many bits
        }

        i++;
    }

    // Ensure that there's at least one binary digit
    if (bit == 0) {
        return 0xFFFFFFFF; // No binary digits
    }

    return value;
}

/**
 * @brief      { function_description }
 *
 * @param[in/out]  str    { description }
 * @param[in]      size   { description }
 * @param[in]      num    { description }
 * @param[in]      nbits  { description }
 *
 * @return     { description_of_the_return_value }
 */
int32_t int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits)
{
    // Check if nbits is within valid range and if the string size is sufficient
    if (nbits < 1 || nbits > 255 || size < nbits + 3) { // 3 = "0b" + '\0'
        str[0] = '\0';
        return 0xFFFFFFFF; // Error code
    }

    

    // Ensure nbits is sufficient to represent the number in 2's complement
    int32_t max_val = (1 << (nbits - 1)) - 1; // Maximum representable value in nbits
    int32_t min_val = -max_val - 1;           // Minimum representable value in nbits


    if (num < min_val || num > max_val) {
        str[0] = '\0';
        return 0xFFFFFFFF; // Error code
    }

    // Start filling the string with the binary representation
    str[0] = '0';
    str[1] = 'b';

    for (int i = 0; i < nbits; i++) {
        int bit_position = nbits - i - 1;
        str[i + 2] = (num & (1 << bit_position)) ? '1' : '0';
    }

    str[nbits + 2] = '\0'; // Null-terminate the string

    return nbits + 2; // Return the length of the binary string including "0b"
}

/**
 * @brief      { function_description }
 *
 * @param[in]  str        { description }
 *
 * @return     { description_of_the_return_value }
 */
uint32_t hexstr_to_uint(const char *str)
{
    unsigned int answer = 0;

    int i = 0;

    // Check for 0x or 0X
    if (str == NULL || str[0] != '0' || (str[1] != 'x' && str[1] != 'X')) {
        return 0xFFFFFFFF; // Invalid prefix
    }

    // Skip the 0x
    i = 2;

    // Convert each hexadecimal digit
    while (str[i] != '\0') {

        char dig = str[i];

        if (dig >= '0' && dig <= '9') {

            answer = (answer << 4) | (dig - '0');

        } else if (dig >= 'A' && dig <= 'F') {

            answer = (answer << 4) | (dig - 'A' + 10);

        } else if (dig >= 'a' && dig <= 'f') {

            answer = (answer << 4) | (dig - 'a' + 10);

        } else {

            // Invalid hexadecimal character

            return 0xFFFFFFFF;
        }

        i++;
    }

    // Check for too many hexadecimal digits
    if ( (i > 10) || (i < 3)) {

        return 0xFFFFFFFF; // Too many digits or 
    }

    return answer;
}

/**
 * @brief      { function_description }
 *
 * @param[in]  input      { description }
 * @param[in]  bit        { description }
 * @param[in]  operation  { description }
 *
 *
 * @return     { description_of_the_return_value }
 */
uint32_t twiggle_except_bit(uint32_t input, int bit, operation_t operation)
{
    // Check if the bit index is within the valid range (0 to 31)
    if (bit < 0 || bit > 31) {
        return 0xFFFFFFFF; // Return error if the bit index is out of range
    }

    if ( (input < 0) || (input > 0xFFFFFFFF) ){
        return 0xFFFFFFFF; // Return error if the input is out of range
    }

    // Create a mask with all bits set except the specified bit
    uint32_t mask = ~((uint32_t)1 << bit);

    switch (operation) {
        case CLEAR:
            // Clear all bits except the specified one
            input &= ~mask; // Clear all bits except the one at the given position
            break;

        case SET:
            // Set all bits except the specified one
            input |= mask; // Set all bits except the one at the given position
            break;

        case TOGGLE:
            // Toggle all bits except the specified one
            input ^= mask; // Toggle all bits except the one at the given position
            break;

        default:
            return 0xFFFFFFFF; // Return error if an invalid operation is specified
    }

    return input;
}

/**
 * @brief      { function_description }
 *
 * @param[in]  input       { description } 
 * @param[in]  start_bit   { description }
 *
 * @return     { description_of_the_return_value }
 */
uint32_t grab_four_bits(uint32_t input, int start_bit)
{
   if (start_bit < 0 || start_bit > 28) {
        return 0xFFFFFFFF; // Invalid start bit
    }

    if ( (input < 0) || (input > 0xFFFFFFFF) ){
        return 0xFFFFFFFF; // Return error if the input is out of range
    }

  uint32_t temp=   input >> start_bit;

  uint32_t result= temp &  15;

  return result;
}


/**
 * @brief      { function_description }
 *
 * @param[in/out]  str   { description } 
 * @param[in]  size      { description }
 * @param[in]  loc       { description }
 * @param[in]  nbytes    { description }
 *
 * @return     { description_of_the_return_value }
 */

char *hexdump(char *str, size_t size, const void *loc, size_t nbytes)
{
    return NULL;
}