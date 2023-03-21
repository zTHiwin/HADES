﻿#include <cstdint>	// std::uint8_t
#include <vector>

#ifndef HRSDK_HRSDK_H_
#define HRSDK_HRSDK_H_

#ifdef HRSDK_HRSDK_H_
#define HRSDK_API __declspec(dllexport)
#else
#define HRSDK_API __declspec(dllimport)
#endif

typedef int HROBOT;
#ifdef __cplusplus
extern "C" {
#endif

enum ConnectionLevels {
	kVerMismatch = -2,
	kDisconnection = -1,
	kMonitor = 0,
	kController
};

enum OperationModes {
	kManual = 0,
	kAuto
};

enum LogLevels {
	kNone = 0,
	kInfo,
	kSetCommand,
	kConsole,
	kSave,
};

enum SpaceOperationTypes {
	kCartesian = 0,
	kJoint,
	kTool,
	kExt
};

enum SpaceOperationDirection {
	kPositive = 1,
	kNegative = -1,
};

enum JointCoordinates {
	kJoint1 = 0,
	kJoint2,
	kJoint3,
	kJoint4,
	kJoint5,
	kJoint6
};

enum CartesianCoordinates {
	kCartesianX = 0,
	kCartesianY,
	kCartesianZ,
	kCartesianA,
	kCartesianB,
	kCartesianC
};

enum RobotMotionStatus {
	kIdle = 1,
	kRunning,
	kHold,
	kDelay,
	kWait
};

/* Connection Command */
typedef void(__stdcall *callback_function)(uint16_t, uint16_t, uint16_t*, int);
HRSDK_API HROBOT __stdcall open_connection(const char* address, int level, callback_function f);
HRSDK_API int __stdcall disconnect(HROBOT robot);
HRSDK_API int __stdcall set_connection_level(HROBOT robot, int Mode);
HRSDK_API int __stdcall get_connection_level(HROBOT robot);
HRSDK_API int __stdcall get_hrsdk_version(char* version);
HRSDK_API void __stdcall set_log_level(int robot_handle, LogLevels log_level);

/* Register Command */
HRSDK_API int __stdcall set_timer(HROBOT robot, int index, int time);
HRSDK_API int __stdcall get_timer(HROBOT robot, int index);
HRSDK_API int __stdcall set_timer_start(HROBOT robot, int index);
HRSDK_API int __stdcall set_timer_stop(HROBOT robot, int index);
HRSDK_API int __stdcall set_timer_name(HROBOT robot, int index, wchar_t* comment);
HRSDK_API int __stdcall get_timer_name(HROBOT robot, int index, wchar_t* comment, int arr_size);
HRSDK_API int __stdcall get_timer_status(HROBOT robot, int index);
HRSDK_API int __stdcall set_counter(HROBOT robot, int index, int co);
HRSDK_API int __stdcall get_counter(HROBOT robot, int index);
HRSDK_API int __stdcall set_pr_type(HROBOT robot, int prNum, int coorType);
HRSDK_API int __stdcall get_pr_type(HROBOT robot, int prNum);
HRSDK_API int __stdcall set_pr_coordinate(HROBOT robot, int prNum, double *coor);
HRSDK_API int __stdcall get_pr_coordinate(HROBOT robot, int pr, double* coor);
HRSDK_API int __stdcall set_pr_tool_base(HROBOT robot, int prNum, int toolNum, int baseNum);
HRSDK_API int __stdcall get_pr_tool_base(HROBOT robot, int pr, int* tool_base);
HRSDK_API int __stdcall set_pr(HROBOT robot, int prNum, int coorType, double *coor, double *ext_pos, int tool, int base);
HRSDK_API int __stdcall get_pr(HROBOT robot, int pr_num, int* coor_type, double *coor, double *ext_pos, int* tool, int* base);
HRSDK_API int __stdcall remove_pr(HROBOT robot, int pr_num);
HRSDK_API int __stdcall set_pr_comment(HROBOT robot, int index, wchar_t* comment);
HRSDK_API int __stdcall get_pr_comment(HROBOT robot, int index, wchar_t* comment, int arr_size);
HRSDK_API int __stdcall get_counter_name(HROBOT robot, int index, wchar_t* name, int arr_size);
HRSDK_API int __stdcall set_counter_name(HROBOT robot, int index, wchar_t* name);

/* System Variable Command */
HRSDK_API int __stdcall set_acc_dec_ratio(HROBOT robot, int acc);
HRSDK_API int __stdcall get_acc_dec_ratio(HROBOT robot);
HRSDK_API int __stdcall set_acc_time(HROBOT robot, double value);
HRSDK_API double __stdcall get_acc_time(HROBOT robot);
HRSDK_API int __stdcall set_ptp_speed(HROBOT robot, int vel);
HRSDK_API int __stdcall get_ptp_speed(HROBOT robot);
HRSDK_API int __stdcall set_lin_speed(HROBOT robot, double vel);
HRSDK_API double __stdcall get_lin_speed(HROBOT robot);
HRSDK_API int __stdcall set_override_ratio(HROBOT robot, int vel);
HRSDK_API int __stdcall get_override_ratio(HROBOT robot);
HRSDK_API int __stdcall get_robot_id(HROBOT robot, char* robot_id);
HRSDK_API int __stdcall set_robot_id(HROBOT robot, char* robot_id);
HRSDK_API int __stdcall set_smooth_length(HROBOT robot, double r);
HRSDK_API int __stdcall get_alarm_code(HROBOT robot, int &count, uint64_t* alarm_code);
HRSDK_API int __stdcall get_alarm_log_count(HROBOT robot, int& size);
HRSDK_API int __stdcall get_alarm_log_msg(HROBOT robot, int idx, wchar_t* msg);

/* Input and Output Command */
HRSDK_API int __stdcall get_digital_input(HROBOT robot, int index);
HRSDK_API int __stdcall get_digital_output(HROBOT robot, int index);
HRSDK_API int __stdcall set_digital_output(HROBOT robot, int index, bool v);
HRSDK_API int __stdcall get_robot_input(HROBOT robot, int index);
HRSDK_API int __stdcall get_robot_output(HROBOT robot, int index);
HRSDK_API int __stdcall set_robot_output(HROBOT robot, int index, bool v);
HRSDK_API int __stdcall get_valve_output(HROBOT robot, int index);
HRSDK_API int __stdcall set_valve_output(HROBOT robot, int index, bool v);
HRSDK_API int __stdcall get_function_input(HROBOT robot, int index);
HRSDK_API int __stdcall get_function_output(HROBOT robot, int index);
HRSDK_API int __stdcall set_DI_simulation_Enable(HROBOT robot, int index, bool v);
HRSDK_API int __stdcall set_DI_simulation(HROBOT robot, int index, bool v);
HRSDK_API int __stdcall get_DI_simulation_Enable(HROBOT robot, int index);
HRSDK_API int  __stdcall set_digital_input_comment(HROBOT robot, int di_index, wchar_t* comment);
HRSDK_API int  __stdcall get_digital_input_comment(HROBOT robot, int di_index, wchar_t* comment, int arr_size);
HRSDK_API int  __stdcall set_digital_output_comment(HROBOT robot, int do_index, wchar_t* comment);
HRSDK_API int  __stdcall get_digital_output_comment(HROBOT robot, int do_index, wchar_t* comment, int arr_size);
HRSDK_API int __stdcall SyncOutput(HROBOT robot, int O_type, int O_id, int on_off, int synMode, int delay, int distance);

/*Module I/O 10/16*/
HRSDK_API int __stdcall get_module_input_config(HROBOT robot, int index, bool& sim, bool& value, int& type, int& start, int& end, wchar_t* comment, int arr_size);
HRSDK_API int __stdcall get_module_output_config(HROBOT robot, int index, bool& value, int& type, int& start, int& end, wchar_t* comment, int arr_size);
HRSDK_API int __stdcall set_module_input_simulation(HROBOT robot, int index, bool enable);
HRSDK_API int __stdcall set_module_input_value(HROBOT robot, int index, bool enable);
HRSDK_API int __stdcall set_module_input_start(HROBOT robot, int index, int start_number);
HRSDK_API int __stdcall set_module_input_end(HROBOT robot, int index, int end_number);
HRSDK_API int __stdcall set_module_input_comment(HROBOT robot, int index, wchar_t* comment);
HRSDK_API int __stdcall set_module_output_value(HROBOT robot, int index, bool enable);
HRSDK_API int __stdcall set_module_output_start(HROBOT robot, int index, int start_number);
HRSDK_API int __stdcall set_module_output_end(HROBOT robot, int index, int end_number);
HRSDK_API int __stdcall set_module_output_comment(HROBOT robot, int index, wchar_t* comment);
HRSDK_API int __stdcall set_module_input_type(HROBOT robot, int index, int type);
HRSDK_API int __stdcall set_module_output_type(HROBOT robot, int index, int type);
HRSDK_API int __stdcall save_module_io_setting(HROBOT robot);

/* Coordinate System Command */
HRSDK_API int __stdcall set_base_number(HROBOT robot, int state);
HRSDK_API int __stdcall get_base_number(HROBOT robot);
HRSDK_API int __stdcall define_base(HROBOT robot, int baseNum, double *coor);
HRSDK_API int __stdcall get_base_data(HROBOT robot, int num, double* coor);
HRSDK_API int __stdcall set_tool_number(HROBOT robot, int num);
HRSDK_API int __stdcall get_tool_number(HROBOT robot);
HRSDK_API int __stdcall define_tool(HROBOT robot, int toolNum, double *coor);
HRSDK_API int __stdcall get_tool_data(HROBOT robot, int num, double* coor);
HRSDK_API int __stdcall set_home_point(HROBOT robot, double * joint);
HRSDK_API int __stdcall get_home_point(HROBOT robot, double * joint);
HRSDK_API int __stdcall get_previous_pos(HROBOT robot, double * joint);
HRSDK_API int __stdcall enable_joint_soft_limit(HROBOT v, bool enable);
HRSDK_API int __stdcall enable_cart_soft_limit(HROBOT robot, bool enable);
HRSDK_API int __stdcall set_joint_soft_limit(HROBOT robot, double* low_limit, double* high_limit);
HRSDK_API int __stdcall set_cart_soft_limit(HROBOT robot, double* low_limit, double* high_limit);
HRSDK_API int __stdcall get_joint_soft_limit_config(HROBOT robot, bool& enable, double* low_limit, double* high_limit);
HRSDK_API int __stdcall get_cart_soft_limit_config(HROBOT robot, bool& enable, double* low_limit, double* high_limit);
HRSDK_API int __stdcall confirm_home_point(HROBOT robot);
HRSDK_API int __stdcall base_calibration(HROBOT robot, int calibrate_type, double* p0coor, double* p1coor, double* p2coor, double* result_coor);
HRSDK_API int __stdcall tool_calibration(HROBOT robot, int calibrate_type, double* p0coor, double* p1coor, double* p2coor, double* p3coor, double* result_coor);

/* Task Command */
HRSDK_API int __stdcall set_rsr(HROBOT robot, char* filename, int index);
HRSDK_API int __stdcall get_rsr_prog_name(HROBOT robot, int rsr_index, char* file_name);
HRSDK_API int __stdcall remove_rsr(HROBOT robot, int index);
HRSDK_API int __stdcall ext_task_start(HROBOT robot, int mode, int select);
HRSDK_API int __stdcall task_start(HROBOT robot, char* task_name);
HRSDK_API int __stdcall task_hold(HROBOT robot);
HRSDK_API int __stdcall task_continue(HROBOT robot);
HRSDK_API int __stdcall task_abort(HROBOT robot);
HRSDK_API int __stdcall get_execute_file_name(HROBOT robot, char* file_name);
HRSDK_API int __stdcall get_prog_number(HROBOT robot);
HRSDK_API int __stdcall get_prog_name(HROBOT robot, int file_index, char* file_name);

/* File Command */
HRSDK_API int __stdcall send_file(HROBOT sock, char* from_file_path, char* to_file_path);
HRSDK_API int __stdcall download_file(HROBOT robot, char* from_file_path, char* to_file_path);
HRSDK_API int __stdcall delete_file(HROBOT robot, char* FilePath);
HRSDK_API int __stdcall delete_folder(HROBOT robot, char* FilePath);
HRSDK_API int __stdcall new_folder(HROBOT robot, char* FilePath);
HRSDK_API int __stdcall file_rename(HROBOT robot, char* oldFilePath, char* newFilePath);
HRSDK_API int __stdcall file_drag(HROBOT robot, char* fromFilePath, char* toFilePath);

/* Controller Setting Command */
HRSDK_API int __stdcall get_hrss_mode(HROBOT robot);
HRSDK_API int __stdcall set_motor_state(HROBOT robot, int state);
HRSDK_API int __stdcall get_motor_state(HROBOT robot);
HRSDK_API int __stdcall set_operation_mode(HROBOT robot, int mode);
HRSDK_API int __stdcall get_operation_mode(HROBOT robot);
HRSDK_API int __stdcall clear_alarm(HROBOT robot);
HRSDK_API int __stdcall update_hrss(HROBOT robot, char* path);
HRSDK_API int __stdcall set_language(HROBOT srobot, int language_number);
HRSDK_API int __stdcall get_controller_time(HROBOT robot, int& year, int& month, int& day, int& hour, int& minute, int& second);
HRSDK_API int __stdcall get_robot_info(HROBOT s, int page_sel, int tool_num, int base_num, char* info, bool is_ready);
HRSDK_API int __stdcall mastering(HROBOT robot, char* joint, char* type);
HRSDK_API int __stdcall calibration(HROBOT robot, char* joint, char* type);

/* Jog */
HRSDK_API int __stdcall jog(HROBOT robot, int space_type, int index, int dir);
HRSDK_API int __stdcall jog_home(HROBOT robot);
HRSDK_API int __stdcall jog_stop(HROBOT robot);

/* Motion Command */
HRSDK_API int __stdcall ptp_pos(HROBOT robot, int mode, double * p);
HRSDK_API int __stdcall ptp_axis(HROBOT robot, int mode, double * p);
HRSDK_API int __stdcall ptp_rel_pos(HROBOT robot, int mode, double * p);
HRSDK_API int __stdcall ptp_rel_axis(HROBOT robot, int mode, double * p);
HRSDK_API int __stdcall ptp_pr(HROBOT robot, int mode, int p);
HRSDK_API int __stdcall ptp_point(HROBOT s, int mode, double* axis, double* pos, double* ext);
HRSDK_API int __stdcall lin_pos(HROBOT robot, int mode, double smooth_value, double * p);
HRSDK_API int __stdcall lin_axis(HROBOT robot, int mode, double smooth_value, double * p);
HRSDK_API int __stdcall lin_rel_pos(HROBOT robot, int mode, double smooth_value, double * p);
HRSDK_API int __stdcall lin_rel_axis(HROBOT robot, int mode, double smooth_value, double * p);
HRSDK_API int __stdcall lin_pr(HROBOT robot, int mode, double smooth_value, int p);
HRSDK_API int __stdcall circ_pos(HROBOT robot, int mode, double * p_aux, double * p_end);
HRSDK_API int __stdcall circ_axis(HROBOT robot, int mode, double * p_aux, double * p_end);
HRSDK_API int __stdcall circ_pr(HROBOT robot, int mode, int p1, int p2);
HRSDK_API int __stdcall motion_hold(HROBOT robot);
HRSDK_API int __stdcall motion_continue(HROBOT robot);
HRSDK_API int __stdcall motion_abort(HROBOT robot);
HRSDK_API int __stdcall motion_delay(HROBOT robot, int delay);
HRSDK_API int __stdcall set_command_id(HROBOT robot, int id);
HRSDK_API int __stdcall get_command_id(HROBOT robot);
HRSDK_API int __stdcall get_command_count(HROBOT robot);
HRSDK_API int __stdcall get_motion_state(HROBOT robot);
HRSDK_API int __stdcall remove_command(HROBOT robot, int num);
HRSDK_API int __stdcall remove_command_tail(HROBOT robot, int num);
HRSDK_API int __stdcall motion_reachable(HROBOT s, double* dest_coord, bool& is_reach);
HRSDK_API int __stdcall motion_check_lin(HROBOT s, double* coord1, double* coord2, bool& is_reach);

/* Manipulator Information Command */
HRSDK_API int __stdcall get_encoder_count(HROBOT robot, int32_t* EncCount);
HRSDK_API int __stdcall get_current_joint(HROBOT robot, double * joint);
HRSDK_API int __stdcall get_current_position(HROBOT robot, double * cart);
HRSDK_API int __stdcall get_position_b0t0(HROBOT robot, double* pos);
HRSDK_API int __stdcall get_current_rpm(HROBOT robot, double * rpm);
HRSDK_API int __stdcall get_device_born_date(HROBOT robot, int* YMD);
HRSDK_API int __stdcall get_operation_time(HROBOT robot, int* YMDHm);
HRSDK_API int __stdcall get_mileage(HROBOT robot, double * mil);
HRSDK_API int __stdcall get_total_mileage(HROBOT robot, double * tomil);
HRSDK_API int __stdcall get_utilization(HROBOT robot, int* utl);
HRSDK_API int __stdcall get_utilization_ratio(HROBOT robot, double& ratio);
HRSDK_API int __stdcall get_motor_torque(HROBOT robot, double * cur);
HRSDK_API int __stdcall get_robot_type(HROBOT robot, char* robType);
HRSDK_API int __stdcall get_hrss_version(HROBOT robot, char* ver);
HRSDK_API int __stdcall download_history_zip(HROBOT s, char* toFilePath);

/*User Alarm Setting*/
HRSDK_API int __stdcall get_user_alarm_setting_message(HROBOT robot, int num, char* message);
HRSDK_API int __stdcall set_user_alarm_setting_message(HROBOT robot, int num, char* message);

/*Payload*/
HRSDK_API int __stdcall get_payload_config(HROBOT robot, int index, double* value, char* comment);
HRSDK_API int __stdcall set_payload_config(HROBOT robot, int index, double* value, char* comment);
HRSDK_API int __stdcall get_payload_active(HROBOT robot, int& index);
HRSDK_API int __stdcall set_payload_active(HROBOT robot, int index);

/*DIO Setting*/
HRSDK_API int __stdcall get_digital_setting(HROBOT robot, int* index, char* text);
HRSDK_API int __stdcall set_digital_setting(HROBOT robot, int* index, char* text);

/*Network Config*/
HRSDK_API int __stdcall set_network_show_msg(HROBOT s, int enable);
HRSDK_API int __stdcall get_network_show_msg(HROBOT s, int& flag);
HRSDK_API int __stdcall network_connect(HROBOT s);
HRSDK_API int __stdcall network_disconnect(HROBOT s);
HRSDK_API int __stdcall network_send_msg(HROBOT s, char * msg);
HRSDK_API int __stdcall network_recieve_msg(HROBOT s, char * msg);
HRSDK_API int __stdcall get_network_config(HROBOT s, int& connect_type, char* ip_addr, int& port, int& bracket_type, int& separator_type, bool & is_format);
HRSDK_API int __stdcall set_network_config(HROBOT s, int connect_type, char* ip_addr, int port, int bracket_type, int separator_type, bool is_format);
HRSDK_API int __stdcall network_change_ip(HROBOT s, int lan_index, int ip_type, char * ip_addr);
HRSDK_API int __stdcall network_get_state(HROBOT s);

/* External Axis Setting*/
HRSDK_API int __stdcall get_ext_axis_setting(HROBOT s, int index, bool& enable, int& mode, double& high_limit, double& low_limit);
HRSDK_API int __stdcall set_ext_axis_setting(HROBOT s, int index, bool enable, int mode, double high_limit, double low_limit);
HRSDK_API int __stdcall get_ext_axis_setting_advanced(HROBOT s, int index, int& type, bool& math, bool& continuous, int* int_value, double* double_value);
HRSDK_API int __stdcall set_ext_axis_setting_advanced(HROBOT s, int index, int type, bool math, bool continuous, int* int_value, double* double_value);
HRSDK_API int __stdcall ext_mastering(HROBOT s, int index);
HRSDK_API int __stdcall get_current_ext_pos(HROBOT s, double* pos);
HRSDK_API int __stdcall get_current_ext_mode(HROBOT s, char* mode);
HRSDK_API int __stdcall set_ext_home_point(HROBOT robot, double * ext_pos);
HRSDK_API int __stdcall get_ext_home_point(HROBOT robot, double * ext_pos);
HRSDK_API int __stdcall get_previous_extpos(HROBOT robot, double * ext_pos);
HRSDK_API int __stdcall ext_ptp_axis(HROBOT s, int mode, double * p);
HRSDK_API int __stdcall ext_ptp_pos(HROBOT s, int mode, double * p);
HRSDK_API int __stdcall ext_lin_axis(HROBOT s, int mode, double smooth_value, double * p);
HRSDK_API int __stdcall ext_lin_pos(HROBOT s, int mode, double smooth_value, double * p);
HRSDK_API int __stdcall ext_asyptp(HROBOT s, int mode, double * p);
HRSDK_API int __stdcall set_ext_driver_limit(HROBOT s, int index, bool enable, bool inverse, int negative_num, int positive_num);
HRSDK_API int __stdcall get_ext_driver_limit(HROBOT s, int index, bool &enable, bool &inverse, int &negative_num, int &positive_num, bool &N_light, bool &P_light);
HRSDK_API int __stdcall get_ext_encoder(HROBOT s, int32_t* EncCount);

/* Home Warning Setting */
HRSDK_API int __stdcall get_home_warning_setting(HROBOT s, double* allow_error_value, double* allow_near_home);
HRSDK_API int __stdcall set_home_warning_setting(HROBOT s, double* allow_error_value, double* allow_near_home);

/* IO all value */
HRSDK_API int __stdcall get_DI_range(HROBOT s, int from_idx, int end_idx, int* value);
HRSDK_API int __stdcall get_DI_sim_range(HROBOT s, int from_idx, int end_idx, int* value);
HRSDK_API int __stdcall get_DI_comment_range(HROBOT s, int from_idx, int end_idx, wchar_t* str, int& next_idx);
HRSDK_API int __stdcall get_DO_range(HROBOT s, int from_idx, int end_idx, int* value);
HRSDK_API int __stdcall get_DO_comment_range(HROBOT s, int from_idx, int end_idx, wchar_t* str, int& next_idx);
HRSDK_API int __stdcall get_FI_all(HROBOT s, int* value);
HRSDK_API int __stdcall get_FO_all(HROBOT s, int* value);
HRSDK_API int __stdcall get_timer_status_all(HROBOT s, int* value);
HRSDK_API int __stdcall get_timer_value_all(HROBOT s, int* value);
HRSDK_API int __stdcall get_timer_comment_range(HROBOT s, int from_idx, int end_idx, wchar_t* str, int& next_idx);
HRSDK_API int __stdcall get_counter_value_all(HROBOT s, int* value);
HRSDK_API int __stdcall get_counter_comment_range(HROBOT s, int from_idx, int end_idx, wchar_t* str, int& next_idx);
HRSDK_API int __stdcall get_fieldbus_rs_srw_range(HROBOT s, int from_idx, int end_idx, int* value);
HRSDK_API int __stdcall get_fieldbus_rs_srr_range(HROBOT s, int from_idx, int end_idx, int* value);
HRSDK_API int __stdcall get_fieldbus_rs_parameter_range(HROBOT s, int from_idx, int end_idx, wchar_t* str, int& next_idx);
HRSDK_API int __stdcall get_fieldbus_rs_comment_range(HROBOT s, int from_idx, int end_idx, wchar_t* str, int& next_idx);
HRSDK_API int __stdcall get_system_input_all(HROBOT s, int* value, wchar_t* comment);
HRSDK_API int __stdcall get_system_output_all(HROBOT s, int* value, wchar_t* comment);
HRSDK_API int __stdcall get_MI_config_all(HROBOT s, int* sim, int* value, int* type, int* start, int* end);
HRSDK_API int __stdcall get_MI_comment_range(HROBOT s, int from_idx, int end_idx, wchar_t* str, int& next_idx);
HRSDK_API int __stdcall get_MO_config_all(HROBOT s, int* value, int* type, int* start, int* end);
HRSDK_API int __stdcall get_MO_comment_range(HROBOT s, int from_idx, int end_idx, wchar_t* str, int& next_idx);
HRSDK_API int __stdcall get_PR_comment_array(HROBOT s, int* idx, int from_idx, int len, wchar_t* str, int& next_idx);
HRSDK_API int __stdcall get_SI_range(HROBOT s, int from_idx, int end_idx, int* value);
HRSDK_API int __stdcall get_SI_sim_range(HROBOT s, int from_idx, int end_idx, int* value);
HRSDK_API int __stdcall get_SO_range(HROBOT s, int from_idx, int end_idx, int* value);
HRSDK_API int __stdcall get_SI_comment_range(HROBOT s, int from_idx, int end_idx, wchar_t* str, int& next_idx);
HRSDK_API int __stdcall get_SO_comment_range(HROBOT s, int from_idx, int end_idx, wchar_t* str, int& next_idx);
HRSDK_API int __stdcall get_PR_array(HROBOT s, int* idx, int from_idx, int len, int* type, double* pos, int* tool, int* base, int& next_idx);
HRSDK_API int __stdcall get_RI_all(HROBOT s, int* values);
HRSDK_API int __stdcall get_RO_all(HROBOT s, int* values);
HRSDK_API int __stdcall get_VO_all(HROBOT s, int* values);

/*Set All IO*/
HRSDK_API int __stdcall set_DI_array(HROBOT s, int* indexes, int* values, int len);
HRSDK_API int __stdcall set_DI_sim_array(HROBOT s, int* indexes, int* values, int len);
HRSDK_API int __stdcall set_DO_array(HROBOT s, int* indexes, int* values, int len);
HRSDK_API int __stdcall set_timer_value_array(HROBOT s, int* indexes, int* values, int len);
HRSDK_API int __stdcall set_counter_array(HROBOT s, int* indexes, int* values, int len);
HRSDK_API int __stdcall set_fieldbus_srw_array(HROBOT s, int* indexes, int* values, int len);
HRSDK_API int __stdcall set_SI_array(HROBOT s, int* indexes, int* values, int len);
HRSDK_API int __stdcall set_SI_sim_array(HROBOT s, int* indexes, int* values, int len);
HRSDK_API int __stdcall set_SO_array(HROBOT s, int* indexes, int* values, int len);
HRSDK_API int __stdcall set_MO_array(HROBOT s, int* indexes, int* values, int len);
HRSDK_API int __stdcall set_VO_array(HROBOT s, int* indexes, int* values, int len);
HRSDK_API int __stdcall set_RO_array(HROBOT s, int* indexes, int* values, int len);

HRSDK_API int __stdcall get_hrss_sdkver(HROBOT s, int& large_ver, int& small_ver, int& revision);
HRSDK_API int __stdcall get_hrsdk_sdkver(int& large_ver, int& small_ver, int& revision);

// Robot Data
HRSDK_API int __stdcall get_robot_data(HROBOT robot, int* sys_info, int* port_info, double* axis_info);
HRSDK_API int __stdcall get_robot_dh(HROBOT robot, int type, double dh_value[][6]);
HRSDK_API int __stdcall get_gear_ratio(HROBOT robot, double gear_ratio[6]);		
extern uint16_t ts;

#ifdef __cplusplus
}
#endif
#endif // HRSDK_HRSDK_H_
