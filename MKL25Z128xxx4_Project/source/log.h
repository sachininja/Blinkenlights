/*
 * File Name: log.h
 *
 *  Created on: Sep 26, 2021
 *      Author: Sachin Mathad
 *
 *Purpose: PES Assignment 3
 *Description: This file contains logging related declarations
 */

#ifndef LOG_H_
#define LOG_H_

/*@Brief: LOG data only when DEBUG module is enabled.
 * Citations: Class lectures by Howdy Pierce
 * */
#include <stdio.h>
#ifdef DEBUG
#define LOG printf
#else
#define LOG(...)
#endif

#endif /* LOG_H_ */
