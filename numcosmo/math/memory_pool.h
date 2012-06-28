/***************************************************************************
 *            memory_pool.h
 *
 *  Wed June 15 18:57:38 2011
 *  Copyright  2011 Sandro Dias Pinto Vitenti
 *  <sandro@isoftware.com.br>
 ****************************************************************************/
/*
 * numcosmo
 * Copyright (C) Sandro Dias Pinto Vitenti 2012 <sandro@lapsandro>
 * numcosmo is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * numcosmo is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _NC_MEMORY_POOL_H
#define _NC_MEMORY_POOL_H

G_BEGIN_DECLS

typedef gpointer (*NcmMemoryPoolAlloc) (void);

typedef struct _NcmMemoryPool NcmMemoryPool;

/**
 * NcmMemoryPool:
 * 
 * FIXME
 */
struct _NcmMemoryPool
{
  /*< private >*/
  GStaticMutex append;
  GPtrArray *slices;
  NcmMemoryPoolAlloc alloc;
  GDestroyNotify free;
};

typedef struct _NcmMemoryPoolSlice NcmMemoryPoolSlice;

/**
 * NcmMemoryPoolSlice:
 * @p: Pointer to the actual slice
 * @lock: Mutex lock used by the pool
 * @mp: A back pointer to the pool
 */
struct _NcmMemoryPoolSlice
{
  gpointer p;
  GStaticMutex lock;
  NcmMemoryPool *mp;
};

NcmMemoryPool *ncm_memory_pool_new (NcmMemoryPoolAlloc mp_alloc, GDestroyNotify mp_free);
void ncm_memory_pool_free (NcmMemoryPool *mp, gboolean free_slices);
void ncm_memory_pool_set_min_size (NcmMemoryPool *mp, gsize n);
gpointer ncm_memory_pool_get (NcmMemoryPool *mp);
void ncm_memory_pool_return (gpointer p);

G_END_DECLS

#endif /* _NC_MEMORY_POOL_H */