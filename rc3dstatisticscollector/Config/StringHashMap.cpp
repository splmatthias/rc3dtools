/**
 * @file StringHashMap.cpp
 * 
 * @author Andreas Seekircher <aseek@cs.miami.edu>
 * 
 */
#include "StringHashMap.h"
#include <cstddef>
#include <cstring>

//#include "MurmurHash2.h"
//#include "City.h"

#include <cstdio>
//------------------------------------------------------------------------------

/*unsigned int hash_128_swapc( const void *p, unsigned int len )
{
  register unsigned long long r8 = 0x1591aefa5e7e5a17ULL,
                              r9 = 0x2bb6863566c4e761ULL,
                              rax = len ^ r8,
                              rcx = r9,
                              rdx;
#define bswap( r ) \
  __asm__ __volatile__ ( "bswapq %0" : "+r" (r) : : )
#define mul128( a, d, r ) \
  __asm__ __volatile__ ( "mulq %2" : "+a" (a), "=d" (d) : "r" (r) : )

  while ( len >= 16 ) {
    rax = ( rax ^ ((unsigned long long *) p)[ 0 ] ) * r8;
    rcx = ( rcx ^ ((unsigned long long *) p)[ 1 ] ) * r9;
    bswap( rax );
    bswap( rcx );
    p = &((unsigned long long *) p)[ 2 ];
    len -= 16;
  }
  if ( len != 0 ) {
    if ( ( len & 8 ) != 0 ) {
      rdx = 0;
      rax ^= ((unsigned long long *) p)[ 0 ];
      p = &((unsigned long long *) p)[ 1 ];
    }
    if ( ( len & 4 ) != 0 ) {
      rdx = ((unsigned int *) p)[ 0 ];
      p = &((unsigned int *) p)[ 1 ];
    }
    if ( ( len & 2 ) != 0 ) {
      rdx = ( rdx << 16 ) | ((unsigned short *) p)[ 0 ];
      p = &((unsigned short *) p)[ 1 ];
    }
    if ( ( len & 1 ) != 0 ) {
      rdx = ( rdx << 8 ) | ((unsigned char *) p)[ 0 ];
    }
    rcx ^= rdx;
  }
  mul128( rax, rdx, r8 );
  rcx = ( rcx * r9 ) + rdx;
  rax ^= rcx;
  mul128( rax, rdx, r8 );
  rcx = ( rcx * r9 ) + rdx;
  rax ^= rcx;

  return ( rax >> 32 ) ^ rax;
}
*/

inline bool hasZeroByte(unsigned long long x)
{
  return ((x - 0x0101010101010101ULL) & ~x & 0x8080808080808080ULL);
}


/*unsigned int hash_128_swapc( const void *p )
{
  register unsigned long long r8 = 0x1591aefa5e7e5a17ULL,
                              r9 = 0x2bb6863566c4e761ULL,
                              rax = 879746238 ^ r8,
                              rcx = r9,
                              rdx;
#define bswap( r ) \
  __asm__ __volatile__ ( "bswapq %0" : "+r" (r) : : )
#define mul128( a, d, r ) \
  __asm__ __volatile__ ( "mulq %2" : "+a" (a), "=d" (d) : "r" (r) : )

  while (   !hasZeroByte(((unsigned long long*)p)[0]) 
         && !hasZeroByte(((unsigned long long*)p)[1]) ) {
    rax = ( rax ^ ((unsigned long long *) p)[ 0 ] ) * r8;
    rcx = ( rcx ^ ((unsigned long long *) p)[ 1 ] ) * r9;
    bswap( rax );
    bswap( rcx );
    p = &((unsigned long long *) p)[ 2 ];
  }
  int len = strlen((char*)p);
  //if(len > 16) printf("CRAP\n");

  if ( len != 0 ) {
    if ( ( len & 8 ) != 0 ) {
      rdx = 0;
      rax ^= ((unsigned long long *) p)[ 0 ];
      p = &((unsigned long long *) p)[ 1 ];
    }
    if ( ( len & 4 ) != 0 ) {
      rdx = ((unsigned int *) p)[ 0 ];
      p = &((unsigned int *) p)[ 1 ];
    }
    if ( ( len & 2 ) != 0 ) {
      rdx = ( rdx << 16 ) | ((unsigned short *) p)[ 0 ];
      p = &((unsigned short *) p)[ 1 ];
    }
    if ( ( len & 1 ) != 0 ) {
      rdx = ( rdx << 8 ) | ((unsigned char *) p)[ 0 ];
    }
    rcx ^= rdx;
  }
  mul128( rax, rdx, r8 );
  rcx = ( rcx * r9 ) + rdx;
  rax ^= rcx;
  mul128( rax, rdx, r8 );
  rcx = ( rcx * r9 ) + rdx;
  rax ^= rcx;

  return ( rax >> 32 ) ^ rax;
}

*/

//------------------------------------------------------------------------------

#define SEED 53789

inline size_t naive(const char *s)
{
    size_t hash = 1;
    for (; *s; ++s)
      hash = hash * SEED + *s;
    return hash;
}


inline size_t naive2(const char *s)
{  
    size_t hash = 1;
    unsigned long long *p = (unsigned long long *)s;
    for (; !hasZeroByte(*p); ++p)
      hash += *p;
 
    //const int l = strlen((char*)p);    
    //hash += *p & ((0x1ULL << (l*8))-1);
    
    return hash;
}



int StringHashFunctions::comparisons = 0;
int StringHashFunctions::hashcalls = 0;


size_t StringHashFunctions::operator()(const char *s) const
{
  //hashcalls++;
  //if(hashcalls % 10000 == 0)
  //{
  //  printf("hash keys %d, compares %d,  ratio %lf\n", hashcalls, comparisons, (double)comparisons/hashcalls);
  //}
  
  //return hash_128_swapc(s);
  //return hash_128_swapc(s, strlen(s));
  //return CityHash64(s, strlen(s));
  //return MurmurHash2(s, strlen(s), SEED);
  //return naive(s);
  return naive2(s);
  
  //static std::tr1::hash<std::string> defaultHash;
  //return defaultHash(std::string(s));
}

