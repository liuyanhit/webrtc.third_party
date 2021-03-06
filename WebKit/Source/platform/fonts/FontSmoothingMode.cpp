// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "platform/fonts/FontSmoothingMode.h"

#include "platform/wtf/text/WTFString.h"

namespace blink {

String ToString(FontSmoothingMode mode) {
  switch (mode) {
    case kAutoSmoothing:
      return "Auto";
    case kNoSmoothing:
      return "None";
    case kAntialiased:
      return "Antialiased";
    case kSubpixelAntialiased:
      return "SubpixelAntialiased";
  }
  return "Unknown";
}

}  // namespace blink
