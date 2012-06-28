/***************************************************************************
 *            de_options.h
 *
 *  Sat Apr 24 14:40:43 2010
 *  Copyright  2010  Sandro Dias Pinto Vitenti
 *  <sandro@isoftware.com.br>
 ****************************************************************************/
/*
 * numcosmo
 * Copyright (C) Sandro Dias Pinto Vitenti 2012 <sandro@isoftware.com.br>
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

typedef struct _NcDEModelEntries NcDEModelEntries;

/**
 * NcDEModelEntries:
 *
 * FIXME
 */
struct _NcDEModelEntries
{
  gchar *model_name;
  gdouble H0;
  gdouble Omega_c;
  gdouble Omega_x;
  gdouble Omega_b;
  gdouble T_gamma;
  gdouble n_s;
  gdouble sigma_8;
  gdouble w[3];
  gboolean plane;
  gboolean Omega_k;
  gboolean help_names;
};

#define NC_DE_MODEL_ENTRIES {"NcHICosmoDEXcdm", 70.0, 0.25, 0.7, 0.05, 2.726, 1.0, 0.9, {-1.0, 0.0, 0.0}, FALSE, FALSE, FALSE }

typedef struct _NcDEDataSimpleEntries NcDEDataSimpleEntries;

/**
 * NcDEDataSimpleEntries:
 *
 * FIXME
 */
struct _NcDEDataSimpleEntries
{
  gint snia_id;
  gint bao_id;
  gint cmb_id;
  gint H_id;
  gint cluster_id;
  gboolean H0_Hst;
  gboolean BBN;
};

#define NC_DE_DATA_SIMPLE_ENTRIES {-1, -1, -1, -1, -1, FALSE, FALSE}

typedef struct _NcDEDataClusterEntries NcDEDataClusterEntries;

/**
 * NcDEDataNcusterEntries:
 *
 * FIXME
 */
struct _NcDEDataClusterEntries
{
  gchar *window_name;
  gchar *transfer_name;
  gchar *multiplicity_name;
  gchar *clusterm_ser;
  gchar *clusterz_ser;
  gint mf_ds_index;    /* refers to the multiplicity function */
  gboolean use_true_data;
  gboolean binned;
  gboolean use_photoz;
  gboolean binmass;
  gboolean use_Mobs;
  gboolean use_Mobs_local; /* sigma_lnM varies with z and lnM. (matching catalog)*/
  gboolean use_selection; /* selection function = completeness / purity (matching catalog) */
  gdouble Mi;
  gdouble Mf;
  gdouble area_survey;
  gdouble z_initial;
  gdouble z_final;
  gdouble photoz_sigma0;
  gdouble photoz_bias;
  gdouble lnM_sigma0;
  gdouble lnM_bias;
  gint n_bins;
  gchar **cata_file;
  gchar *save_cata;
  gboolean print_mass_function;
};

#define NC_DE_DATA_CLUSTER_ENTRIES {"NcWindowTophat", "NcTransferFuncEH", "NcMultiplicityFuncTinkerMean", "NcClusterMassNodist", "NcClusterRedshiftNodist", 0, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 5.0e13, 1.0e16, 5000.0, 0.0, 1.4, 0.03, 0.0, 0.2, 0.0, 10, NULL, NULL, FALSE}

typedef struct _NcDEFitEntries NcDEFitEntries;

/**
 * NcDEFitEntries:
 *
 * FIXME
 */
struct _NcDEFitEntries
{
  gchar *file_out;
  gint min_algo;
  gint diff_algo;
  gint nsigma;
  gint nsigma_fisher;
  gint bidim_cr[2];
  gchar **onedim_cr;
  gchar *fit_params;
  gint max_iter;
  gboolean resample;
  gint msg_level;
  gint montecarlo;
  gint mc_ni;
  gboolean fiducial;
  gboolean mc_data;
  gboolean fit;
  gboolean fisher;
  gboolean save_fisher;
  gboolean save_best_fit;
};

#ifdef NUMCOSMO_HAVE_NLOPT
#define NC_DE_FIT_ENTRIES { NULL, NCM_FIT_TYPE_NLOPT_LN_NELDERMEAD, NCM_FIT_GRAD_NUMDIFF_FORWARD, -1, -1, {-1, -1}, NULL, NULL, NC_BF_MAX_ITER, FALSE, NCM_FIT_RUN_MSGS_SIMPLE, -1, 0, FALSE, FALSE, FALSE, FALSE, FALSE}
#else
#define NC_DE_FIT_ENTRIES { NULL, NCM_FIT_TYPE_SIMPLEX,             NCM_FIT_GRAD_NUMDIFF_FORWARD, -1, -1, {-1, -1}, NULL, NULL, NC_BF_MAX_ITER, FALSE, NCM_FIT_RUN_MSGS_SIMPLE, -1, 0, FALSE, FALSE, FALSE, FALSE, FALSE}
#endif

GOptionGroup *nc_de_opt_get_model_group (NcDEModelEntries *de_model);
GOptionGroup *nc_de_opt_get_data_simple_group (NcDEDataSimpleEntries *de_data_simple);
GOptionGroup *nc_de_opt_get_data_cluster_group (NcDEDataClusterEntries *de_data_cluster);
GOptionGroup *nc_de_opt_get_fit_group (NcDEFitEntries *de_fit_group);