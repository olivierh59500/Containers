/* linkedlist-impl.h -- associative array implemented as ordered linked list */

#ifndef LINKEDLIST_IMPL_H
#define LINKEDLIST_IMPL_H

#include "types.h"

#include "item.h"

#include "linkedlist.h"

/* ----------------------------------------------------------------------- */

typedef struct linkedlist__node
{
  struct linkedlist__node  *next;
  item_t                    item;
}
linkedlist__node_t;

struct linkedlist
{
  linkedlist__node_t       *anchor;

  int                       count;

  const void               *default_value;

  linkedlist_compare       *compare;
  linkedlist_destroy_key   *destroy_key;
  linkedlist_destroy_value *destroy_value;
};

/* ----------------------------------------------------------------------- */

/* internal tree walk functions. callback returns a pointer to a
 * linkedlist__node_t, so internal for that reason. */

typedef error (linkedlist__walk_internal_callback)(linkedlist__node_t *n,
                                                   void               *opaque);

error linkedlist__walk_internal(linkedlist_t                       *t,
                                linkedlist__walk_internal_callback *cb,
                                void                               *opaque);

/* ----------------------------------------------------------------------- */

#endif /* LINKEDLIST_IMPL_H */