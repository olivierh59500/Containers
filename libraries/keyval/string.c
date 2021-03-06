/* --------------------------------------------------------------------------
 *    Name: string.c
 * Purpose: Functions for keys or values which are strings
 * ----------------------------------------------------------------------- */

#include <string.h>

#include "base/types.h"

#include "keyval/string.h"

size_t stringkv_len(const void *key_)
{
  const char *key = key_;

  return strlen(key);
}

int stringkv_compare(const void *a_, const void *b_)
{
  const char *a = a_;
  const char *b = b_;

  if (a && b)
    return strcmp(a, b);

  /* sort NULL keys after non-NULL */
  if (!a && !b) return  0;
  else if (!a)  return -1;
  else          return  1;
}

/* Fowler/Noll/Vo FNV-1 hash */
unsigned int stringkv_hash(const void *key_)
{
  const unsigned char *s = key_;
  unsigned int         h;

  h = 0x811c9dc5;
  while (*s)
  {
    h += (h << 1) + (h << 4) + (h << 7) + (h << 8) + (h << 24);
    h ^= *s++;
  }

  return h;
}

const char *stringkv_fmt(const void *kv)
{
  return kv;
}

