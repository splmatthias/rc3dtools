/**
 * @file StringWrapper.cpp
 * 
 * @author Andreas Seekircher <aseek@cs.miami.edu>
 * 
 */
#include "StringWrapper.h"
#include "cstring"
#include <cstdio>

StringWrapper::StringWrapper(const char* s) : s(s), copied(false)
{
} 

StringWrapper::StringWrapper(const char* s, bool createCopy) : s(s), copied(false) 
{
  if(createCopy)  this->copy();
}

StringWrapper::StringWrapper(const StringWrapper& other) : copied(false)
{
  s = other;
  copy();
}
 
StringWrapper::~StringWrapper()
{
  if(copied)
    delete[] s;
}


void StringWrapper::copy()
{
  //static int count = 0;
  //count++;
  //printf("StringWrapper copy %d\n", count);
  
  if(copied) 
    return;
  int l = strlen(s);
  char *n = new char[l+1];
  memcpy(n, s, l+1);
  s = n;
  copied = true;
}
