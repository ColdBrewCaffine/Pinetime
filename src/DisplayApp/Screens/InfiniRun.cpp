#include <libs/lvgl/lvgl.h>
#include <libraries/log/nrf_log.h>
#include "InfiniRun.h"
#include "../DisplayApp.h"

using namespace Pinetime::Applications::Screens;
extern lv_font_t jetbrains_mono_extrabold_compressed;
extern lv_font_t jetbrains_mono_bold_20;

//extern static lv_img_dsc_t bitmap; 

lv_obj_t *img_src_1;
lv_obj_t *img_src_2;

InfiniRun::InfiniRun(Pinetime::Applications::DisplayApp *app, Pinetime::Components::LittleVgl& lvgl) : Screen(app){
  app->SetTouchMode(DisplayApp::TouchModes::Polling);
  
  paddle.header.always_zero = 0;
  paddle.header.w = 4;
  paddle.header.h = 60;
  paddle.data_size = 60 * 4 * LV_COLOR_SIZE / 8;
  paddle.header.cf = LV_IMG_CF_TRUE_COLOR;
  paddle.data = paddle_map;  
  img_src_1 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(img_src_1, &paddle);
  
  ball.header.always_zero = 0;
  ball.header.w = 24;
  ball.header.h = 24;
  ball.data_size = 24 * 24 * LV_COLOR_SIZE / 8;
  ball.header.cf = LV_IMG_CF_TRUE_COLOR;
  ball.data = ball_map;  
  img_src_2 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(img_src_2, &ball);
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
   
  lv_obj_set_pos(img_src_1, 0, 0);  
  return true; 
}

bool InfiniRun::OnTouchEvent(uint16_t x, uint16_t y) {
 
  lv_obj_set_pos(img_src, 0, y - 30);
 // lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::None);
 // lvgl.FlushDisplay(&area, b);
  return true;
}

