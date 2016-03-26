/***************************************************************************
 *            ncm_mset_catalog.h
 *
 *  Tue February 18 10:49:59 2014
 *  Copyright  2014  Sandro Dias Pinto Vitenti
 *  <sandro@isoftware.com.br>
 ****************************************************************************/
/*
 * ncm_mset_catalog.h
 * Copyright (C) 2014 Sandro Dias Pinto Vitenti <sandro@isoftware.com.br>
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

#ifndef _NCM_MSET_CATALOG_H_
#define _NCM_MSET_CATALOG_H_

#include <glib.h>
#include <glib-object.h>
#include <numcosmo/build_cfg.h>
#include <numcosmo/math/ncm_fit.h>
#include <numcosmo/math/ncm_stats_vec.h>
#include <numcosmo/math/ncm_stats_dist1d_epdf.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_vector_complex.h>
#ifdef NUMCOSMO_HAVE_CFITSIO
#include <fitsio.h>
#endif /* NUMCOSMO_HAVE_CFITSIO */

G_BEGIN_DECLS

#define NCM_TYPE_MSET_CATALOG             (ncm_mset_catalog_get_type ())
#define NCM_MSET_CATALOG(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), NCM_TYPE_MSET_CATALOG, NcmMSetCatalog))
#define NCM_MSET_CATALOG_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), NCM_TYPE_MSET_CATALOG, NcmMSetCatalogClass))
#define NCM_IS_MSET_CATALOG(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NCM_TYPE_MSET_CATALOG))
#define NCM_IS_MSET_CATALOG_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), NCM_TYPE_MSET_CATALOG))
#define NCM_MSET_CATALOG_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), NCM_TYPE_MSET_CATALOG, NcmMSetCatalogClass))

typedef struct _NcmMSetCatalogClass NcmMSetCatalogClass;
typedef struct _NcmMSetCatalog NcmMSetCatalog;

/**
 * NcmMSetCatalogSync:
 * @NCM_MSET_CATALOG_SYNC_DISABLE: Catalog will be synchronized only when closing the file or with an explicit call of ncm_mset_catalog_sync().
 * @NCM_MSET_CATALOG_SYNC_AUTO: Catalog will be synchronized in every catalog addition.
 * @NCM_MSET_CATALOG_SYNC_TIMED: Catalog will be synchronized with a minimum time interval between syncs.
 * 
 * Catalog sync modes. 
 * 
 */
typedef enum _NcmMSetCatalogSync
{
  NCM_MSET_CATALOG_SYNC_DISABLE,
  NCM_MSET_CATALOG_SYNC_AUTO,
  NCM_MSET_CATALOG_SYNC_TIMED, /*< private >*/
  NCM_MSET_CATALOG_SYNC_LEN,   /*< skip >*/
} NcmMSetCatalogSync;

struct _NcmMSetCatalog
{
  /*< private >*/
  GObject parent_instance;
  NcmMSet *mset;
  guint nadd_vals;
  GPtrArray *add_vals_names;
  NcmStatsVec *pstats;
  NcmMSetCatalogSync smode;
  gboolean readonly;
  NcmRNG *rng;
  gboolean weighted;
  gboolean first_flush;
  guint nchains;
  GPtrArray *chain_pstats;
  NcmStatsVec *mean_pstats;
  NcmStatsVec *e_stats;
  GPtrArray *e_mean_array;
  GPtrArray *e_var_array;
  NcmVector *chain_means;
  NcmVector *chain_vars;
  NcmMatrix *chain_cov;
  NcmMatrix *chain_sM;
  gsl_eigen_nonsymm_workspace *chain_sM_ws;
  gsl_vector_complex *chain_sM_ev;
  NcmVector *tau;
  gchar *rng_inis;
  gchar *rng_stat;
  GTimer *sync_timer;
  gdouble sync_interval;
  gchar *file;
  gchar *mset_file;
  gchar *rtype_str;
  GArray *porder;
  NcmVector *quantile_ws;
  gint first_id;
  gint cur_id;
  gint file_first_id;
  gint file_cur_id;
  glong burnin;
#ifdef NUMCOSMO_HAVE_CFITSIO
  fitsfile *fptr;
#endif /* NUMCOSMO_HAVE_CFITSIO */
  NcmVector *params_max;
  NcmVector *params_min;
  glong pdf_i;
  gsl_histogram *h;
  gsl_histogram_pdf *h_pdf;
  gboolean constructed;
};

struct _NcmMSetCatalogClass
{
  /*< private >*/
  GObjectClass parent_class;
};

GType ncm_mset_catalog_get_type (void) G_GNUC_CONST;

NcmMSetCatalog *ncm_mset_catalog_new (NcmMSet *mset, guint nadd_vals, guint nchains, gboolean weighted, ...);
NcmMSetCatalog *ncm_mset_catalog_new_from_file (const gchar *filename, glong burnin);
NcmMSetCatalog *ncm_mset_catalog_new_from_file_ro (const gchar *filename, glong burnin);
NcmMSetCatalog *ncm_mset_catalog_ref (NcmMSetCatalog *mcat);
void ncm_mset_catalog_free (NcmMSetCatalog *mcat);
void ncm_mset_catalog_clear (NcmMSetCatalog **mcat);

void ncm_mset_catalog_set_add_val_name (NcmMSetCatalog *mcat, guint i, const gchar *name);
void ncm_mset_catalog_set_file (NcmMSetCatalog *mcat, const gchar *filename);
void ncm_mset_catalog_set_sync_mode (NcmMSetCatalog *mcat, NcmMSetCatalogSync smode);
void ncm_mset_catalog_set_sync_interval (NcmMSetCatalog *mcat, gdouble interval);
void ncm_mset_catalog_set_first_id (NcmMSetCatalog *mcat, gint first_id);
void ncm_mset_catalog_set_run_type (NcmMSetCatalog *mcat, const gchar *rtype_str);
void ncm_mset_catalog_set_rng (NcmMSetCatalog *mcat, NcmRNG *rng);
void ncm_mset_catalog_sync (NcmMSetCatalog *mcat, gboolean check);
void ncm_mset_catalog_timed_sync (NcmMSetCatalog *mcat, gboolean check);
void ncm_mset_catalog_reset_stats (NcmMSetCatalog *mcat);
void ncm_mset_catalog_reset (NcmMSetCatalog *mcat);
void ncm_mset_catalog_erase_data (NcmMSetCatalog *mcat);

const gchar *ncm_mset_catalog_peek_filename (NcmMSetCatalog *mcat);
NcmRNG *ncm_mset_catalog_get_rng (NcmMSetCatalog *mcat);

gboolean ncm_mset_catalog_is_empty (NcmMSetCatalog *mcat);
gdouble ncm_mset_catalog_largest_error (NcmMSetCatalog *mcat);
guint ncm_mset_catalog_len (NcmMSetCatalog *mcat);
guint ncm_mset_catalog_max_time (NcmMSetCatalog *mcat);

void ncm_mset_catalog_set_burnin (NcmMSetCatalog *mcat, glong burnin);
glong ncm_mset_catalog_get_burnin (NcmMSetCatalog *mcat);

void ncm_mset_catalog_add_from_mset (NcmMSetCatalog *mcat, NcmMSet *mset, ...);
void ncm_mset_catalog_add_from_mset_array (NcmMSetCatalog *mcat, NcmMSet *mset, gdouble *ax);
void ncm_mset_catalog_add_from_vector (NcmMSetCatalog *mcat, NcmVector *vals);
void ncm_mset_catalog_log_current_stats (NcmMSetCatalog *mcat);
void ncm_mset_catalog_log_current_chain_stats (NcmMSetCatalog *mcat);

NcmMSet *ncm_mset_catalog_get_mset (NcmMSetCatalog *mcat);
const gchar *ncm_mset_catalog_get_run_type (NcmMSetCatalog *mcat);

NcmVector *ncm_mset_catalog_peek_row (NcmMSetCatalog *mcat, guint i);
NcmVector *ncm_mset_catalog_peek_current_row (NcmMSetCatalog *mcat);
NcmVector *ncm_mset_catalog_peek_current_e_mean (NcmMSetCatalog *mcat);
NcmVector *ncm_mset_catalog_peek_current_e_var (NcmMSetCatalog *mcat);
NcmVector *ncm_mset_catalog_peek_e_mean_t (NcmMSetCatalog *mcat, guint t);
NcmVector *ncm_mset_catalog_peek_e_var_t (NcmMSetCatalog *mcat, guint t);

void ncm_mset_catalog_get_mean (NcmMSetCatalog *mcat, NcmVector  **mean);
void ncm_mset_catalog_get_covar (NcmMSetCatalog *mcat, NcmMatrix **cov);

void ncm_mset_catalog_estimate_autocorrelation_tau (NcmMSetCatalog *mcat);
NcmVector *ncm_mset_catalog_peek_autocorrelation_tau (NcmMSetCatalog *mcat);
gdouble ncm_mset_catalog_get_param_shrink_factor (NcmMSetCatalog *mcat, guint p);
gdouble ncm_mset_catalog_get_shrink_factor (NcmMSetCatalog *mcat);

void ncm_mset_catalog_param_pdf (NcmMSetCatalog *mcat, guint i);
gdouble ncm_mset_catalog_param_pdf_pvalue (NcmMSetCatalog *mcat, gdouble pval, gboolean both);

NcmMatrix *ncm_mset_catalog_calc_ci_direct (NcmMSetCatalog *mcat, NcmMSetFunc *func, gdouble *x, GArray *p_val);
NcmMatrix *ncm_mset_catalog_calc_ci_interp (NcmMSetCatalog *mcat, NcmMSetFunc *func, gdouble *x, GArray *p_val, guint nodes, NcmFitRunMsgs mtype);
NcmStatsDist1d *ncm_mset_catalog_calc_distrib (NcmMSetCatalog *mcat, NcmMSetFunc *func, NcmFitRunMsgs mtype);
NcmStatsDist1d *ncm_mset_catalog_calc_param_distrib (NcmMSetCatalog *mcat, const NcmMSetPIndex *pi, NcmFitRunMsgs mtype);
NcmStatsDist1d *ncm_mset_catalog_calc_add_param_distrib (NcmMSetCatalog *mcat, guint add_param, NcmFitRunMsgs mtype);

void ncm_mset_catalog_calc_param_ensemble_evol (NcmMSetCatalog *mcat, const NcmMSetPIndex *pi, guint nsteps, NcmFitRunMsgs mtype, NcmVector **pval, NcmMatrix **t_evol);
void ncm_mset_catalog_calc_add_param_ensemble_evol (NcmMSetCatalog *mcat, guint add_param, guint nsteps, NcmFitRunMsgs mtype, NcmVector **pval, NcmMatrix **t_evol);

#define NCM_MSET_CATALOG_EXTNAME "NcmMSetCatalog:DATA"
#define NCM_MSET_CATALOG_M2LNL_COLNAME "NcmFit:m2lnL"
#define NCM_MSET_CATALOG_FIRST_ID_LABEL "FIRST_ID"
#define NCM_MSET_CATALOG_RNG_ALGO_LABEL "RNG_ALGO"
#define NCM_MSET_CATALOG_RNG_SEED_LABEL "RNG_SEED"
#define NCM_MSET_CATALOG_RNG_STAT_LABEL "RNG_STAT"
#define NCM_MSET_CATALOG_RNG_INIS_LABEL "RNG_INIS"
#define NCM_MSET_CATALOG_NROWS_LABEL "NAXIS2"
#define NCM_MSET_CATALOG_RTYPE_LABEL "RTYPE"
#define NCM_MSET_CATALOG_NCHAINS_LABEL "NCHAINS"
#define NCM_MSET_CATALOG_NADDVAL_LABEL "NADDVAL"
#define NCM_MSET_CATALOG_WEIGHTED_LABEL "WEIGHTED"
#define NCM_MSET_CATALOG_RTYPE_BSTRAP_MEAN "bootstrap-mean"
#define NCM_MSET_CATALOG_RTYPE_UNDEFINED "undefined-run"
#define NCM_MSET_CATALOG_FSYMB_LABEL "FSYMB"

G_END_DECLS

#endif /* _NCM_MSET_CATALOG_H_ */

