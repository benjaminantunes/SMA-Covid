#pragma once

// Use of a class removes many C nasties and also allows you to easily
// create multiple generators.
// To compile on GNU a simple line is:
// g++ -O3 RandMT.cc -o RandMT
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

// To keep this all as one file (easier distribution) the class is
// in the code, cut'n'paste this bit to create a .h for use in
// other programs
#ifndef WIN32
#include <inttypes.h>
#else
typdef uint8_t unsigned __int8;
typdef uint32_t unsigned __int32;
#endif

#ifndef _RANDMT_H_
#define _RANDMT_H_
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */
#define NB_THREAD 4
#endif

using namespace std;

static uint32_t      _mag01[2] = {0x0UL, MATRIX_A};
static unsigned long _compteur = 0;
class RandMT {

   uint32_t _mt[N];
   int      _mti = N +1;
   


public:

   RandMT() ;
   RandMT(string fileName) ;
   RandMT(unsigned long init_key[], int key_length);
   void          init_genrand(uint32_t s);
   void          init_by_array(uint32_t init_key[], int key_length);
   uint32_t      genrand_int32(void);
   uint32_t      genrand_int31(void);
   double        genrand_real1(void);
   double        genrand_real2(void);
   double        genrand_real3(void);
   double        genrand_res53(void);
   unsigned long getCompteur();
   void          saveStatus(string inFileName);
   void          restoreStatus(string inFileName);

};


