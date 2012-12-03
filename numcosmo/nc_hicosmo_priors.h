/***************************************************************************
 *            nc_hicosmo_priors.h
 *
 *  Thu November 22 17:22:03 2012
 *  Copyright  2012  Sandro Dias Pinto Vitenti
 *  <sandro@isoftware.com.br>
 ****************************************************************************/
/*
 * numcosmo
 * Copyright (C) 2012 Sandro Dias Pinto Vitenti <sandro@isoftware.com.br>
 * 
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

#ifndef _NC_HICOSMO_PRIORS_H_
#define _NC_HICOSMO_PRIORS_H_

#include <glib.h>
#include <glib-object.h>
#include <numcosmo/nc_distance.h>

G_BEGIN_DECLS

typedef struct _NcHICosmoPriorTop NcHICosmoPriorTop;

/**
 * NcHICosmoPriorTop:
 * 
 * FIXME
 */
struct _NcHICosmoPriorTop
{
  /*< private >*/
  NcDistance *dist;
  gdouble z;
  gdouble mean;
  gdouble sigma;
};

NcHICosmoPriorTop *nc_hicosmo_prior_top_new (gdouble z, gdouble alpha, gdouble sigma_alpha, gint n);
void nc_hicosmo_prior_top_free (NcHICosmoPriorTop *tp);
void nc_hicosmo_prior_top_set (NcHICosmoPriorTop *tp, gdouble z, gdouble alpha, gdouble sigma_alpha, gint n);
void nc_hicosmo_prior_top_add (NcmLikelihood *lh, gdouble z, gdouble alpha, gdouble sigma_alpha, gint n);

G_END_DECLS

#endif /* _NC_HICOSMO_PRIORS_H_ */