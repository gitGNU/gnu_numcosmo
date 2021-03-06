/***************************************************************************
 *            nc_xcor_limber_gal.h
 *
 *  Tue July 14 12:00:00 2015
 *  Copyright  2015  Cyrille Doux
 *  <cdoux@apc.in2p3.fr>
 ****************************************************************************/
/*
 * numcosmo
 * Copyright (C) 2015 Cyrille Doux <cdoux@apc.in2p3.fr>
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

#ifndef _NC_XCOR_LIMBER_GAL_H_
#define _NC_XCOR_LIMBER_GAL_H_

#include <glib.h>
#include <glib-object.h>
#include <numcosmo/build_cfg.h>
#include <numcosmo/math/ncm_spline.h>
#include <numcosmo/math/ncm_spline_cubic_notaknot.h>
#include <numcosmo/xcor/nc_xcor_limber.h>

G_BEGIN_DECLS

#define NC_TYPE_XCOR_LIMBER_GAL (nc_xcor_limber_gal_get_type ())
#define NC_XCOR_LIMBER_GAL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), NC_TYPE_XCOR_LIMBER_GAL, NcXcorLimberGal))
#define NC_XCOR_LIMBER_GAL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), NC_TYPE_XCOR_LIMBER_GAL, NcXcorLimberGalClass))
#define NC_IS_XCOR_LIMBER_GAL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NC_TYPE_XCOR_LIMBER_GAL))
#define NC_IS_XCOR_LIMBER_GAL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), NC_TYPE_XCOR_LIMBER_GAL))
#define NC_XCOR_LIMBER_GAL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), NC_TYPE_XCOR_LIMBER_GAL, NcXcorLimberGalClass))

typedef struct _NcXcorLimberGalClass NcXcorLimberGalClass;
typedef struct _NcXcorLimberGal NcXcorLimberGal;

/**
 * NcXcorLimberGalParams:
 * @NC_XCOR_LIMBER_GAL_BIAS: FIXME
 * @NC_XCOR_LIMBER_GAL_SPARAM_LEN: FIXME
 *
 * FIXME
 */
typedef enum _NcXcorLimberGalParams
{
	NC_XCOR_LIMBER_GAL_BIAS = 0,
	NC_XCOR_LIMBER_GAL_SPARAM_LEN, /*< skip >*/
} NcXcorLimberGalParams;

#define NC_XCOR_LIMBER_GAL_DEFAULT_BIAS (1.0)

#define NC_XCOR_LIMBER_GAL_DEFAULT_PARAMS_ABSTOL (0.0)

struct _NcXcorLimberGal
{
	/*< private >*/
	NcXcorLimber parent_instance;
	NcmSpline* dN_dz;
	gdouble z_max;
	gdouble z_min;
	gdouble nbar;
	gdouble nbarm1;
};

struct _NcXcorLimberGalClass
{
	/*< private >*/
	NcXcorLimberClass parent_class;
};

GType nc_xcor_limber_gal_get_type (void) G_GNUC_CONST;
void nc_xcor_limber_gal_set_dNdz (NcXcorLimberGal* xclg, GArray* z, GArray* dN_dz_array);

G_END_DECLS

#endif /* _NC_XCOR_LIMBER_GAL_H_ */
