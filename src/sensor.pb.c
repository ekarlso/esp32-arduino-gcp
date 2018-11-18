/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.2 at Fri Nov 16 00:14:51 2018. */

#include "sensor.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t sensor_Value_fields[6] = {
    PB_FIELD(  1, INT64   , SINGULAR, STATIC  , FIRST, sensor_Value, type, type, 0),
    PB_FIELD(  2, SINT32  , SINGULAR, STATIC  , OTHER, sensor_Value, timestamp, type, 0),
    PB_ONEOF_FIELD(value,   3, SINT32  , ONEOF, STATIC  , OTHER, sensor_Value, sint_v, timestamp, 0),
    PB_ONEOF_FIELD(value,   4, DOUBLE  , ONEOF, STATIC  , UNION, sensor_Value, double_v, timestamp, 0),
    PB_ONEOF_FIELD(value,   5, FLOAT   , ONEOF, STATIC  , UNION, sensor_Value, float_v, timestamp, 0),
    PB_LAST_FIELD
};

const pb_field_t sensor_SensorEvent_fields[5] = {
    PB_FIELD(  1, INT64   , SINGULAR, STATIC  , FIRST, sensor_SensorEvent, event_id, event_id, 0),
    PB_FIELD(  2, INT64   , SINGULAR, STATIC  , OTHER, sensor_SensorEvent, timestamp, event_id, 0),
    PB_FIELD(  3, INT64   , SINGULAR, STATIC  , OTHER, sensor_SensorEvent, device_id, timestamp, 0),
    PB_FIELD(  4, MESSAGE , REPEATED, CALLBACK, OTHER, sensor_SensorEvent, values, device_id, &sensor_Value_fields),
    PB_LAST_FIELD
};

const pb_field_t sensor_SensorEvents_fields[2] = {
    PB_FIELD(  1, MESSAGE , REPEATED, CALLBACK, FIRST, sensor_SensorEvents, events, events, &sensor_SensorEvent_fields),
    PB_LAST_FIELD
};


/* @@protoc_insertion_point(eof) */