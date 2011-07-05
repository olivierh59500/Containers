/* orderedarray-impl.h -- associative array implemented as ordered array */

#ifndef ORDEREDARRAY_IMPL_H
#define ORDEREDARRAY_IMPL_H

#include "types.h"

#include "item.h"

#include "orderedarray.h"

/* ----------------------------------------------------------------------- */

typedef struct orderedarray__node
{
  item_t                      item;
}
orderedarray__node_t;

struct orderedarray
{
  orderedarray__node_t       *array;
  int                         nelems;
  int                         maxelems;

  const void                 *default_value;

  orderedarray_compare       *compare;
  orderedarray_destroy_key   *destroy_key;
  orderedarray_destroy_value *destroy_value;
};

/* ----------------------------------------------------------------------- */

/* internal tree walk functions. callback returns a pointer to a
 * orderedarray__node_t, so internal for that reason. */

typedef error (orderedarray__walk_internal_callback)(orderedarray__node_t *n,
                                                     void                 *opaque);

error orderedarray__walk_internal(orderedarray_t                       *t,
                                  orderedarray__walk_internal_callback *cb,
                                  void                                 *opaque);

/* ----------------------------------------------------------------------- */

#endif /* ORDEREDARRAY_IMPL_H */