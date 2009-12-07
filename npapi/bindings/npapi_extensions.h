/* Copyright (c) 2006-2009 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef _NP_EXTENSIONS_H_
#define _NP_EXTENSIONS_H_

#include "third_party/npapi/bindings/npapi.h"

/*
 * A fake "enum" value for getting Pepper extensions.
 * The variable returns a pointer to an NPPepperExtensions structure
 */
#define NPNVPepperExtensions ((NPNVariable) 4000)

typedef void NPDeviceConfig;
typedef void NPDeviceContext;
typedef void NPUserData;

/* unique id for each device interface */
typedef int32 NPDeviceID;

/* completion callback for flush device */
typedef void (*NPDeviceFlushContextCallbackPtr)(
    NPP instace,
    NPDeviceContext* context,
    NPError err,
    NPUserData* userData);

/* query single capabilities of device */
typedef NPError (
    *NPDeviceQueryCapabilityPtr)(NPP instance,
    int32 capability,
    int32 *value);
/* query config (configuration == a set of capabilities) */
typedef NPError (
    *NPDeviceQueryConfigPtr)(NPP instance,
    const NPDeviceConfig* request,
    NPDeviceConfig* obtain);
/* device initialization */
typedef NPError (*NPDeviceInitializeContextPtr)(
    NPP instance,
    const NPDeviceConfig* config,
    NPDeviceContext* context);
/* peek at device state */
typedef NPError (*NPDeviceGetStateContextPtr) (
    NPP instance,
    NPDeviceContext* context,
    int32 state,
    int32 *value);
/* poke device state */
typedef NPError (*NPDeviceSetStateContextPtr) (
    NPP instance,
    NPDeviceContext* context,
    int32 state,
    int32 value);
/* flush context, if callback, userData are NULL */
/* this becomes a blocking call */
typedef NPError (*NPDeviceFlushContextPtr)(
    NPP instance,
    NPDeviceContext* context,
    NPDeviceFlushContextCallbackPtr callback,
    void* userData);
/* destroy device context.  Application responsible for */
/* freeing context, if applicable */
typedef NPError (*NPDeviceDestroyContextPtr)(
    NPP instance,
    NPDeviceContext* context);

/* forward decl typdef structs */
typedef struct NPDevice NPDevice;
typedef struct NPExtensions NPExtensions;

/* generic device interface */
struct NPDevice {
  NPDeviceQueryCapabilityPtr queryCapability;
  NPDeviceQueryConfigPtr queryConfig;
  NPDeviceInitializeContextPtr initializeContext;
  NPDeviceSetStateContextPtr setStateContext;
  NPDeviceGetStateContextPtr getStateContext;
  NPDeviceFlushContextPtr flushContext;
  NPDeviceDestroyContextPtr destroyContext;
};

/* returns NULL if deviceID unavailable / unrecognized */
typedef NPDevice* (*NPAcquireDevicePtr)(
    NPP instance,
    NPDeviceID device);

/* Pepper extensions */
struct NPExtensions {
  /* Device interface acquisition */
  NPAcquireDevicePtr acquireDevice;
};

/* Events -------------------------------------------------------------------*/

typedef enum {
  NPMouseButton_None    = -1,
  NPMouseButton_Left    = 0,
  NPMouseButton_Middle  = 1,
  NPMouseButton_Right   = 2,
} NPMouseButtons;

typedef enum {
  NPEventType_Undefined   = -1,
  NPEventType_MouseDown   = 0,
  NPEventType_MouseUp     = 1,
  NPEventType_MouseMove   = 2,
  NPEventType_MouseEnter  = 3,
  NPEventType_MouseLeave  = 4,
  NPEventType_MouseWheel  = 5,
  NPEventType_RawKeyDown  = 6,
  NPEventType_KeyDown     = 7,
  NPEventType_KeyUp       = 8,
  NPEventType_Char        = 9,
  NPEventType_Minimize    = 10,
  NPEventType_Focus       = 11,
  NPEventType_Device      = 12
} NPEventTypes;

typedef enum {
  NPEventModifier_ShiftKey         = 1 << 0,
  NPEventModifier_ControlKey       = 1 << 1,
  NPEventModifier_AltKey           = 1 << 2,
  NPEventModifier_MetaKey          = 1 << 3,
  NPEventModifier_IsKeyPad         = 1 << 4,
  NPEventModifier_IsAutoRepeat     = 1 << 5,
  NPEventModifier_LeftButtonDown   = 1 << 6,
  NPEventModifier_MiddleButtonDown = 1 << 7,
  NPEventModifier_RightButtonDown  = 1 << 8
} NPEventModifiers;

typedef struct _NPKeyEvent
{
  uint32 modifier;
  uint32 normalizedKeyCode;
} NPKeyEvent;

typedef struct _NPCharacterEvent
{
  uint32 modifier;
  uint16 text[4];
  uint16 unmodifiedText[4];
} NPCharacterEvent;

typedef struct _NPMouseEvent
{
  uint32 modifier;
  int32 button;
  int32 x;
  int32 y;
  int32 clickCount;
} NPMouseEvent;

typedef struct _NPMouseWheelEvent
{
  uint32 modifier;
  float deltaX;
  float deltaY;
  float wheelTicksX;
  float wheelTicksY;
  uint32 scrollByPage;
} NPMouseWheelEvent;

typedef struct _NPDeviceEvent {
  uint32 device_uid;
  uint32 subtype;
  /* uint8 generic[0]; */
} NPDeviceEvent;

typedef struct _NPMinimizeEvent {
  int32 value;
} NPMinimizeEvent;

typedef struct _NPFocusEvent {
  int32 value;
} NPFocusEvent;

typedef struct _NPPepperEvent
{
  uint32 size;
  int32 type;
  double timeStampSeconds;
  union {
    NPKeyEvent key;
    NPCharacterEvent character;
    NPMouseEvent mouse;
    NPMouseWheelEvent wheel;
    NPMinimizeEvent minimize;
    NPFocusEvent focus;
    NPDeviceEvent device;
  } u;
} NPPepperEvent;

/* 2D -----------------------------------------------------------------------*/

#define NPPepper2DDevice 1

typedef struct _NPDeviceContext2DConfig {
} NPDeviceContext2DConfig;

typedef struct _NPDeviceContext2D
{
  union {
    struct {
      void* region;
      int32 stride;

      /* The dirty region that the plugin has painted into the buffer. This
       * will be initialized to the size of the plugin image in
       * initializeRenderContextPtr. The plugin can change the values to only
       * update portions of the image.
       */
      struct {
        int32 left;
        int32 top;
        int32 right;
        int32 bottom;
      } dirty;
    } graphicsRgba;
  } u;
} NPDeviceContext2D;

/* 3D -----------------------------------------------------------------------*/

#define NPPepper3DDevice 2

typedef struct _NPDeviceContext3DConfig {
} NPDeviceContext3DConfig;

typedef struct _NPDeviceContext3D
{
  void* buffer;
  int32 bufferLength;
} NPDeviceContext3D;

#endif  /* _NP_EXTENSIONS_H_ */
