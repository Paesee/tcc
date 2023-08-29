#define EXPORT __declspec(dllexport)

#ifndef GRID_FOLLOWING_INVERTER
#define GRID_FOLLOWING_INVERTER

/* POWER CONTROLLER */

// Power Controller Struct
typedef struct{
  float p_ref;
  float q_ref;
  float last_p_error;
  float last_i_direct;
  float last_q_error;
  float last_i_quad;
  float last_pf_meas;
  float last_qf_meas;
} PowerControl;

// Power Controller Gains

/*
Having in mind that the implemented controller is a PI and its difference equation looks like this:
  p_ctrl_action = P_GAIN_1 * p_error + P_GAIN_2 * pc->last_p_error + P_GAIN_3 * pc->last_p_action;
  q_ctrl_action = Q_GAIN_1 * q_error + Q_GAIN_2 * pc->last_q_error + Q_GAIN_3 * pc->last_q_action;
Please, define the gains below.
*/

#define P_GAIN_1  0.00035
#define P_GAIN_2 -0.0002625
#define P_GAIN_3  1
#define Q_GAIN_1  0.00035
#define Q_GAIN_2 -0.0002625
#define Q_GAIN_3  1

/*
Having in mind that the implemented power calculation method uses a Low Pass Filter and its difference equation looks like this:
  P = LPF_GAIN_1 * p + LPF_GAIN_2 * ep->last_pf;
  Q = LPF_GAIN_1 * q + LPF_GAIN_2 * ep->last_qf;
Please, define the gains below.
*/

#define LPF_GAIN_1 0.01559
#define LPF_GAIN_2 0.9844

// Power Controller Functions

EXPORT void PowerControlInit(PowerControl *pc, float p_ref, float q_ref);
EXPORT void setPQ(PowerControl *pc, float p_ref, float q_ref);
EXPORT void calculatePQ(PowerControl *pc, float v_alpha, float v_beta, float i_alpha, float i_beta, float *active_power, float *reactive_power);
EXPORT void executePQControl(PowerControl *pc, float *id, float *iq);

/* CURRENT CONTROLLER */

// Current Controller Struct

typedef struct{
  float last_u;
  float sec_last_u;
  float last_error;
  float sec_last_error;
} CurrentControl;

// Current Controller Gains
#define C_GAIN_1 0.15
#define C_GAIN_2 -0.15
#define C_GAIN_3 -1.9999
#define C_GAIN_4 0.9999

// Current Controller Functions
EXPORT void CurrentControlInit(CurrentControl *cc);
EXPORT void executeCurrentControl(CurrentControl *cc, float id, float iq, float sin_wt, float cos_wt, float i_meas, float *u);

#endif