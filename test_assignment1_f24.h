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
 * @file    test_assignment1_f24.h
 * @brief   Header file for test cases of functions used in embedded systems projects.
 *
 *
 * @author  Parth Patel
 * @date    02-09-2024
 *
 */

#ifndef TEST_ASSIGNMENT1_F24_H
#define TEST_ASSIGNMENT1_F24_H

#include <stdint.h>     // for uint32_t and similar definitions
#include <stdlib.h>     // for size_t
#include <stdio.h>


// typedef enum {
//     CLEAR,    // Set the bits to 0
//     SET,      // Set the bits to 1
//     TOGGLE    // Change bit value 1 to 0 and vice versa
// } operation_t;

uint8_t test_rotate_right();
uint32_t test_binstr_to_uint();
int32_t test_int_to_binstr();
uint32_t test_hexstr_to_uint();

uint32_t test_twiggle_except_bit();
uint32_t test_grab_four_bits();
int test_hexdump();

#endif  /* TEST_ASSIGNMENT1_F24_H */
