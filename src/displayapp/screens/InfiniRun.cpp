#include <libs/lvgl/lvgl.h>
#include <libraries/log/nrf_log.h>
#include "InfiniRun.h"
#include "../DisplayApp.h"

using namespace Pinetime::Applications::Screens;
extern lv_font_t jetbrains_mono_extrabold_compressed;
extern lv_font_t jetbrains_mono_bold_20;


lv_obj_t *img_src_1;		// pointer to paddle image
lv_obj_t *img_src_2;		// pointer to ball image

int x_1 = 0;
int y_1 = 90;		// bottom extreme of the paddle

int x_2 = 0;
int y_2 = 150;		//top extreme of the paddle

int pos_x = 108;	// Initial x_coordinate for the ball (12px offset from the center to counteract the ball's 24px size)
int pos_y = 108;	// Initial y_coordinate for the ball

int dx = 3;		// Velocity of the ball in the x_coordinate
int dy = 2;		// Velocity of the ball in the y_coordinate

int counter = 0;	// init Frame refresh limit counter

int score = 0;

char Val[10];

InfiniRun::InfiniRun(Pinetime::Applications::DisplayApp *app, Pinetime::Components::LittleVgl& lvgl) : Screen(app){
  app->SetTouchMode(DisplayApp::TouchModes::Polling);
	
  points = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(points, "0");
  lv_obj_align(points, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 0);
	
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
  
  if((counter++ % 5) == 0){

    counter = 0;	
    
    pos_x += dx;
    pos_y += dy;	    
	  
    lv_obj_set_pos(img_src_2, pos_x, pos_y);
  
    //checks if it has touched the sides (floor and ceiling)	  
    if(pos_y <= 0 || pos_y >= 216){
      dy *= -1;
    }
  
    //checks if it has touched the side (left side)  
    if(pos_x >= 216){
      dx *= -1; 
    }
  
    //checks if it is in the position of the paddle	  
    if(pos_x <= 4 && pos_y >= y_1 && pos_y <= y_2){
      dx *= -1;   
      score++;
    }
	  
    //checks if it has gone behind the paddle
    else if(pos_x <= -40){
      pos_x = 108;
      pos_y = 108; 
      score = 0;	    
    } 
    sprintf(Val, "%d", score);	
    lv_label_set_text(points, Val);	  
  }      
  return running;
}

bool InfiniRun::OnButtonPushed() {
  running = false;
  return true;
}


bool InfiniRun::OnTouchEvent(Pinetime::Applications::TouchEvents event) { 
  return true; 
}

bool InfiniRun::OnTouchEvent(uint16_t x, uint16_t y) {
 
  lv_obj_set_pos(img_src_1, 0, y - 30);		// sets the center paddle pos. (30px offset) with the the y_coordinate of the finger and defaults the x_coordinate to 0
  y_1 = y - 30;					// refreshes the upper extreme of the paddle
  y_2 = y + 30;					// refreshes the upper extreme of the paddle
  
 // lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::None);
 // lvgl.FlushDisplay(&area, b);
  return true;
}
