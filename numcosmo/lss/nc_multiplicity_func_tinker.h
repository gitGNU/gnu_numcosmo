/***************************************************************************
 *            nc_multiplicity_func_tinker.h
 *
 *  Mon Jun 28 15:09:13 2010
 *  Copyright  2010  Mariana Penna Lima
 *  <pennalima@gmail.com>
 ****************************************************************************/
/*
 * numcosmo
 * Copyright (C) Mariana Penna Lima 2012 <pennalima@gmail.com>
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

#ifndef _NC_MULTIPLICITY_FUNC_TINKER_H_
#define _NC_MULTIPLICITY_FUNC_TINKER_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define NC_TYPE_MULTIPLICITY_FUNC_TINKER             (nc_multiplicity_func_tinker_get_type ())
#define NC_MULTIPLICITY_FUNC_TINKER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), NC_TYPE_MULTIPLICITY_FUNC_TINKER, NcMultiplicityFuncTinker))
#define NC_MULTIPLICITY_FUNC_TINKER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), NC_TYPE_MULTIPLICITY_FUNC_TINKER, NcMultiplicityFuncTinkerClass))
#define NC_IS_MULTIPLICITY_FUNC_TINKER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NC_TYPE_MULTIPLICITY_FUNC_TINKER))
#define NC_IS_MULTIPLICITY_FUNC_TINKER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), NC_TYPE_MULTIPLICITY_FUNC_TINKER))
#define NC_MULTIPLICITY_FUNC_TINKER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), NC_TYPE_MULTIPLICITY_FUNC_TINKER, NcMultiplicityFuncTinkerClass))

typedef struct _NcMultiplicityFuncTinkerClass NcMultiplicityFuncTinkerClass;
typedef struct _NcMultiplicityFuncTinker NcMultiplicityFuncTinker;



struct _NcMultiplicityFuncTinkerClass
{
  /*< private >*/
  NcMultiplicityFuncClass parent_class;
};

struct _NcMultiplicityFuncTinker
{
  /*< private >*/
  NcMultiplicityFunc parent_instance;
  gdouble A0;
  gdouble a0;
  gdouble b0;
  gdouble c;
  gdouble Delta;
};

GType nc_multiplicity_func_tinker_get_type (void) G_GNUC_CONST;

NcMultiplicityFunc *nc_multiplicity_func_tinker_new (gdouble A0, gdouble a0, gdouble b0, gdouble c, gdouble Delta);
void nc_multiplicity_func_tinker_set_A0 (NcMultiplicityFuncTinker *mulf_tinker, gdouble A0);
gdouble nc_multiplicity_func_tinker_get_A0 (const NcMultiplicityFuncTinker *mulf_tinker);
void nc_multiplicity_func_tinker_set_a0 (NcMultiplicityFuncTinker *mulf_tinker, gdouble a0);
gdouble nc_multiplicity_func_tinker_get_a0 (const NcMultiplicityFuncTinker *mulf_tinker);
void nc_multiplicity_func_tinker_set_b0 (NcMultiplicityFuncTinker *mulf_tinker, gdouble b0);
gdouble nc_multiplicity_func_tinker_get_b0 (const NcMultiplicityFuncTinker *mulf_tinker);
void nc_multiplicity_func_tinker_set_c (NcMultiplicityFuncTinker *mulf_tinker, gdouble c);
gdouble nc_multiplicity_func_tinker_get_c (const NcMultiplicityFuncTinker *mulf_tinker);
void nc_multiplicity_func_tinker_set_Delta (NcMultiplicityFuncTinker *mulf_tinker, gdouble Delta);
gdouble nc_multiplicity_func_tinker_get_Delta (const NcMultiplicityFuncTinker *mulf_tinker);

G_END_DECLS

#endif /* _NC_MULTIPLICITY_FUNC_TINKER_H_ */