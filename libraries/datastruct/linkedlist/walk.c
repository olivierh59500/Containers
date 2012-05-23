/* walk.c -- associative array implemented as ordered linked list */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base/memento/memento.h"

#include "base/types.h"
#include "string.h"
#include "keyval/string.h"

#include "datastruct/linkedlist.h"

#include "impl.h"

/* ----------------------------------------------------------------------- */

error linkedlist_walk(const linkedlist_t       *t,
                      linkedlist_walk_callback *cb,
                      void                     *opaque)
{
  error               err;
  linkedlist__node_t *n;
  linkedlist__node_t *next;

  if (t == NULL)
    return error_OK;

  for (n = t->anchor; n; n = next)
  {
    next = n->next;

    err = cb(&n->item, opaque);
    if (err)
      return err;
  }

  return error_OK;
}

/* ----------------------------------------------------------------------- */