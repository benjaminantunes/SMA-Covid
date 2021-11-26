

// Use of a class removes many C nasties and also allows you to easily
// create multiple generators.
// To compile on GNU a simple line is:
// g++ -O3 RandMT.cc -o RandMT
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <thread>

// To keep this all as one file (easier distribution) the class is
// in the code, cut'n'paste this bit to create a .h for use in
// other programs
#ifndef WIN32
#include <inttypes.h>
#else
typdef uint8_t unsigned __int8;
typdef uint32_t unsigned __int32;
#endif
#include "RandMT.hpp"


RandMT::RandMT() {
	//std::cout<< "Creation objet sans fichier" << std::endl;
	uint32_t tabInit[4] = {0x123, 0x234, 0x345, 0x456};
	init_by_array(tabInit,4);
}

RandMT::RandMT(std::string fileName) {

	restoreStatus(fileName);

}

void RandMT::saveStatus(std::string inFileName)
{

	std::ofstream monFlux(inFileName.c_str());

	if(monFlux)
	{
	    monFlux << mti << std::endl;
	    for(int i = 0 ; i < N ; i++)
		{
	   		monFlux << mt[i] << " ";
		}

	}
	else
	{
	    std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
	}
}


void RandMT::restoreStatus(std::string inFileName)
{

	std::ifstream monFlux(inFileName.c_str());
	if(monFlux)
	{

	    monFlux >> mti;


	    for(int i = 0 ; i < N ; i++)
		{
	   		monFlux >> mt[i] ;

		}

	}
	else
	{
	    std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
	}
}


 /* initializes mt[N] with a seed */
void RandMT::init_genrand(uint32_t s)
{
	//std::cout<< "Init genrand" << std::endl;
	mt[0]= s & 0xffffffffUL;
	for (mti=1; mti<N; mti++) {
	    mt[mti] =
		(1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
	    /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
	    /* In the previous versions, MSBs of the seed affect   */
	    /* only MSBs of the array mt[].                        */
	    /* 2002/01/09 modified by Makoto Matsumoto             */
	    mt[mti] &= 0xffffffffUL;
	    /* for >32 bit machines */
	}
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void RandMT::init_by_array(uint32_t init_key[], int key_length)
{
	//std::cout<< "Init by array" << std::endl;
	int i, j, k;
	init_genrand(19650218UL);
	//std::cout<< "Init by array ça continue" << std::endl;
	i=1; j=0;
	k = (N>key_length ? N : key_length);
	for (; k; k--) {
	    mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
	      + init_key[j] + j; /* non linear */
	    mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
	    i++; j++;
	    if (i>=N) { mt[0] = mt[N-1]; i=1; }
	    if (j>=key_length) j=0;
	}
	for (k=N-1; k; k--) {
	    mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
	      - i; /* non linear */
	    mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
	    i++;
	    if (i>=N) { mt[0] = mt[N-1]; i=1; }
	}

	mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
uint32_t RandMT::genrand_int32(void)
{
	uint32_t y;
	//unsigned long mag01[2]={0x0UL, MATRIX_A};
	/* mag01[x] = x * MATRIX_A  for x=0,1 */
	//std::cout << "mti vaut : " << mti << std::endl;
	if (mti >= N) { /* generate N words at one time */
	    int kk;

	    if (mti == N+1)   /* if init_genrand() has not been called, */
	        init_genrand(5489UL); /* a default initial seed is used */

	    for (kk=0;kk<N-M;kk++) {
	        y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
	        mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
	    }
	    for (;kk<N-1;kk++) {
	        y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
	        mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
	    }
	    y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
	    mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

	    mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
uint32_t RandMT::genrand_int31(void)
{
	return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double RandMT::genrand_real1(void)
{
	return genrand_int32()*(1.0/4294967295.0);
	/* divided by 2^32-1 */
}

/* generates a random number on [0,1)-real-interval */
double RandMT::genrand_real2(void)
{
	return genrand_int32()*(1.0/4294967296.0);
	/* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double RandMT::genrand_real3(void)
{
	return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0);
	/* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double RandMT::genrand_res53(void)
{
	unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6;
	return(a*67108864.0+b)*(1.0/9007199254740992.0);
}






