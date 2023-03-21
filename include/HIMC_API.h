//
// Copyright (C) HIWIN MIKROSYSTEM. All rights reserved.
//
// Public APIs for HIMC motion controller
//

#ifndef HIMC_API_H
#define HIMC_API_H


#if defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__
  #ifdef HIMC_API_EXPORTS
    #ifdef __GNUC__
      #define HIMC_API_API __attribute__ ((dllexport))
    #else
      #define HIMC_API_API __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define HIMC_API_API __attribute__ ((dllimport))
    #else
      #define HIMC_API_API __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define HIMC_API_API __attribute__ ((visibility ("default")))
  #else
    #define HIMC_API_API
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------//
// 18. Enumerations                                               //
// ---------------------------------------------------------------//

// 18.1 connection type of himc 
typedef enum {
  COM_TYPE_TCPIP,
  COM_TYPE_RS232,
  COM_TYPE_SIMULATOR
} ComType;

// 18.2 coordinate systems for coordinated motion 
typedef enum {
  kCoord_ACS = 0,  /* axis coordinate system */
  kCoord_MCS = 1,  /* machine coordinate system */
  kCoord_PCS = 2,  /* product coordinate system */
} CoordSystem;

// 18.3 buffer modes: for blending between motion segments 
typedef enum {
  kBM_Buffered = 0,
  kBM_Aborting = 1,
  kBM_BlendingLow = 2,
  kBM_BlendingPrevious = 3,
  kBM_BlendingNext = 4,
  kBM_BlendingHigh = 5,
} MotionBufferMode;

// 18.4 transition modes: for characterizing contour curve
typedef enum {
  kTM_None = 0,
  kTM_StartVelocity = 1,
  kTM_ConstantVelocity = 2,
  kTM_CornerDistance = 3,
  kTM_MaxCornerDeviation = 4,
  kTM_PLCopenReserved_05 = 5,
  kTM_PLCopenReserved_06 = 6,
  kTM_PLCopenReserved_07 = 7,
  kTM_PLCopenReserved_08 = 8,
  kTM_PLCopenReserved_09 = 9
} MotionTransitionMode;

// 18.5 input shaping mode enumeration
typedef enum {
  Shaper_Normal = 0,
  Shaper_Robust
} ShaperMode;


// ---------------------------------------------------------------//
// 17. Data Struct                                                //
// ---------------------------------------------------------------//
// 17.1  It defines the connection type and its information.
typedef struct {

  ComType type;

  struct {
    char ip[20];
    char port[12];
  } TCP_IP;

  struct {
    char com_port_name[80];
    int baud_rate;
  } RS232;

  struct {
    char autoExecExe;
  } Simulator;

} ComInfo;

// 17.2 It defines the positions or distances of the coordinate motion. 
typedef struct tagCoordPosition {
  double x_pos;
  double y_pos;
  double z_pos;
  double a_pos;
  double b_pos;
  double c_pos;
} CoordPosition, *PCoordPosition;

// 17.3 It defines the motion profile settings.
typedef struct tagMotionProfile {
  double max_vel;
  double max_acc;
  double max_dec;
  double smooth_time;
} MotionProfile, *PMotionProfile;

//17.4 It defines the center position settings. 
typedef struct tagCenterPosition {
  double x_pos;
  double y_pos;
  double z_pos;
} CenterPosition;

//17.5 It defines the normal vector settings. 
typedef struct tagNormalVector {
  double x_vector;
  double y_vector;
  double z_vector;
} NormalVector;

//17.6 It defines the position trigger settings. 
typedef struct tagPosTriggerPar {
  double start_pos;
  double end_pos;
  double interval;
  int    pulse_width;
} PosTriggerPar, *PPosTriggerPar;


// ---------------------------------------------------------------//
// 2. HIMC System Functions                                       //
// ---------------------------------------------------------------//

HIMC_API_API int HIMC_ConnectCtrl(const ComInfo com_info, int *p_ctrl_id);
HIMC_API_API int HIMC_ConnectToSimulator(int *p_ctrl_id);
HIMC_API_API int HIMC_ConnectToEthernet(const char *ip_address,const char *port, int *p_ctrl_id);
HIMC_API_API int HIMC_DisconnectCtrl(int ctrl_id);
HIMC_API_API int HIMC_RebootController(int ctrl_id);
HIMC_API_API int HIMC_IsSystemOper(int ctrl_id, int *isOper);   
HIMC_API_API int HIMC_IsSystemPreOp(int ctrl_id, int *isPreOp);  
HIMC_API_API int HIMC_IsSystemError(int ctrl_id, int *isError);
HIMC_API_API int HIMC_DisableAll(int ctrl_id);
HIMC_API_API int HIMC_StopAll(int ctrl_id);
HIMC_API_API int HIMC_EStop(int ctrl_id);
HIMC_API_API int HIMC_GetSlaveNum(int ctrl_id, int *p_num_of_slave);
HIMC_API_API int HIMC_GetFirmwareVer(int ctrl_id, char *p_ver_buf);
HIMC_API_API int HIMC_RescanMoE(int ctrl_id);


// ---------------------------------------------------------------//
// 3. Axis Functions                                              //
// ---------------------------------------------------------------//

// -------------------3.2 Axis Motion Control---------------------/

HIMC_API_API int HIMC_Enable(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_Disable(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_Reset(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_MoveAbs(int ctrl_id, int axis_id, double pos);
HIMC_API_API int HIMC_MoveRel(int ctrl_id, int axis_id, double rel_dist);
HIMC_API_API int HIMC_MoveVel(int ctrl_id, int axis_id, double vel);
HIMC_API_API int HIMC_Stop(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_Halt(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_Resume(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_PVTMotion(int ctrl_id, int axis_id, double *time, double *pos, double *vel, int num_pt);

// -------------------3.3 Axis Setting---------------------//

HIMC_API_API int HIMC_GetMaxVel(int ctrl_id, int axis_id, double *p_vel);
HIMC_API_API int HIMC_SetVel(int ctrl_id, int axis_id, double vel);
HIMC_API_API int HIMC_GetMaxAcc(int ctrl_id, int axis_id, double *p_acc);
HIMC_API_API int HIMC_SetAcc(int ctrl_id, int axis_id, double acc);
HIMC_API_API int HIMC_SetAccTime(int ctrl_id, int axis_id, double acc_time);
HIMC_API_API int HIMC_GetMaxDec(int ctrl_id, int axis_id, double *p_dec);
HIMC_API_API int HIMC_SetDec(int ctrl_id, int axis_id, double dec);
HIMC_API_API int HIMC_SetDecTime(int ctrl_id, int axis_id, double dec_time);
HIMC_API_API int HIMC_GetKillDec(int ctrl_id, int axis_id, double *p_kill_dec);
HIMC_API_API int HIMC_SetKillDec(int ctrl_id, int axis_id, double kill_dec);

HIMC_API_API int HIMC_GetSWRL(int ctrl_id, int axis_id, double *p_right_limit_pos);
HIMC_API_API int HIMC_SetSWRL(int ctrl_id, int axis_id, double right_limit_pos);
HIMC_API_API int HIMC_GetSWLL(int ctrl_id, int axis_id, double *p_left_limit_pos);
HIMC_API_API int HIMC_SetSWLL(int ctrl_id, int axis_id, double left_limit_pos);
HIMC_API_API int HIMC_GetSMTime(int ctrl_id, int axis_id, double *p_smooth_time);
HIMC_API_API int HIMC_SetSMTime(int ctrl_id, int axis_id, double smooth_time);
HIMC_API_API int HIMC_GetMoveTime(int ctrl_id, int axis_id, double *p_move_time);
HIMC_API_API int HIMC_GetSettlingTime(int ctrl_id, int axis_id, double *p_settling_time);

HIMC_API_API int HIMC_SetPos(int ctrl_id, int axis_id, double pos);
HIMC_API_API int HIMC_GetPosFb(int ctrl_id, int axis_id, double *p_pos);
HIMC_API_API int HIMC_GetPosOffset(int ctrl_id, int axis_id, double *p_pos);
HIMC_API_API int HIMC_GetPosErr(int ctrl_id, int axis_id, double *p_pos_err);
HIMC_API_API int HIMC_GetVelFb (int ctrl_id, int axis_id, double *p_vel);
HIMC_API_API int HIMC_GetVelErr (int ctrl_id, int axis_id, double *p_vel_err);
HIMC_API_API int HIMC_GetCurrFb (int ctrl_id, int axis_id, double *p_curr);
HIMC_API_API int HIMC_GetRefPos(int ctrl_id, int axis_id, double *p_pos);
HIMC_API_API int HIMC_GetRefVel(int ctrl_id, int axis_id, double *p_vel);
HIMC_API_API int HIMC_GetRefAcc(int ctrl_id, int axis_id, double *p_acc);
HIMC_API_API int HIMC_GetPosOut(int ctrl_id, int axis_id, double *p_pos);
HIMC_API_API int HIMC_GetVelOut(int ctrl_id, int axis_id, double *p_vel);
HIMC_API_API int HIMC_GetAccOut(int ctrl_id, int axis_id, double *p_acc);

HIMC_API_API int HIMC_IgnoreHWL(int ctrl_id, int axis_id, int cmd);
HIMC_API_API int HIMC_IgnoreSWL(int ctrl_id, int axis_id, int cmd);
HIMC_API_API int HIMC_IgnorePE(int ctrl_id, int axis_id, int cmd);
HIMC_API_API int HIMC_GetAxisNum(int ctrl_id, int *num);
HIMC_API_API int HIMC_SetVelScale(int ctrl_id, int axis_id, double scale);
HIMC_API_API int HIMC_GetVelScale(int ctrl_id, int axis_id, double *p_scale);
HIMC_API_API int HIMC_SetRollover(int ctrl_id, int axis_id, double rollover_val);
HIMC_API_API int HIMC_GetRolloverTurns(int ctrl_id, int axis_id, int *p_turns);
HIMC_API_API int HIMC_GetMultiAxesFeedbackPos(int ctrl_id, int *p_axes_id_array, int num_of_axes, double *p_pos_array);

// -------------------3.4 Axis Status---------------------//

HIMC_API_API int HIMC_IsEnabled(int ctrl_id, int axis_id,  int *p_enabled);
HIMC_API_API int HIMC_IsMoving(int ctrl_id, int axis_id, int *p_is_moving);
HIMC_API_API int HIMC_IsInPos(int ctrl_id, int axis_id, int *p_in_position);
HIMC_API_API int HIMC_IsErrorStop(int ctrl_id, int axis_id, int *p_is_errorstop);
HIMC_API_API int HIMC_IsGantry(int ctrl_id, int axis_id, int *p_is_gantry);
HIMC_API_API int HIMC_IsGrouped(int ctrl_id, int axis_id, int *p_is_grouped);
HIMC_API_API int HIMC_IsSync(int ctrl_id, int axis_id, int *p_is_sync);
HIMC_API_API int HIMC_IsHWLL(int ctrl_id, int axis_id, int *p_is_hwll);
HIMC_API_API int HIMC_IsHWRL(int ctrl_id, int axis_id, int *p_is_hwrl);
HIMC_API_API int HIMC_IsSWLL(int ctrl_id, int axis_id, int *p_is_swll);
HIMC_API_API int HIMC_IsSWRL(int ctrl_id, int axis_id, int *p_is_swrl);
HIMC_API_API int HIMC_IsDriveErr(int ctrl_id, int axis_id, int *p_is_driveerr);
HIMC_API_API int HIMC_IsPosErr(int ctrl_id, int axis_id, int *p_is_pos_err);
HIMC_API_API int HIMC_IsCompActive(int ctrl_id, int axis_id, int *p_is_compactive);


// ---------------------------------------------------------------//
// 4. Synchronized Motion Functions                               //
// ---------------------------------------------------------------//

HIMC_API_API int HIMC_EnableGear(int ctrl_id, int axis_master_id, int axis_slave_id);
HIMC_API_API int HIMC_DisableGear(int ctrl_id, int axis_slave_id);
HIMC_API_API int HIMC_GearIn(int ctrl_id, int axis_master_id, int axis_slave_id, double gear_ratio);
HIMC_API_API int HIMC_GearOut(int ctrl_id, int axis_slave_id);
HIMC_API_API int HIMC_GetGearRatio(int ctrl_id, int sync_slave_id, double *gear_ratio);
HIMC_API_API int HIMC_IsInGear(int ctrl_id, int axis_id, int *p_is_in_gear);
HIMC_API_API int HIMC_IsGearMaster(int ctrl_id, int axis_id, int *p_is_gear_master);
HIMC_API_API int HIMC_IsGearSlave(int ctrl_id, int axis_id, int *p_is_gear_slave);


// ---------------------------------------------------------------//
// 5. Gantry Functions                                            //
// ---------------------------------------------------------------//

HIMC_API_API int HIMC_EnableGantryPair(int ctrl_id, int lhs_axis_id, int rhs_axis_id);
HIMC_API_API int HIMC_DisableGantryPair(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_GetGantryPairID(int ctrl_id, int axis_id, int *p_id);
HIMC_API_API int HIMC_IsGantryPair(int ctrl_id, int axis_id1,int axis_id2, int *p_is_gantry_pair);


// ---------------------------------------------------------------//
// 6. Group Functions                                             //
// ---------------------------------------------------------------//

// -------------------6.2 Group Motion Control--------------------//
HIMC_API_API int HIMC_EnableGroup(int ctrl_id, int group_id);
HIMC_API_API int HIMC_DisableGroup(int ctrl_id, int group_id);
HIMC_API_API int HIMC_StopGroup(int ctrl_id, int group_id);
HIMC_API_API int HIMC_ResetGroup(int ctrl_id, int group_id);
HIMC_API_API int HIMC_HaltGroup(int ctrl_id, int group_id);
HIMC_API_API int HIMC_ResumeGroup(int ctrl_id, int group_id);
HIMC_API_API int HIMC_JogGroup(int ctrl_id, int group_id, int carte_dir, double jog_vel);
HIMC_API_API int HIMC_JogGroupAxis(int ctrl_id, int group_id, int grp_axis, double jog_vel);
HIMC_API_API int HIMC_LineAbs2D(int ctrl_id, int group_id, double end_x, double end_y);
HIMC_API_API int HIMC_LineAbs3D(int ctrl_id, int group_id, double end_x, double end_y, double end_z);
HIMC_API_API int HIMC_LineRel2D(int ctrl_id, int group_id, double distance_x, double distance_y);
HIMC_API_API int HIMC_LineRel3D(int ctrl_id, int group_id, double distance_x, double distance_y, double distance_z);
HIMC_API_API int HIMC_Arc2D(int ctrl_id, int group_id, double border_x, double border_y, double end_x, double end_y);
HIMC_API_API int HIMC_ArcCW2D(int ctrl_id, int group_id, double center_x, double center_y, double end_x, double end_y);
HIMC_API_API int HIMC_ArcCCW2D(int ctrl_id, int group_id, double center_x, double center_y, double end_x, double end_y);
HIMC_API_API int HIMC_Circle2D(int ctrl_id, int group_id, double center_x, double center_y, double end_x, double end_y, int turns);

// -------------------6.3 Group Setting--------------------//

HIMC_API_API int HIMC_AddAxesToGrp(int ctrl_id, int group_id, int num_of_axes, int *p_axes_id);
HIMC_API_API int HIMC_RemoveAxisFromGrp(int ctrl_id, int group_id);
HIMC_API_API int HIMC_SetupGroup(int ctrl_id, int group_id, int num_of_axes, int *axis_list);
HIMC_API_API int HIMC_UngrpAllAxes(int ctrl_id, int group_id);
HIMC_API_API int HIMC_GetGroupID(int ctrl_id, int axis_id, int *p_group_id);
HIMC_API_API int HIMC_SetGrpMotionProfile(int ctrl_id, int group_id, double max_velocity, double max_acceleration, double max_deceleration, double smooth_time);
HIMC_API_API int HIMC_GetGrpKin(int ctrl_id, int group_id, int *p_kin_type);
HIMC_API_API int HIMC_SetGrpKin(int ctrl_id, int group_id, int kin_type);   
HIMC_API_API int HIMC_GetGrpMaxVel(int ctrl_id, int group_id, double *p_grp_vel);
HIMC_API_API int HIMC_SetGrpVel(int ctrl_id, int group_id, double vel);
HIMC_API_API int HIMC_GetGrpMaxAcc(int ctrl_id, int group_id, double *p_grp_acc);
HIMC_API_API int HIMC_SetGrpAcc(int ctrl_id, int group_id, double acc);
HIMC_API_API int HIMC_SetGrpAccTime(int ctrl_id, int group_id, double acc_time);
HIMC_API_API int HIMC_GetGrpMaxDec(int ctrl_id, int group_id, double *p_dec);
HIMC_API_API int HIMC_SetGrpDec(int ctrl_id, int group_id, double dec);
HIMC_API_API int HIMC_SetGrpDecTime(int ctrl_id, int group_id, double dec_time);
HIMC_API_API int HIMC_GetGrpSMTime(int ctrl_id, int group_id, double *p_grp_smooth_time);
HIMC_API_API int HIMC_SetGrpSMTime(int ctrl_id, int group_id, double smooth_time);
HIMC_API_API int HIMC_GetGrpCoordSys(int ctrl_id, int group_id, int *p_grp_coord_sys);
HIMC_API_API int HIMC_SetGrpCoordSys(int ctrl_id, int group_id, int coord_sys);
HIMC_API_API int HIMC_GetGrpBufferMode(int ctrl_id, int group_id, int *p_grp_buffer_mode);
HIMC_API_API int HIMC_SetGrpBufferMode(int ctrl_id, int group_id, int buffer_mode);
HIMC_API_API int HIMC_GetGrpTransMode(int ctrl_id, int group_id, int *p_grp_trans_mode);
HIMC_API_API int HIMC_SetGrpTransMode(int ctrl_id, int group_id, int trans_mode);
HIMC_API_API int HIMC_SetGrpTransPrm(int ctrl_id, int group_id, double trans_vel, double trans_dis);
HIMC_API_API int HIMC_GetGrpCmdNum(int ctrl_id, int group_id, int *p_grp_cmd_num);
HIMC_API_API int HIMC_SetGrpVelScale(int ctrl_id, int group_id, double scale);
HIMC_API_API int HIMC_GetGrpVelScale(int ctrl_id, int group_id, double *p_grp_vel_scale);

// -------------------6.4 Group Status---------------------//

HIMC_API_API int HIMC_IsGrpEnabled(int ctrl_id, int group_id, int *p_is_grp_enabled);
HIMC_API_API int HIMC_IsGrpMoving(int ctrl_id, int group_id, int *p_is_grp_moving);
HIMC_API_API int HIMC_IsGrpInPos(int ctrl_id, int group_id, int *p_is_grp_inpos);
HIMC_API_API int HIMC_IsGrpErrorStop(int ctrl_id, int group_id, int *p_is_grp_errorstop);

// -------------------6.5 Advanced Motion Command---------//

HIMC_API_API int HIMC_LinAbs(int ctrl_id, int group_id, CoordPosition *target_pos, MotionProfile *motion_profile, CoordSystem coord_sys, MotionBufferMode buf_mode, MotionTransitionMode trans_mode, double trans_par);
HIMC_API_API int HIMC_LinRel(int ctrl_id, int group_id, CoordPosition *relative_dist, MotionProfile *motion_profile, CoordSystem coord_sys, MotionBufferMode buf_mode, MotionTransitionMode trans_mode, double trans_par);
HIMC_API_API int HIMC_CircAbs(int ctrl_id, int group_id, CenterPosition *center_pos, NormalVector *normal_vector, int turns, CoordPosition *target_pos, MotionProfile *motion_profile, CoordSystem coord_sys, MotionBufferMode buf_mode, MotionTransitionMode trans_mode, double trans_par);


// ---------------------------------------------------------------//
// 7. GPIO Functions                                              //
// ---------------------------------------------------------------//

// ----------------------7.2 HIMC IO Setting----------------------//

HIMC_API_API int HIMC_SetHimcGpo(int ctrl_id, int gpo_idx, char state);
HIMC_API_API int HIMC_ToggleHimcGpo(int ctrl_id, int gpo_idx);
HIMC_API_API int HIMC_SetHimcMultiGpo(int ctrl_id, int start_idx, int num, char *p_state_array);

// ----------------------7.3 Slave IO Setting---------------------//

HIMC_API_API int HIMC_SetSlaveGpo(int ctrl_id, int slave_id, int gpo_idx, char state);
HIMC_API_API int HIMC_ToggleSlaveGpo(int ctrl_id, int slave_id, int gpo_idx);
HIMC_API_API int HIMC_SetSlaveMultiGpo(int ctrl_id, int slave_id, int start_idx, int num, char *p_state_array);

// ----------------------7.4 HIMC IO Status-----------------------//

HIMC_API_API int HIMC_GetHimcGpi(int ctrl_id, int gpi_idx, char *p_state);
HIMC_API_API int HIMC_GetHimcGpo(int ctrl_id, int gpo_idx, char *p_state);
HIMC_API_API int HIMC_GetHimcMultiGpi(int ctrl_id, int start_idx, int num, char *p_state_array);
HIMC_API_API int HIMC_GetHimcMultiGpo(int ctrl_id, int start_idx, int num, char *p_state_array);
HIMC_API_API int HIMC_GetHimcGpiNum(int ctrl_id, int *p_gpi_num);
HIMC_API_API int HIMC_GetHimcGpoNum(int ctrl_id, int *p_gpo_num);

// ----------------------7.5 Slave IO Status----------------------//

HIMC_API_API int HIMC_GetSlaveGpi(int ctrl_id, int slave_id, int gpi_idx, char *p_state);
HIMC_API_API int HIMC_GetSlaveGpo(int ctrl_id, int slave_id, int gpo_idx, char *p_state);
HIMC_API_API int HIMC_GetSlaveMultiGpi(int ctrl_id, int slave_id, int start_idx, int num, char *p_state_array);
HIMC_API_API int HIMC_GetSlaveMultiGpo(int ctrl_id, int slave_id, int start_idx, int num, char *p_state_array);
HIMC_API_API int HIMC_GetSlaveGpiNum(int ctrl_id, int slave_id, int *p_gpi_num);
HIMC_API_API int HIMC_GetSlaveGpoNum(int ctrl_id, int slave_id, int *p_gpo_num);


// ---------------------------------------------------------------//
// 8. User Table Functions                                        //
// ---------------------------------------------------------------//

HIMC_API_API int HIMC_SetUserTable(int ctrl_id, double *p_user_table_data, int start_idx, int number_of_doubles_to_write);
HIMC_API_API int HIMC_GetUserTable(int ctrl_id, double *p_user_table_data, int start_idx, int number_of_doubles_to_read);
HIMC_API_API int HIMC_SetTableValue(int ctrl_id, int index, double value);
HIMC_API_API int HIMC_GetTableValue(int ctrl_id, int index, double *value);
HIMC_API_API int HIMC_SaveUserTable(int ctrl_id, int start_idx, int num_data);
HIMC_API_API int HIMC_LoadUserTable(int ctrl_id, int start_idx, int num_data);


// ---------------------------------------------------------------//
// 9. Position Trigger Functions                                  //
// ---------------------------------------------------------------//

HIMC_API_API int HIMC_EnablePT(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_DisablePT(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_IsPTEnabled(int ctrl_id, int axis_id, int *p_is_pt_enabled);
HIMC_API_API int HIMC_SetPosTriggerConfig(int ctrl_id, int axis_id, PosTriggerPar *pos_trigger_par);


// ---------------------------------------------------------------//
// 10. Touch Probe Functions                                      //
// ---------------------------------------------------------------//

HIMC_API_API int HIMC_EnableTouchProbe(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_DisableTouchProbe(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_IsTouchProbeEnabled(int ctrl_id, int axis_id, int *p_is_probe_enabled);
HIMC_API_API int HIMC_IsTouchProbeTriggered(int ctrl_id, int axis_id, int *p_is_probe_triggered);
HIMC_API_API int HIMC_GetTouchProbePos(int ctrl_id, int axis_id, double *p_get_probe_pos);


// ---------------------------------------------------------------//
// 11. Dynamic Error Compensation Functions                       //
// ---------------------------------------------------------------//

HIMC_API_API int HIMC_EnableComp(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_DisableComp(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_SetupComp(int ctrl_id, int axis_id, int start_idx, double base_val, double interval, int num_pt, int ref_axis_id);
HIMC_API_API int HIMC_SetupComp2D(int ctrl_id, int axis_id, int start_idx, double *base_val, double *interval, int *num_pt, int *ref_axis_id);
HIMC_API_API int HIMC_SetupComp3D(int ctrl_id, int axis_id, int start_idx, double *base_val, double *interval, int *num_pt, int *ref_axis_id);
HIMC_API_API int HIMC_GetCompPos(int ctrl_id, int axis_id, double *p_comp_pos_set);


// ---------------------------------------------------------------//
// 12. Filter Functions                                           //
// ---------------------------------------------------------------//

HIMC_API_API int HIMC_EnableAxisVsf(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_DisableAxisVsf(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_SetAxisVsf(int ctrl_id, int axis_id, double frequency, double damping_ratio);
HIMC_API_API int HIMC_EnableAxisInshape(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_DisableAxisInshape(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_SetAxisInshape(int ctrl_id, int axis_id, double frequency, double damping_factor, ShaperMode shaper_type);
HIMC_API_API int HIMC_EnableGrpInShape(int ctrl_id, int group_id);
HIMC_API_API int HIMC_DisableGrpInShape(int ctrl_id, int group_id);
HIMC_API_API int HIMC_SetGrpInShape(int ctrl_id, int group_id, double frequency, double damping_ratio, ShaperMode shaper_type);


// ---------------------------------------------------------------//
// 13. HMPL Task Functions                                        //
// ---------------------------------------------------------------//

HIMC_API_API int HIMC_StartTask(int ctrl_id, int task_id);
HIMC_API_API int HIMC_StartTaskFunc(int ctrl_id, int task_id, char *func_name);
HIMC_API_API int HIMC_StopTask(int ctrl_id, int task_id);
HIMC_API_API int HIMC_StopAllTask(int ctrl_id);                     
HIMC_API_API int HIMC_IsTaskStop(int ctrl_id, int task_id, int *isStop);         


// ---------------------------------------------------------------//
// 14. Callback Functions                                         //
// ---------------------------------------------------------------//

// callback function
#ifndef WIN32
#ifndef __cdecl
#define __cdecl __attribute__((__cdecl__))
#endif /* __cdecl */
#endif /* WIN32 */

typedef void (__cdecl *HMPLEventCBFuncPtr)(int event_id);

HIMC_API_API int HIMC_SetHmplEvtCallback(int ctrl_id,
  HMPLEventCBFuncPtr hmpl_event_cb_func_ptr);

typedef void (__cdecl *HimcErrorCBFuncPtr)(int error_id);

HIMC_API_API int HIMC_SetErrorCallback(int ctrl_id,
  HimcErrorCBFuncPtr himc_error_cb_func_ptr);


// ---------------------------------------------------------------//
// 15. Variables Operating Functions                              //
// ---------------------------------------------------------------//

// -----------------15.2 Slave Variable Opearate------------------//

HIMC_API_API int HIMC_GetSlvVar(int ctrl_id, int slave_id, const char *var_name, double *p_var);
HIMC_API_API int HIMC_SetSlvVar(int ctrl_id, int slave_id, const char *var_name, double value); 
HIMC_API_API int HIMC_GetSlvSt(int ctrl_id, int slave_id, const char*st_name, int *on_off);
HIMC_API_API int HIMC_SetSlvSt(int ctrl_id, int slave_id, const char*st_name, int on_off);

// -----------------15.3 Slave PDL Function Opearate------------------//

HIMC_API_API int HIMC_RunSlvPdlFunc(int ctrl_id, int slave_id, const char* input_pdl_func_name);
HIMC_API_API int HIMC_StopSlvPdlFunc(int ctrl_id, int slave_id, const char* input_pdl_func_name);
HIMC_API_API int HIMC_IsSlvPdlFuncRunning(int ctrl_id, int slave_id, const char* input_pdl_func_name, int* p_ret_is_running);

// -----------------15.4 HIMC Variable Operate------------------//

HIMC_API_API int HIMC_GetVariableByID(int ctrl_id, int var_id, double *p_val);
HIMC_API_API int HIMC_SetVariableByID(int ctrl_id, int var_id, double val);
HIMC_API_API int HIMC_GetVariableListByID(int ctrl_id, int *p_var_id, int num, double *p_val);
HIMC_API_API int HIMC_SetVariableListByID(int ctrl_id, int *p_var_id, int num, double *p_val);
HIMC_API_API int HIMC_GetGlobalVariables(int ctrl_id, char **pp_var_name_array, int length, double *p_output_array);
HIMC_API_API int HIMC_SetGlobalVariables(int ctrl_id, char **pp_var_name_array, int length, double *p_input_array);


// ---------------------------------------------------------------//
// 16. HIMC Error Functions                                       //
// ---------------------------------------------------------------//

HIMC_API_API int HIMC_GetLastError(int ctrl_id, int *p_error_code);
HIMC_API_API int HIMC_GetAxisLastErr(int ctrl_id, int axis_id, int* err_code);
HIMC_API_API int HIMC_ClearAxisLastErr(int ctrl_id, int axis_id);
HIMC_API_API int HIMC_GetGrpLastErr(int ctrl_id, int group_id, int *err_code);
HIMC_API_API int HIMC_ClearGrpLastErr(int ctrl_id, int group_id);
// *p_name_len and *p_description_len not include the null charactor in the end
HIMC_API_API int HIMC_GetErrorInformation(int error_id,
  char *p_name, int name_buff_len, int *p_name_actual_len,
  char *p_description, int description_buff_len, int *p_description_actual_len);

// iA Studio 1.0 compatibility
HIMC_API_API int HIMC_IsOperMode(int ctrl_id, int *isOper);   
HIMC_API_API int HIMC_IsPreOpMode(int ctrl_id, int *isPreOp);  
HIMC_API_API int HIMC_GetSwPositiveLimitPos(int ctrl_id, int axis_id, double *p_positive_limit_pos);
HIMC_API_API int HIMC_SetSwPositiveLimitPos(int ctrl_id, int axis_id, double positive_limit_pos);
HIMC_API_API int HIMC_GetSwNegativeLimitPos(int ctrl_id, int axis_id, double *p_negative_limit_pos);
HIMC_API_API int HIMC_SetSwNegativeLimitPos(int ctrl_id, int axis_id, double negative_limit_pos);
HIMC_API_API int HIMC_StartHMPLTask(int ctrl_id, int task_id);
HIMC_API_API int HIMC_StopHMPLTask(int ctrl_id, int task_id);
HIMC_API_API int HIMC_GroupReset(int ctrl_id, int group_id);

//Server timeout setting
HIMC_API_API int HIMC_SetModbusTimeout(int ctrl_id, unsigned int timeout);
HIMC_API_API int HIMC_SetApiTimeout(int ctrl_id, unsigned int timeout);
HIMC_API_API int HIMC_SetAsciiTimeout(int ctrl_id, unsigned int timeout);

HIMC_API_API int HIMC_IsAcc(int ctrl_id, int axis_id,  int *p_enabled);

#ifdef __cplusplus
}
#endif

#endif