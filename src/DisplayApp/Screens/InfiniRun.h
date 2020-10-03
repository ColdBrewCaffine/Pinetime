#pragma once

#include <cstdint>
#include "Screen.h"
#include <bits/unique_ptr.h>
#include <libs/lvgl/src/lv_core/lv_style.h>
#include <libs/lvgl/src/lv_core/lv_obj.h>
#include <drivers/St7789.h>
#include <DisplayApp/LittleVgl.h>

namespace Pinetime {
  namespace Applications {
    namespace Screens {

      class InfiniRun : public Screen{
        public:
          InfiniRun(DisplayApp* app, Pinetime::Components::LittleVgl& lvgl);
          ~InfiniRun() override;

          bool Refresh() override;
          bool OnButtonPushed() override;
          bool OnTouchEvent(TouchEvents event) override;
        
      };
    }
  }
}
