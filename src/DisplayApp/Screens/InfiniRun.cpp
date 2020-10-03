#include <libs/lvgl/lvgl.h>
#include <libraries/log/nrf_log.h>
#include "InfiniRun.h"
#include "../DisplayApp.h"

using namespace Pinetime::Applications::Screens;
extern lv_font_t jetbrains_mono_extrabold_compressed;
extern lv_font_t jetbrains_mono_bold_20;

//extern static lv_img_dsc_t bitmap; 
 lv_obj_t *img_src = lv_img_create(lv_scr_act(), NULL);

InfiniRun::InfiniRun(Pinetime::Applications::DisplayApp *app, Pinetime::Components::LittleVgl& lvgl) : Screen(app){
  app->SetTouchMode(DisplayApp::TouchModes::Polling);
  bitmap.header.always_zero = 0;
  bitmap.header.w = 240;
  bitmap.header.h = 240;
  bitmap.data_size = 240 * 240 * LV_COLOR_SIZE / 8;
  bitmap.header.cf = LV_IMG_CF_TRUE_COLOR;
  bitmap.data = bitmap_map;  
  lv_img_set_src(img_src, &bitmap);
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
   
  lv_obj_set_pos(img_src, 0, 0);  
  return true; 
}

bool InfiniRun::OnTouchEvent(uint16_t x, uint16_t y) {
 
  lv_obj_set_pos(img_src, x, y);
 // lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::None);
 // lvgl.FlushDisplay(&area, b);
  return true;
}

