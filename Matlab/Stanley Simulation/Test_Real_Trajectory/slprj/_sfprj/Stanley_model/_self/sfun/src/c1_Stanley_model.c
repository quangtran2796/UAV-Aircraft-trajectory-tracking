/* Include files */

#include "blascompat32.h"
#include "Stanley_model_sfun.h"
#include "c1_Stanley_model.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Stanley_model_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[29] = { "line", "perpen_vct1",
  "perpen_vct2", "vct_d1", "vct_d2", "x", "phi", "d", "nargin", "nargout",
  "slope", "start_index", "tra_x", "tra_y", "v", "k", "init_pos", "init_angle",
  "rec_index", "recX", "recY", "rec_times", "rec_angle", "cur_index", "curX",
  "curY", "cur_times", "cur_angle", "val" };

/* Function Declarations */
static void initialize_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance);
static void initialize_params_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct *
  chartInstance);
static void enable_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance);
static void disable_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance);
static void c1_update_debugger_state_c1_Stanley_model
  (SFc1_Stanley_modelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_Stanley_model
  (SFc1_Stanley_modelInstanceStruct *chartInstance);
static void set_sim_state_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_st);
static void finalize_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance);
static void sf_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct *chartInstance);
static void c1_chartstep_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance);
static void initSimStructsc1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_val, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_c_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[2]);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[24]);
static real_T c1_mpower(SFc1_Stanley_modelInstanceStruct *chartInstance, real_T
  c1_a);
static void c1_eml_error(SFc1_Stanley_modelInstanceStruct *chartInstance);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_d_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_e_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_Stanley_model, const char_T
  *c1_identifier);
static uint8_T c1_f_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_Stanley_modelInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_Stanley_model = 0U;
}

static void initialize_params_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct *
  chartInstance)
{
}

static void enable_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_Stanley_model
  (SFc1_Stanley_modelInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c1_Stanley_model
  (SFc1_Stanley_modelInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_d_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_e_hoistedGlobal;
  real_T c1_e_u;
  const mxArray *c1_f_y = NULL;
  real_T c1_f_hoistedGlobal;
  real_T c1_f_u;
  const mxArray *c1_g_y = NULL;
  uint8_T c1_g_hoistedGlobal;
  uint8_T c1_g_u;
  const mxArray *c1_h_y = NULL;
  real_T *c1_curX;
  real_T *c1_curY;
  real_T *c1_cur_angle;
  real_T *c1_cur_index;
  real_T *c1_cur_times;
  real_T *c1_val;
  c1_val = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c1_cur_angle = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c1_cur_times = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_curY = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_curX = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_cur_index = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(7), FALSE);
  c1_hoistedGlobal = *c1_curX;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *c1_curY;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = *c1_cur_angle;
  c1_c_u = c1_c_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = *c1_cur_index;
  c1_d_u = c1_d_hoistedGlobal;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_e_hoistedGlobal = *c1_cur_times;
  c1_e_u = c1_e_hoistedGlobal;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_f_hoistedGlobal = *c1_val;
  c1_f_u = c1_f_hoistedGlobal;
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_f_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_g_hoistedGlobal = chartInstance->c1_is_active_c1_Stanley_model;
  c1_g_u = c1_g_hoistedGlobal;
  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_g_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 6, c1_h_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T *c1_curX;
  real_T *c1_curY;
  real_T *c1_cur_angle;
  real_T *c1_cur_index;
  real_T *c1_cur_times;
  real_T *c1_val;
  c1_val = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c1_cur_angle = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c1_cur_times = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_curY = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_curX = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_cur_index = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_curX = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    0)), "curX");
  *c1_curY = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    1)), "curY");
  *c1_cur_angle = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 2)), "cur_angle");
  *c1_cur_index = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 3)), "cur_index");
  *c1_cur_times = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 4)), "cur_times");
  *c1_val = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 5)),
    "val");
  chartInstance->c1_is_active_c1_Stanley_model = c1_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 6)),
     "is_active_c1_Stanley_model");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_Stanley_model(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance)
{
}

static void sf_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct *chartInstance)
{
  int32_T c1_i0;
  int32_T c1_i1;
  int32_T c1_i2;
  int32_T c1_i3;
  real_T *c1_cur_index;
  real_T *c1_curX;
  real_T *c1_curY;
  real_T *c1_cur_times;
  real_T *c1_start_index;
  real_T *c1_v;
  real_T *c1_k;
  real_T *c1_init_angle;
  real_T *c1_rec_index;
  real_T *c1_recX;
  real_T *c1_recY;
  real_T *c1_rec_times;
  real_T *c1_rec_angle;
  real_T *c1_cur_angle;
  real_T *c1_val;
  real_T (*c1_init_pos)[2];
  real_T (*c1_tra_y)[8];
  real_T (*c1_tra_x)[8];
  real_T (*c1_slope)[7];
  c1_val = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c1_cur_angle = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c1_rec_angle = (real_T *)ssGetInputPortSignal(chartInstance->S, 12);
  c1_rec_times = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
  c1_recY = (real_T *)ssGetInputPortSignal(chartInstance->S, 10);
  c1_recX = (real_T *)ssGetInputPortSignal(chartInstance->S, 9);
  c1_rec_index = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
  c1_init_angle = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
  c1_init_pos = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 6);
  c1_k = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c1_v = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c1_tra_y = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 3);
  c1_tra_x = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 2);
  c1_start_index = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_cur_times = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_slope = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 0);
  c1_curY = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_curX = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_cur_index = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c1_cur_index, 0U);
  _SFD_DATA_RANGE_CHECK(*c1_curX, 1U);
  _SFD_DATA_RANGE_CHECK(*c1_curY, 2U);
  for (c1_i0 = 0; c1_i0 < 7; c1_i0++) {
    _SFD_DATA_RANGE_CHECK((*c1_slope)[c1_i0], 3U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_cur_times, 4U);
  _SFD_DATA_RANGE_CHECK(*c1_start_index, 5U);
  for (c1_i1 = 0; c1_i1 < 8; c1_i1++) {
    _SFD_DATA_RANGE_CHECK((*c1_tra_x)[c1_i1], 6U);
  }

  for (c1_i2 = 0; c1_i2 < 8; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((*c1_tra_y)[c1_i2], 7U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_v, 8U);
  _SFD_DATA_RANGE_CHECK(*c1_k, 9U);
  for (c1_i3 = 0; c1_i3 < 2; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((*c1_init_pos)[c1_i3], 10U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_init_angle, 11U);
  _SFD_DATA_RANGE_CHECK(*c1_rec_index, 12U);
  _SFD_DATA_RANGE_CHECK(*c1_recX, 13U);
  _SFD_DATA_RANGE_CHECK(*c1_recY, 14U);
  _SFD_DATA_RANGE_CHECK(*c1_rec_times, 15U);
  _SFD_DATA_RANGE_CHECK(*c1_rec_angle, 16U);
  _SFD_DATA_RANGE_CHECK(*c1_cur_angle, 17U);
  _SFD_DATA_RANGE_CHECK(*c1_val, 18U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_Stanley_model(chartInstance);
  sf_debug_check_for_state_inconsistency(_Stanley_modelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance)
{
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_hoistedGlobal;
  real_T c1_d_hoistedGlobal;
  real_T c1_e_hoistedGlobal;
  real_T c1_f_hoistedGlobal;
  real_T c1_g_hoistedGlobal;
  real_T c1_h_hoistedGlobal;
  real_T c1_i_hoistedGlobal;
  int32_T c1_i4;
  real_T c1_slope[7];
  real_T c1_start_index;
  int32_T c1_i5;
  real_T c1_tra_x[8];
  int32_T c1_i6;
  real_T c1_tra_y[8];
  real_T c1_v;
  real_T c1_k;
  int32_T c1_i7;
  real_T c1_init_pos[2];
  real_T c1_init_angle;
  real_T c1_rec_index;
  real_T c1_recX;
  real_T c1_recY;
  real_T c1_rec_times;
  real_T c1_rec_angle;
  uint32_T c1_debug_family_var_map[29];
  real_T c1_line;
  real_T c1_perpen_vct1;
  real_T c1_perpen_vct2;
  real_T c1_vct_d1;
  real_T c1_vct_d2;
  real_T c1_x;
  real_T c1_phi;
  real_T c1_d[2];
  real_T c1_nargin = 13.0;
  real_T c1_nargout = 6.0;
  real_T c1_cur_index;
  real_T c1_curX;
  real_T c1_curY;
  real_T c1_cur_times;
  real_T c1_cur_angle;
  real_T c1_val;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_a;
  real_T c1_b;
  real_T c1_y;
  real_T c1_b_a;
  real_T c1_b_y;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_c_a;
  real_T c1_b_b;
  real_T c1_c_y;
  real_T c1_d_a;
  real_T c1_d_y;
  real_T c1_e_a;
  real_T c1_c_b;
  real_T c1_e_y;
  real_T c1_f_a;
  real_T c1_d_b;
  real_T c1_f_y;
  real_T c1_g_a;
  real_T c1_e_b;
  real_T c1_g_y;
  real_T c1_h_a;
  real_T c1_f_b;
  real_T c1_h_y;
  real_T c1_i_a;
  real_T c1_g_b;
  real_T c1_j_a;
  real_T c1_h_b;
  real_T c1_i_y;
  real_T c1_k_a;
  real_T c1_i_b;
  real_T c1_j_y;
  real_T c1_l_a;
  real_T c1_j_b;
  real_T c1_k_y;
  real_T c1_m_a;
  real_T c1_k_b;
  real_T c1_n_a;
  real_T c1_l_b;
  real_T c1_l_y;
  real_T c1_o_a;
  real_T c1_m_b;
  real_T c1_m_y;
  real_T c1_f_x;
  real_T c1_g_x;
  real_T c1_n_y;
  real_T c1_h_x;
  real_T c1_i_x;
  real_T c1_A;
  real_T c1_B;
  real_T c1_j_x;
  real_T c1_o_y;
  real_T c1_k_x;
  real_T c1_p_y;
  real_T c1_l_x;
  real_T c1_m_x;
  real_T c1_p_a;
  real_T c1_n_b;
  real_T c1_q_y;
  real_T c1_b_A;
  real_T c1_b_B;
  real_T c1_n_x;
  real_T c1_r_y;
  real_T c1_o_x;
  real_T c1_s_y;
  real_T c1_t_y;
  real_T c1_p_x;
  real_T c1_q_x;
  real_T c1_q_a;
  real_T c1_o_b;
  real_T c1_u_y;
  real_T c1_r_x;
  real_T c1_s_x;
  real_T c1_r_a;
  real_T c1_p_b;
  real_T c1_v_y;
  real_T c1_c_A;
  real_T c1_c_B;
  real_T c1_t_x;
  real_T c1_w_y;
  real_T c1_u_x;
  real_T c1_x_y;
  real_T c1_y_y;
  real_T c1_v_x;
  real_T c1_w_x;
  real_T c1_s_a;
  real_T c1_q_b;
  real_T c1_ab_y;
  real_T c1_x_x;
  real_T c1_y_x;
  real_T c1_t_a;
  real_T c1_r_b;
  real_T c1_bb_y;
  real_T c1_u_a;
  real_T c1_cb_y;
  real_T c1_ab_x;
  real_T c1_bb_x;
  real_T c1_v_a;
  real_T c1_s_b;
  real_T c1_db_y;
  real_T c1_w_a;
  real_T c1_eb_y;
  int32_T c1_i8;
  real_T c1_cb_x;
  real_T c1_db_x;
  real_T c1_eb_x;
  real_T c1_fb_x;
  real_T c1_d_A;
  real_T c1_d_B;
  real_T c1_gb_x;
  real_T c1_fb_y;
  real_T c1_hb_x;
  real_T c1_gb_y;
  real_T c1_hb_y;
  real_T *c1_b_val;
  real_T *c1_b_cur_angle;
  real_T *c1_b_cur_times;
  real_T *c1_b_curY;
  real_T *c1_b_curX;
  real_T *c1_b_cur_index;
  real_T *c1_b_rec_angle;
  real_T *c1_b_rec_times;
  real_T *c1_b_recY;
  real_T *c1_b_recX;
  real_T *c1_b_rec_index;
  real_T *c1_b_init_angle;
  real_T *c1_b_k;
  real_T *c1_b_v;
  real_T *c1_b_start_index;
  real_T (*c1_b_init_pos)[2];
  real_T (*c1_b_tra_y)[8];
  real_T (*c1_b_tra_x)[8];
  real_T (*c1_b_slope)[7];
  boolean_T guard1 = FALSE;
  c1_b_val = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c1_b_cur_angle = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c1_b_rec_angle = (real_T *)ssGetInputPortSignal(chartInstance->S, 12);
  c1_b_rec_times = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
  c1_b_recY = (real_T *)ssGetInputPortSignal(chartInstance->S, 10);
  c1_b_recX = (real_T *)ssGetInputPortSignal(chartInstance->S, 9);
  c1_b_rec_index = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
  c1_b_init_angle = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
  c1_b_init_pos = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 6);
  c1_b_k = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c1_b_v = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c1_b_tra_y = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 3);
  c1_b_tra_x = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 2);
  c1_b_start_index = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_cur_times = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_b_slope = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 0);
  c1_b_curY = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_b_curX = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_b_cur_index = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *c1_b_start_index;
  c1_b_hoistedGlobal = *c1_b_v;
  c1_c_hoistedGlobal = *c1_b_k;
  c1_d_hoistedGlobal = *c1_b_init_angle;
  c1_e_hoistedGlobal = *c1_b_rec_index;
  c1_f_hoistedGlobal = *c1_b_recX;
  c1_g_hoistedGlobal = *c1_b_recY;
  c1_h_hoistedGlobal = *c1_b_rec_times;
  c1_i_hoistedGlobal = *c1_b_rec_angle;
  for (c1_i4 = 0; c1_i4 < 7; c1_i4++) {
    c1_slope[c1_i4] = (*c1_b_slope)[c1_i4];
  }

  c1_start_index = c1_hoistedGlobal;
  for (c1_i5 = 0; c1_i5 < 8; c1_i5++) {
    c1_tra_x[c1_i5] = (*c1_b_tra_x)[c1_i5];
  }

  for (c1_i6 = 0; c1_i6 < 8; c1_i6++) {
    c1_tra_y[c1_i6] = (*c1_b_tra_y)[c1_i6];
  }

  c1_v = c1_b_hoistedGlobal;
  c1_k = c1_c_hoistedGlobal;
  for (c1_i7 = 0; c1_i7 < 2; c1_i7++) {
    c1_init_pos[c1_i7] = (*c1_b_init_pos)[c1_i7];
  }

  c1_init_angle = c1_d_hoistedGlobal;
  c1_rec_index = c1_e_hoistedGlobal;
  c1_recX = c1_f_hoistedGlobal;
  c1_recY = c1_g_hoistedGlobal;
  c1_rec_times = c1_h_hoistedGlobal;
  c1_rec_angle = c1_i_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 29U, 29U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_line, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_perpen_vct1, 1U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_perpen_vct2, 2U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_vct_d1, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_vct_d2, 4U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_x, 5U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_phi, 6U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_d, 7U, c1_e_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 8U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 9U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c1_slope, 10U, c1_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_start_index, 11U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c1_tra_x, 12U, c1_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c1_tra_y, 13U, c1_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_v, 14U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_k, 15U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c1_init_pos, 16U, c1_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_init_angle, 17U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_rec_index, 18U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_recX, 19U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_recY, 20U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_rec_times, 21U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_rec_angle, 22U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_cur_index, 23U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_curX, 24U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_curY, 25U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_cur_times, 26U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_cur_angle, 27U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_val, 28U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 2);
  if (CV_EML_IF(0, 1, 0, c1_rec_index > 7.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 3);
    c1_cur_index = c1_rec_index;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
    c1_cur_angle = c1_rec_angle;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 5);
    c1_b_x = c1_cur_angle;
    c1_c_x = c1_b_x;
    c1_c_x = muDoubleScalarCos(c1_c_x);
    c1_a = c1_v;
    c1_b = c1_c_x;
    c1_y = c1_a * c1_b;
    c1_b_a = c1_y;
    c1_b_y = c1_b_a * 0.05;
    c1_curX = c1_recX + c1_b_y;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
    c1_d_x = c1_cur_angle;
    c1_e_x = c1_d_x;
    c1_e_x = muDoubleScalarSin(c1_e_x);
    c1_c_a = c1_v;
    c1_b_b = c1_e_x;
    c1_c_y = c1_c_a * c1_b_b;
    c1_d_a = c1_c_y;
    c1_d_y = c1_d_a * 0.05;
    c1_curY = c1_recY + c1_d_y;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
    c1_cur_times = c1_rec_times + 1.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
    c1_line = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
    c1_val = 0.0;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
    if (CV_EML_IF(0, 1, 1, c1_rec_times == 0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
      c1_recX = c1_init_pos[0];
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
      c1_recY = c1_init_pos[1];
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
      c1_rec_index = c1_start_index;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
      c1_rec_angle = c1_init_angle;
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
    c1_perpen_vct1 = c1_tra_x[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_x", (int32_T)
      _SFD_INTEGER_CHECK("rec_index + 1", c1_rec_index + 1.0), 1, 8, 1, 0) - 1]
      - c1_tra_x[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_x", (int32_T)
      _SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 8, 1, 0) - 1];
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 17);
    c1_perpen_vct2 = c1_tra_y[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_y", (int32_T)
      _SFD_INTEGER_CHECK("rec_index + 1", c1_rec_index + 1.0), 1, 8, 1, 0) - 1]
      - c1_tra_y[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_y", (int32_T)
      _SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 8, 1, 0) - 1];
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 18);
    c1_vct_d1 = c1_tra_x[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_x", (int32_T)
      _SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 8, 1, 0) - 1] - c1_recX;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
    c1_vct_d2 = c1_tra_y[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_y", (int32_T)
      _SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 8, 1, 0) - 1] - c1_recY;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 21);
    if (CV_EML_IF(0, 1, 2, -c1_perpen_vct1 != 0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
      c1_e_a = c1_perpen_vct2;
      c1_c_b = c1_recX;
      c1_e_y = c1_e_a * c1_c_b;
      c1_f_a = c1_perpen_vct1;
      c1_d_b = c1_recY;
      c1_f_y = c1_f_a * c1_d_b;
      c1_g_a = c1_perpen_vct2;
      c1_e_b = c1_tra_x[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_x", (int32_T)
        _SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 8, 1, 0) - 1];
      c1_g_y = c1_g_a * c1_e_b;
      c1_h_a = c1_perpen_vct1;
      c1_f_b = c1_tra_y[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_y", (int32_T)
        _SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 8, 1, 0) - 1];
      c1_h_y = c1_h_a * c1_f_b;
      c1_i_a = -c1_perpen_vct1;
      c1_g_b = (c1_e_y - c1_f_y) - (c1_g_y - c1_h_y);
      c1_line = c1_i_a * c1_g_b;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
      c1_j_a = c1_perpen_vct2;
      c1_h_b = c1_recX;
      c1_i_y = c1_j_a * c1_h_b;
      c1_k_a = c1_perpen_vct2;
      c1_i_b = c1_tra_x[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_x", (int32_T)
        _SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 8, 1, 0) - 1];
      c1_j_y = c1_k_a * c1_i_b;
      c1_l_a = c1_perpen_vct1;
      c1_j_b = c1_tra_y[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_y", (int32_T)
        _SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 8, 1, 0) - 1];
      c1_k_y = c1_l_a * c1_j_b;
      c1_m_a = c1_perpen_vct2;
      c1_k_b = c1_i_y - (c1_j_y - c1_k_y);
      c1_line = c1_m_a * c1_k_b;
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 27);
    c1_n_a = c1_perpen_vct2;
    c1_l_b = c1_vct_d1;
    c1_l_y = c1_n_a * c1_l_b;
    c1_o_a = c1_perpen_vct1;
    c1_m_b = c1_vct_d2;
    c1_m_y = c1_o_a * c1_m_b;
    c1_f_x = c1_l_y - c1_m_y;
    c1_g_x = c1_f_x;
    c1_n_y = muDoubleScalarAbs(c1_g_x);
    c1_h_x = c1_mpower(chartInstance, c1_perpen_vct1) + c1_mpower(chartInstance,
      c1_perpen_vct2);
    c1_i_x = c1_h_x;
    if (c1_i_x < 0.0) {
      c1_eml_error(chartInstance);
    }

    c1_i_x = muDoubleScalarSqrt(c1_i_x);
    c1_A = c1_n_y;
    c1_B = c1_i_x;
    c1_j_x = c1_A;
    c1_o_y = c1_B;
    c1_k_x = c1_j_x;
    c1_p_y = c1_o_y;
    c1_x = c1_k_x / c1_p_y;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 29);
    c1_phi = -c1_rec_angle + c1_slope[_SFD_EML_ARRAY_BOUNDS_CHECK("slope",
      (int32_T)_SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 7, 1, 0) - 1];
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 31);
    guard1 = FALSE;
    if (CV_EML_COND(0, 1, 0, c1_slope[_SFD_EML_ARRAY_BOUNDS_CHECK("slope",
          (int32_T)_SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 7, 1, 0) -
                    1] <= -1.5707963267948966)) {
      guard1 = TRUE;
    } else if (CV_EML_COND(0, 1, 1, c1_slope[_SFD_EML_ARRAY_BOUNDS_CHECK("slope",
                 (int32_T)_SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 7, 1,
      0) - 1] >= 1.5707963267948966)) {
      guard1 = TRUE;
    } else {
      CV_EML_MCDC(0, 1, 0, FALSE);
      CV_EML_IF(0, 1, 3, FALSE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 34);
      c1_r_x = c1_line;
      c1_s_x = c1_r_x;
      c1_s_x = muDoubleScalarSign(c1_s_x);
      c1_r_a = c1_k;
      c1_p_b = c1_x;
      c1_v_y = c1_r_a * c1_p_b;
      c1_c_A = c1_v_y;
      c1_c_B = c1_v;
      c1_t_x = c1_c_A;
      c1_w_y = c1_c_B;
      c1_u_x = c1_t_x;
      c1_x_y = c1_w_y;
      c1_y_y = c1_u_x / c1_x_y;
      c1_v_x = c1_y_y;
      c1_w_x = c1_v_x;
      c1_w_x = muDoubleScalarAtan(c1_w_x);
      c1_s_a = c1_s_x;
      c1_q_b = c1_w_x;
      c1_ab_y = c1_s_a * c1_q_b;
      c1_cur_angle = (c1_phi - c1_ab_y) + c1_rec_angle;
    }

    if (guard1 == TRUE) {
      CV_EML_MCDC(0, 1, 0, TRUE);
      CV_EML_IF(0, 1, 3, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
      c1_l_x = c1_line;
      c1_m_x = c1_l_x;
      c1_m_x = muDoubleScalarSign(c1_m_x);
      c1_p_a = c1_k;
      c1_n_b = c1_x;
      c1_q_y = c1_p_a * c1_n_b;
      c1_b_A = c1_q_y;
      c1_b_B = c1_v;
      c1_n_x = c1_b_A;
      c1_r_y = c1_b_B;
      c1_o_x = c1_n_x;
      c1_s_y = c1_r_y;
      c1_t_y = c1_o_x / c1_s_y;
      c1_p_x = c1_t_y;
      c1_q_x = c1_p_x;
      c1_q_x = muDoubleScalarAtan(c1_q_x);
      c1_q_a = c1_m_x;
      c1_o_b = c1_q_x;
      c1_u_y = c1_q_a * c1_o_b;
      c1_cur_angle = (c1_phi + c1_u_y) + c1_rec_angle;
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 36);
    c1_val = c1_x;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 43);
    c1_x_x = c1_cur_angle;
    c1_y_x = c1_x_x;
    c1_y_x = muDoubleScalarCos(c1_y_x);
    c1_t_a = c1_v;
    c1_r_b = c1_y_x;
    c1_bb_y = c1_t_a * c1_r_b;
    c1_u_a = c1_bb_y;
    c1_cb_y = c1_u_a * 0.05;
    c1_curX = c1_recX + c1_cb_y;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 44);
    c1_ab_x = c1_cur_angle;
    c1_bb_x = c1_ab_x;
    c1_bb_x = muDoubleScalarSin(c1_bb_x);
    c1_v_a = c1_v;
    c1_s_b = c1_bb_x;
    c1_db_y = c1_v_a * c1_s_b;
    c1_w_a = c1_db_y;
    c1_eb_y = c1_w_a * 0.05;
    c1_curY = c1_recY + c1_eb_y;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 45);
    if (CV_EML_IF(0, 1, 4, c1_rec_times != 0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 46);
      for (c1_i8 = 0; c1_i8 < 2; c1_i8++) {
        c1_d[c1_i8] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 47);
      c1_cb_x = c1_mpower(chartInstance, c1_recX -
                          c1_tra_x[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_x", (int32_T)
        _SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 8, 1, 0) - 1]) +
        c1_mpower(chartInstance, c1_recY - c1_tra_y[_SFD_EML_ARRAY_BOUNDS_CHECK(
        "tra_y", (int32_T)_SFD_INTEGER_CHECK("rec_index", c1_rec_index), 1, 8, 1,
        0) - 1]);
      c1_db_x = c1_cb_x;
      if (c1_db_x < 0.0) {
        c1_eml_error(chartInstance);
      }

      c1_db_x = muDoubleScalarSqrt(c1_db_x);
      c1_d[0] = c1_db_x;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 48);
      c1_eb_x = c1_mpower(chartInstance, c1_recX -
                          c1_tra_x[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_x", (int32_T)
        _SFD_INTEGER_CHECK("rec_index+1", c1_rec_index + 1.0), 1, 8, 1, 0) - 1])
        + c1_mpower(chartInstance, c1_recY -
                    c1_tra_y[_SFD_EML_ARRAY_BOUNDS_CHECK("tra_y", (int32_T)
        _SFD_INTEGER_CHECK("rec_index+1", c1_rec_index + 1.0), 1, 8, 1, 0) - 1]);
      c1_fb_x = c1_eb_x;
      if (c1_fb_x < 0.0) {
        c1_eml_error(chartInstance);
      }

      c1_fb_x = muDoubleScalarSqrt(c1_fb_x);
      c1_d[1] = c1_fb_x;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 50);
      c1_d_A = c1_d[1];
      c1_d_B = c1_d[0];
      c1_gb_x = c1_d_A;
      c1_fb_y = c1_d_B;
      c1_hb_x = c1_gb_x;
      c1_gb_y = c1_fb_y;
      c1_hb_y = c1_hb_x / c1_gb_y;
      if (CV_EML_IF(0, 1, 5, c1_hb_y < 0.33333333333333331)) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 51);
        c1_rec_index++;
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 54);
    c1_cur_index = c1_rec_index;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 55);
    c1_cur_times = c1_rec_times + 1.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -55);
  sf_debug_symbol_scope_pop();
  *c1_b_cur_index = c1_cur_index;
  *c1_b_curX = c1_curX;
  *c1_b_curY = c1_curY;
  *c1_b_cur_times = c1_cur_times;
  *c1_b_cur_angle = c1_cur_angle;
  *c1_b_val = c1_val;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_Stanley_model(SFc1_Stanley_modelInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_Stanley_modelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Stanley_modelInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_val, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_val), &c1_thisId);
  sf_mex_destroy(&c1_val);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_val;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_Stanley_modelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Stanley_modelInstanceStruct *)chartInstanceVoid;
  c1_val = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_val), &c1_thisId);
  sf_mex_destroy(&c1_val);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i9;
  real_T c1_b_inData[2];
  int32_T c1_i10;
  real_T c1_u[2];
  const mxArray *c1_y = NULL;
  SFc1_Stanley_modelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Stanley_modelInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i9 = 0; c1_i9 < 2; c1_i9++) {
    c1_b_inData[c1_i9] = (*(real_T (*)[2])c1_inData)[c1_i9];
  }

  for (c1_i10 = 0; c1_i10 < 2; c1_i10++) {
    c1_u[c1_i10] = c1_b_inData[c1_i10];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i11;
  real_T c1_b_inData[8];
  int32_T c1_i12;
  real_T c1_u[8];
  const mxArray *c1_y = NULL;
  SFc1_Stanley_modelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Stanley_modelInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i11 = 0; c1_i11 < 8; c1_i11++) {
    c1_b_inData[c1_i11] = (*(real_T (*)[8])c1_inData)[c1_i11];
  }

  for (c1_i12 = 0; c1_i12 < 8; c1_i12++) {
    c1_u[c1_i12] = c1_b_inData[c1_i12];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 8), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i13;
  real_T c1_b_inData[7];
  int32_T c1_i14;
  real_T c1_u[7];
  const mxArray *c1_y = NULL;
  SFc1_Stanley_modelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Stanley_modelInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i13 = 0; c1_i13 < 7; c1_i13++) {
    c1_b_inData[c1_i13] = (*(real_T (*)[7])c1_inData)[c1_i13];
  }

  for (c1_i14 = 0; c1_i14 < 7; c1_i14++) {
    c1_u[c1_i14] = c1_b_inData[c1_i14];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 7), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i15;
  real_T c1_b_inData[2];
  int32_T c1_i16;
  real_T c1_u[2];
  const mxArray *c1_y = NULL;
  SFc1_Stanley_modelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Stanley_modelInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i15 = 0; c1_i15 < 2; c1_i15++) {
    c1_b_inData[c1_i15] = (*(real_T (*)[2])c1_inData)[c1_i15];
  }

  for (c1_i16 = 0; c1_i16 < 2; c1_i16++) {
    c1_u[c1_i16] = c1_b_inData[c1_i16];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 2), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_c_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[2])
{
  real_T c1_dv0[2];
  int32_T c1_i17;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv0, 1, 0, 0U, 1, 0U, 2, 1, 2);
  for (c1_i17 = 0; c1_i17 < 2; c1_i17++) {
    c1_y[c1_i17] = c1_dv0[c1_i17];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_d;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[2];
  int32_T c1_i18;
  SFc1_Stanley_modelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Stanley_modelInstanceStruct *)chartInstanceVoid;
  c1_d = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_d), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_d);
  for (c1_i18 = 0; c1_i18 < 2; c1_i18++) {
    (*(real_T (*)[2])c1_outData)[c1_i18] = c1_y[c1_i18];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_Stanley_model_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[24];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i19;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 24), FALSE);
  for (c1_i19 = 0; c1_i19 < 24; c1_i19++) {
    c1_r0 = &c1_info[c1_i19];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i19);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i19);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i19);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i19);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i19);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i19);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i19);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i19);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[24])
{
  c1_info[0].context = "";
  c1_info[0].name = "length";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c1_info[0].fileTimeLo = 1303128206U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 0U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context = "";
  c1_info[1].name = "cos";
  c1_info[1].dominantType = "double";
  c1_info[1].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c1_info[1].fileTimeLo = 1286800706U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 0U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c1_info[2].name = "eml_scalar_cos";
  c1_info[2].dominantType = "double";
  c1_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c1_info[2].fileTimeLo = 1286800722U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context = "";
  c1_info[3].name = "mtimes";
  c1_info[3].dominantType = "double";
  c1_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[3].fileTimeLo = 1289498092U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context = "";
  c1_info[4].name = "sin";
  c1_info[4].dominantType = "double";
  c1_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c1_info[4].fileTimeLo = 1286800750U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c1_info[5].name = "eml_scalar_sin";
  c1_info[5].dominantType = "double";
  c1_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c1_info[5].fileTimeLo = 1286800736U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context = "";
  c1_info[6].name = "abs";
  c1_info[6].dominantType = "double";
  c1_info[6].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[6].fileTimeLo = 1286800694U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[7].name = "eml_scalar_abs";
  c1_info[7].dominantType = "double";
  c1_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[7].fileTimeLo = 1286800712U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context = "";
  c1_info[8].name = "mpower";
  c1_info[8].dominantType = "double";
  c1_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[8].fileTimeLo = 1286800842U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[9].name = "power";
  c1_info[9].dominantType = "double";
  c1_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[9].fileTimeLo = 1336504096U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[10].name = "eml_scalar_eg";
  c1_info[10].dominantType = "double";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[10].fileTimeLo = 1286800796U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[11].name = "eml_scalexp_alloc";
  c1_info[11].dominantType = "double";
  c1_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[11].fileTimeLo = 1330586834U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[12].name = "floor";
  c1_info[12].dominantType = "double";
  c1_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[12].fileTimeLo = 1286800742U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[13].name = "eml_scalar_floor";
  c1_info[13].dominantType = "double";
  c1_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[13].fileTimeLo = 1286800726U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 0U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context = "";
  c1_info[14].name = "sqrt";
  c1_info[14].dominantType = "double";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[14].fileTimeLo = 1286800752U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[15].name = "eml_error";
  c1_info[15].dominantType = "char";
  c1_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c1_info[15].fileTimeLo = 1305300000U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
  c1_info[16].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[16].name = "eml_scalar_sqrt";
  c1_info[16].dominantType = "double";
  c1_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c1_info[16].fileTimeLo = 1286800738U;
  c1_info[16].fileTimeHi = 0U;
  c1_info[16].mFileTimeLo = 0U;
  c1_info[16].mFileTimeHi = 0U;
  c1_info[17].context = "";
  c1_info[17].name = "mrdivide";
  c1_info[17].dominantType = "double";
  c1_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[17].fileTimeLo = 1342792944U;
  c1_info[17].fileTimeHi = 0U;
  c1_info[17].mFileTimeLo = 1319711966U;
  c1_info[17].mFileTimeHi = 0U;
  c1_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[18].name = "rdivide";
  c1_info[18].dominantType = "double";
  c1_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[18].fileTimeLo = 1286800844U;
  c1_info[18].fileTimeHi = 0U;
  c1_info[18].mFileTimeLo = 0U;
  c1_info[18].mFileTimeHi = 0U;
  c1_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[19].name = "eml_div";
  c1_info[19].dominantType = "double";
  c1_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[19].fileTimeLo = 1313329810U;
  c1_info[19].fileTimeHi = 0U;
  c1_info[19].mFileTimeLo = 0U;
  c1_info[19].mFileTimeHi = 0U;
  c1_info[20].context = "";
  c1_info[20].name = "sign";
  c1_info[20].dominantType = "double";
  c1_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c1_info[20].fileTimeLo = 1286800750U;
  c1_info[20].fileTimeHi = 0U;
  c1_info[20].mFileTimeLo = 0U;
  c1_info[20].mFileTimeHi = 0U;
  c1_info[21].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c1_info[21].name = "eml_scalar_sign";
  c1_info[21].dominantType = "double";
  c1_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sign.m";
  c1_info[21].fileTimeLo = 1307633238U;
  c1_info[21].fileTimeHi = 0U;
  c1_info[21].mFileTimeLo = 0U;
  c1_info[21].mFileTimeHi = 0U;
  c1_info[22].context = "";
  c1_info[22].name = "atan";
  c1_info[22].dominantType = "double";
  c1_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan.m";
  c1_info[22].fileTimeLo = 1305299998U;
  c1_info[22].fileTimeHi = 0U;
  c1_info[22].mFileTimeLo = 0U;
  c1_info[22].mFileTimeHi = 0U;
  c1_info[23].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan.m";
  c1_info[23].name = "eml_scalar_atan";
  c1_info[23].dominantType = "double";
  c1_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan.m";
  c1_info[23].fileTimeLo = 1286800718U;
  c1_info[23].fileTimeHi = 0U;
  c1_info[23].mFileTimeLo = 0U;
  c1_info[23].mFileTimeHi = 0U;
}

static real_T c1_mpower(SFc1_Stanley_modelInstanceStruct *chartInstance, real_T
  c1_a)
{
  real_T c1_b_a;
  real_T c1_c_a;
  real_T c1_ak;
  c1_b_a = c1_a;
  c1_c_a = c1_b_a;
  c1_ak = c1_c_a;
  return muDoubleScalarPower(c1_ak, 2.0);
}

static void c1_eml_error(SFc1_Stanley_modelInstanceStruct *chartInstance)
{
  int32_T c1_i20;
  static char_T c1_varargin_1[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o',
    'o', 'l', 'b', 'o', 'x', ':', 's', 'q', 'r', 't', '_', 'd', 'o', 'm', 'a',
    'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c1_u[30];
  const mxArray *c1_y = NULL;
  for (c1_i20 = 0; c1_i20 < 30; c1_i20++) {
    c1_u[c1_i20] = c1_varargin_1[c1_i20];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 30), FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c1_y));
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_Stanley_modelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Stanley_modelInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_d_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i21;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i21, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i21;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_Stanley_modelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Stanley_modelInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_e_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_Stanley_model, const char_T
  *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_Stanley_model), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_Stanley_model);
  return c1_y;
}

static uint8_T c1_f_emlrt_marshallIn(SFc1_Stanley_modelInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_Stanley_modelInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_Stanley_model_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(498658945U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(928100305U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1778264220U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1107135973U);
}

mxArray *sf_c1_Stanley_model_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("OU8FjEtlF0q5DDiNl7cFKC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,13,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c1_Stanley_model(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x7'type','srcId','name','auxInfo'{{M[1],M[11],T\"curX\",},{M[1],M[12],T\"curY\",},{M[1],M[20],T\"cur_angle\",},{M[1],M[10],T\"cur_index\",},{M[1],M[5],T\"cur_times\",},{M[1],M[26],T\"val\",},{M[8],M[0],T\"is_active_c1_Stanley_model\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 7, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_Stanley_model_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_Stanley_modelInstanceStruct *chartInstance;
    chartInstance = (SFc1_Stanley_modelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_Stanley_modelMachineNumber_,
           1,
           1,
           1,
           19,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_Stanley_modelMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_Stanley_modelMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_Stanley_modelMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,2,0,1,"cur_index");
          _SFD_SET_DATA_PROPS(1,2,0,1,"curX");
          _SFD_SET_DATA_PROPS(2,2,0,1,"curY");
          _SFD_SET_DATA_PROPS(3,1,1,0,"slope");
          _SFD_SET_DATA_PROPS(4,2,0,1,"cur_times");
          _SFD_SET_DATA_PROPS(5,1,1,0,"start_index");
          _SFD_SET_DATA_PROPS(6,1,1,0,"tra_x");
          _SFD_SET_DATA_PROPS(7,1,1,0,"tra_y");
          _SFD_SET_DATA_PROPS(8,1,1,0,"v");
          _SFD_SET_DATA_PROPS(9,1,1,0,"k");
          _SFD_SET_DATA_PROPS(10,1,1,0,"init_pos");
          _SFD_SET_DATA_PROPS(11,1,1,0,"init_angle");
          _SFD_SET_DATA_PROPS(12,1,1,0,"rec_index");
          _SFD_SET_DATA_PROPS(13,1,1,0,"recX");
          _SFD_SET_DATA_PROPS(14,1,1,0,"recY");
          _SFD_SET_DATA_PROPS(15,1,1,0,"rec_times");
          _SFD_SET_DATA_PROPS(16,1,1,0,"rec_angle");
          _SFD_SET_DATA_PROPS(17,2,0,1,"cur_angle");
          _SFD_SET_DATA_PROPS(18,2,0,1,"val");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,6,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2172);
        _SFD_CV_INIT_EML_IF(0,1,0,177,213,405,2171);
        _SFD_CV_INIT_EML_IF(0,1,1,414,433,-1,554);
        _SFD_CV_INIT_EML_IF(0,1,2,765,789,928,1054);
        _SFD_CV_INIT_EML_IF(0,1,3,1248,1310,1377,1451);
        _SFD_CV_INIT_EML_IF(0,1,4,1736,1755,-1,2104);
        _SFD_CV_INIT_EML_IF(0,1,5,2025,2045,-1,2096);

        {
          static int condStart[] = { 1253, 1284 };

          static int condEnd[] = { 1278, 1308 };

          static int pfixExpr[] = { 0, 1, -2 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,1252,1309,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 8;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 8;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);

        {
          real_T *c1_cur_index;
          real_T *c1_curX;
          real_T *c1_curY;
          real_T *c1_cur_times;
          real_T *c1_start_index;
          real_T *c1_v;
          real_T *c1_k;
          real_T *c1_init_angle;
          real_T *c1_rec_index;
          real_T *c1_recX;
          real_T *c1_recY;
          real_T *c1_rec_times;
          real_T *c1_rec_angle;
          real_T *c1_cur_angle;
          real_T *c1_val;
          real_T (*c1_slope)[7];
          real_T (*c1_tra_x)[8];
          real_T (*c1_tra_y)[8];
          real_T (*c1_init_pos)[2];
          c1_val = (real_T *)ssGetOutputPortSignal(chartInstance->S, 6);
          c1_cur_angle = (real_T *)ssGetOutputPortSignal(chartInstance->S, 5);
          c1_rec_angle = (real_T *)ssGetInputPortSignal(chartInstance->S, 12);
          c1_rec_times = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
          c1_recY = (real_T *)ssGetInputPortSignal(chartInstance->S, 10);
          c1_recX = (real_T *)ssGetInputPortSignal(chartInstance->S, 9);
          c1_rec_index = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
          c1_init_angle = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
          c1_init_pos = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 6);
          c1_k = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c1_v = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c1_tra_y = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 3);
          c1_tra_x = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 2);
          c1_start_index = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c1_cur_times = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c1_slope = (real_T (*)[7])ssGetInputPortSignal(chartInstance->S, 0);
          c1_curY = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c1_curX = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c1_cur_index = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_cur_index);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_curX);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_curY);
          _SFD_SET_DATA_VALUE_PTR(3U, *c1_slope);
          _SFD_SET_DATA_VALUE_PTR(4U, c1_cur_times);
          _SFD_SET_DATA_VALUE_PTR(5U, c1_start_index);
          _SFD_SET_DATA_VALUE_PTR(6U, *c1_tra_x);
          _SFD_SET_DATA_VALUE_PTR(7U, *c1_tra_y);
          _SFD_SET_DATA_VALUE_PTR(8U, c1_v);
          _SFD_SET_DATA_VALUE_PTR(9U, c1_k);
          _SFD_SET_DATA_VALUE_PTR(10U, *c1_init_pos);
          _SFD_SET_DATA_VALUE_PTR(11U, c1_init_angle);
          _SFD_SET_DATA_VALUE_PTR(12U, c1_rec_index);
          _SFD_SET_DATA_VALUE_PTR(13U, c1_recX);
          _SFD_SET_DATA_VALUE_PTR(14U, c1_recY);
          _SFD_SET_DATA_VALUE_PTR(15U, c1_rec_times);
          _SFD_SET_DATA_VALUE_PTR(16U, c1_rec_angle);
          _SFD_SET_DATA_VALUE_PTR(17U, c1_cur_angle);
          _SFD_SET_DATA_VALUE_PTR(18U, c1_val);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_Stanley_modelMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization()
{
  return "xGJ0fwINiN25D5Qbfcf2AE";
}

static void sf_opaque_initialize_c1_Stanley_model(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_Stanley_modelInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_Stanley_model((SFc1_Stanley_modelInstanceStruct*)
    chartInstanceVar);
  initialize_c1_Stanley_model((SFc1_Stanley_modelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c1_Stanley_model(void *chartInstanceVar)
{
  enable_c1_Stanley_model((SFc1_Stanley_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_Stanley_model(void *chartInstanceVar)
{
  disable_c1_Stanley_model((SFc1_Stanley_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_Stanley_model(void *chartInstanceVar)
{
  sf_c1_Stanley_model((SFc1_Stanley_modelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_Stanley_model(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_Stanley_model
    ((SFc1_Stanley_modelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_Stanley_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_Stanley_model(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_Stanley_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_Stanley_model((SFc1_Stanley_modelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_Stanley_model(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_Stanley_model(S);
}

static void sf_opaque_set_sim_state_c1_Stanley_model(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c1_Stanley_model(S, st);
}

static void sf_opaque_terminate_c1_Stanley_model(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_Stanley_modelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_Stanley_model((SFc1_Stanley_modelInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_Stanley_model_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_Stanley_model((SFc1_Stanley_modelInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_Stanley_model(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_Stanley_model((SFc1_Stanley_modelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_Stanley_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Stanley_model_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 11, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 12, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,13);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,6);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1469512875U));
  ssSetChecksum1(S,(2291793003U));
  ssSetChecksum2(S,(525343514U));
  ssSetChecksum3(S,(1223390690U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_Stanley_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_Stanley_model(SimStruct *S)
{
  SFc1_Stanley_modelInstanceStruct *chartInstance;
  chartInstance = (SFc1_Stanley_modelInstanceStruct *)malloc(sizeof
    (SFc1_Stanley_modelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_Stanley_modelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_Stanley_model;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_Stanley_model;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_Stanley_model;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_Stanley_model;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_Stanley_model;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_Stanley_model;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_Stanley_model;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_Stanley_model;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_Stanley_model;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_Stanley_model;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_Stanley_model;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_Stanley_model_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_Stanley_model(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_Stanley_model(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_Stanley_model(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_Stanley_model_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
