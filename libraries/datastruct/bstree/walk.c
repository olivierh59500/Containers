/* --------------------------------------------------------------------------
 *    Name: walk.c
 * Purpose: Associative array implemented as a binary search tree
 * ----------------------------------------------------------------------- */

#include <stdlib.h>

#include "base/types.h"

#include "datastruct/bstree.h"

#include "impl.h"

static error walk_in_order(const bstree__node_t *n,
                           bstree_walk_flags     flags,
                           int                   level,
                           bstree_walk_callback *cb,
                           void                 *opaque)
{
  error err;

  if (n == NULL)
    return error_OK;

  err = walk_in_order(n->child[0], flags, level + 1, cb, opaque);
  if (!err)
    err = cb(&n->item, level, opaque);
  if (!err)
    err = walk_in_order(n->child[1], flags, level + 1, cb, opaque);

  return err;
}

static error walk_pre_order(const bstree__node_t *n,
                            bstree_walk_flags     flags,
                            int                   level,
                            bstree_walk_callback *cb,
                            void                 *opaque)
{
  error err;

  if (n == NULL)
    return error_OK;

  err = cb(&n->item, level, opaque);
  if (!err)
    err = walk_in_order(n->child[0], flags, level + 1, cb, opaque);
  if (!err)
    err = walk_in_order(n->child[1], flags, level + 1, cb, opaque);

  return err;
}

static error walk_post_order(const bstree__node_t *n,
                             bstree_walk_flags     flags,
                             int                   level,
                             bstree_walk_callback *cb,
                             void                 *opaque)
{
  error err;

  if (n == NULL)
    return error_OK;

  err = walk_in_order(n->child[0], flags, level + 1, cb, opaque);
  if (!err)
    err = walk_in_order(n->child[1], flags, level + 1, cb, opaque);
  if (!err)
    err = cb(&n->item, level, opaque);

  return err;
}

error bstree_walk(const bstree_t       *t,
                  bstree_walk_flags     flags,
                  bstree_walk_callback *cb,
                  void                 *opaque)
{
  error (*walker)(const bstree__node_t *n,
                  bstree_walk_flags     flags,
                  int                   level,
                  bstree_walk_callback *cb,
                  void                 *opaque);

  if (t == NULL)
    return error_OK;

  // does not yet implement bstree_WALK_BRANCHES etc

  switch (flags & bstree_WALK_ORDER_MASK)
  {
  default:
  case bstree_WALK_IN_ORDER:
    walker = walk_in_order;
    break;

  case bstree_WALK_PRE_ORDER:
    walker = walk_pre_order;
    break;

  case bstree_WALK_POST_ORDER:
    walker = walk_post_order;
    break;
  }

  return walker(t->root, flags, 0, cb, opaque);
}

