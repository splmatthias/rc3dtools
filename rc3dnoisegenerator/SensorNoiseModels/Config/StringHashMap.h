/**
 * @file StringHashMap.h
 * 
 * @author Andreas Seekircher <aseek@cs.miami.edu>
 * 
 */
#pragma once
#include <cstddef>
#include <string>
#include <cstring>

#include <tr1/unordered_map>
#define unordered_map std::tr1::unordered_map
#include "StringWrapper.h"

/**
 * This class provides string hash functions that can be used e.g. with
 * unordered_map. Faster then the default TR1 hash for strings.
 */
class StringHashFunctions
{
  public:

  // comparison
  inline bool operator()(const char *s1, const char *s2) const
  {
      //comparisons++;
      return strcmp(s1, s2) == 0;
  }
  
  // hash function
  inline size_t operator()(const std::string &str) const
  {
      return (*this)(str.c_str());
  }
  size_t operator()(const char *s) const;

  static int hashcalls, comparisons;
};


template<typename T> class CStringHashMap
 : public unordered_map<StringWrapper, T, StringHashFunctions, StringHashFunctions>
{
  public:
    CStringHashMap()
    { 
      this->max_load_factor(0.2);
    }
};

template<typename T> class StdStringHashMap 
 : public unordered_map<std::string, T>
{
  public:
    StdStringHashMap()
    { 
      this->max_load_factor(0.2);
    }
};
