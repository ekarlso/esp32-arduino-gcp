/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.2 at Fri Nov 16 00:14:51 2018. */

#ifndef PB_SENSOR_SENSOR_PB_H_INCLUDED
#define PB_SENSOR_SENSOR_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _sensor_SensorEvents {
    pb_callback_t events;
/* @@protoc_insertion_point(struct:sensor_SensorEvents) */
} sensor_SensorEvents;

typedef struct _sensor_SensorEvent {
    int64_t event_id;
    int64_t timestamp;
    int64_t device_id;
    pb_callback_t values;
/* @@protoc_insertion_point(struct:sensor_SensorEvent) */
} sensor_SensorEvent;

typedef struct _sensor_Value {
    int64_t type;
    int32_t timestamp;
    pb_size_t which_value;
    union {
        int32_t sint_v;
        double double_v;
        float float_v;
    } value;
/* @@protoc_insertion_point(struct:sensor_Value) */
} sensor_Value;

/* Default values for struct fields */

/* Initializer values for message structs */
#define sensor_Value_init_default                {0, 0, 0, {0}}
#define sensor_SensorEvent_init_default          {0, 0, 0, {{NULL}, NULL}}
#define sensor_SensorEvents_init_default         {{{NULL}, NULL}}
#define sensor_Value_init_zero                   {0, 0, 0, {0}}
#define sensor_SensorEvent_init_zero             {0, 0, 0, {{NULL}, NULL}}
#define sensor_SensorEvents_init_zero            {{{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define sensor_SensorEvents_events_tag           1
#define sensor_SensorEvent_event_id_tag          1
#define sensor_SensorEvent_timestamp_tag         2
#define sensor_SensorEvent_device_id_tag         3
#define sensor_SensorEvent_values_tag            4
#define sensor_Value_sint_v_tag                  3
#define sensor_Value_double_v_tag                4
#define sensor_Value_float_v_tag                 5
#define sensor_Value_type_tag                    1
#define sensor_Value_timestamp_tag               2

/* Struct field encoding specification for nanopb */
extern const pb_field_t sensor_Value_fields[6];
extern const pb_field_t sensor_SensorEvent_fields[5];
extern const pb_field_t sensor_SensorEvents_fields[2];

/* Maximum encoded size of messages (where known) */
#define sensor_Value_size                        26
/* sensor_SensorEvent_size depends on runtime parameters */
/* sensor_SensorEvents_size depends on runtime parameters */

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define SENSOR_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
