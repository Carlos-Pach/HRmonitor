/*
 * algorithm.h
 *
 *  Created on: Aug 11, 2020
 *      Author: CarlosPach
 */

#ifndef SOURCES_ALGORITHM_H_
#define SOURCES_ALGORITHM_H_

#include "Cpu.h"

//#define true 1
//#define false 0
#define FS 100
#define BUFFER_SIZE  (FS * 5)
#define HR_FIFO_SIZE 7
#define MA4_SIZE  4 // DO NOT CHANGE
#define HAMMING_SIZE  5// DO NOT CHANGE
#define min(x,y) ((x) < (y) ? (x) : (y))


/* 			Error noted: ONLY declare variables (e.g. const uint16_t auw_hamm ...)
 * 			but do not define variables (e.g. auw_hamm[n] = { ... })
 * 			Variables are only defined in source files, not header files
 */

/*const uint16_t auw_hamm[31]={ 41,    276,    512,    276,     41 }; //Hamm=  long16(512* hamming(5)');
//uch_spo2_table is computed as  -45.060*ratioAverage* ratioAverage + 30.354 *ratioAverage + 94.845 ;

const uint8_t uch_spo2_table[184]={ 95, 95, 95, 96, 96, 96, 97, 97, 97, 97, 97, 98,
									98, 98, 98, 98, 99, 99, 99, 99,
                             	  } ;*/

static  int32_t an_dx[BUFFER_SIZE - MA4_SIZE]; // delta
static  int32_t an_x[BUFFER_SIZE]; //ir
static  int32_t an_y[BUFFER_SIZE]; //red


void maxim_heart_rate_and_oxygen_saturation(uint32_t *pun_ir_buffer ,  int32_t n_ir_buffer_length, uint32_t *pun_red_buffer ,   int32_t *pn_spo2, int8_t *pch_spo2_valid ,  int32_t *pn_heart_rate , int8_t  *pch_hr_valid);
void maxim_find_peaks( int32_t *pn_locs, int32_t *pn_npks,  int32_t *pn_x, int32_t n_size, int32_t n_min_height, int32_t n_min_distance, int32_t n_max_num );
void maxim_peaks_above_min_height( int32_t *pn_locs, int32_t *pn_npks,  int32_t *pn_x, int32_t n_size, int32_t n_min_height );
void maxim_remove_close_peaks( int32_t *pn_locs, int32_t *pn_npks,   int32_t  *pn_x, int32_t n_min_distance );
void maxim_sort_ascend( int32_t *pn_x, int32_t n_size );
void maxim_sort_indices_descend(  int32_t  *pn_x, int32_t *pn_indx, int32_t n_size);

#endif /* SOURCES_ALGORITHM_H_ */
