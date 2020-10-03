#include <libs/lvgl/lvgl.h>
#include <libraries/log/nrf_log.h>
#include "InfiniRun.h"
#include "../DisplayApp.h"

using namespace Pinetime::Applications::Screens;
extern lv_font_t jetbrains_mono_extrabold_compressed;
extern lv_font_t jetbrains_mono_bold_20;

InfiniRun::InfiniRun(Pinetime::Applications::DisplayApp *app, Pinetime::Components::LittleVgl& lvgl) : Screen(app){
  app->SetTouchMode(DisplayApp::TouchModes::Polling);
}

InfiniRun::~InfiniRun() {
  // Reset the touchmode
  app->SetTouchMode(DisplayApp::TouchModes::Gestures);
  lv_obj_clean(lv_scr_act());
}

bool InfiniRun::Refresh() {
  return running;
}

bool InfiniRun::OnButtonPushed() {
  running = false;
  return true;
}

bool InfiniRun::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  return true;
}
