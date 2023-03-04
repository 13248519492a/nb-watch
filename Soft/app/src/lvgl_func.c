#include "lvgl_func.h"
#include "tim.h"
#include "lcd.h"
extern lv_indev_t * indev_keypad;
extern uint8_t Lcd_Bck_Pwm;
extern unsigned char gImage_setting[];

static lv_group_t * g;
static lv_obj_t * set_bck_slider;
static lv_obj_t * set_bck_slider_label;

static lv_style_t slider_main_style;
static lv_style_t slider_knob_style;
static lv_style_t slider_indicator_style;

/******************************************************************************
      函数说明：设置背光源事件函数
      入口数据：无
      返回值：  无
******************************************************************************/
static void slider_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch(code)
	{
		case LV_EVENT_VALUE_CHANGED:
			HAL_TIM_Base_Stop(&htim11);
			__HAL_TIM_SET_COUNTER(&htim11, 0);
			lv_label_set_text_fmt(set_bck_slider_label, "%d%%", (int)lv_slider_get_value(set_bck_slider));
			Lcd_Bck_Pwm = (uint8_t)lv_slider_get_value(set_bck_slider);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, Lcd_Bck_Pwm);
			HAL_TIM_Base_Start_IT(&htim11);
			break;
	}
}



/******************************************************************************
      函数说明：设置滑动条样式
      入口数据：无
      返回值：  无
******************************************************************************/
void set_slider_style(void)
{
	lv_style_init(&slider_main_style);
	lv_style_set_bg_color(&slider_main_style, lv_color_hex(0x1e1e1e));
	lv_style_set_radius(&slider_main_style, 15);
	lv_style_set_pad_left(&slider_main_style, -2);
	lv_style_set_pad_right(&slider_main_style, -2);
	
	lv_style_init(&slider_knob_style);
	lv_style_set_opa(&slider_knob_style, LV_OPA_0);
	
	lv_style_init(&slider_indicator_style);
	lv_style_set_bg_color(&slider_indicator_style, lv_color_hex(0xffffff));
	lv_style_set_bg_opa(&slider_indicator_style, LV_OPA_100);
	lv_style_set_radius(&slider_indicator_style, 0);
}
/******************************************************************************
      函数说明：lvgl界面初始化配置函数
      入口数据：无
      返回值：  无
******************************************************************************/
void lvgl_init(void)
{
	g = lv_group_create();
	lv_group_set_default(g);
	lv_indev_set_group(indev_keypad, g);
	set_slider_style();
}



/******************************************************************************
      函数说明：lvgl主界面函数
      入口数据：无
      返回值：  无
******************************************************************************/
void lvgl_home(void)
{
	lv_obj_t *btn = lv_btn_create(lv_scr_act());
	lv_style_t btn_style;

	lv_style_init(&btn_style);
	lv_obj_set_size(btn, 60, 60);
	lv_style_set_radius(&btn_style, 30);
	lv_obj_add_style(btn, &btn_style, LV_STATE_DEFAULT);
	lv_obj_center(btn);
}



static void demo_btn_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if(code == LV_EVENT_PRESSED)
	{
	}
}


void demo(void)
{
	lv_obj_t *btn = lv_btn_create(lv_scr_act());
	lv_obj_center(btn);
	lv_obj_set_size(btn, 60, 60);
	lv_obj_add_event_cb(btn, demo_btn_event_cb, LV_EVENT_ALL, NULL);
}	


/******************************************************************************
      函数说明：设置背光源界面
      入口数据：无
      返回值：  无
******************************************************************************/
void set_bck(void)
{
	set_bck_slider = lv_slider_create(lv_scr_act());
	set_bck_slider_label = lv_label_create(lv_scr_act());
	lv_obj_t *set_bck_slider_name_label = lv_label_create(lv_scr_act());
	lv_obj_t * set_bck_slider_label_picture1 = lv_label_create(set_bck_slider);
	lv_obj_t * set_bck_slider_label_picture2 = lv_label_create(set_bck_slider);
	
	lv_obj_center(set_bck_slider);
	lv_obj_add_event_cb(set_bck_slider, slider_event_cb, LV_EVENT_ALL, NULL);
	lv_slider_set_value(set_bck_slider, Lcd_Bck_Pwm, LV_ANIM_OFF);
	lv_obj_set_size(set_bck_slider, 200, 50);
	lv_slider_set_range(set_bck_slider, 0, 100);
	lv_obj_add_style(set_bck_slider, &slider_main_style, LV_PART_MAIN);
	lv_obj_add_style(set_bck_slider, &slider_knob_style, LV_PART_KNOB);
	lv_obj_add_style(set_bck_slider, &slider_indicator_style, LV_PART_INDICATOR);
	
	lv_obj_align_to(set_bck_slider_label, set_bck_slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
	lv_label_set_text_fmt(set_bck_slider_label, "%d%%", Lcd_Bck_Pwm);
	
	lv_obj_align_to(set_bck_slider_name_label, set_bck_slider, LV_ALIGN_OUT_BOTTOM_MID, -10, -45);
	lv_label_set_text(set_bck_slider_name_label, "set bck");

	lv_obj_set_style_text_font(set_bck_slider_label_picture1, &lv_font_montserrat_20, 0);
	lv_label_set_text(set_bck_slider_label_picture1, LV_SYMBOL_PLUS);
	lv_obj_align(set_bck_slider_label_picture1, LV_ALIGN_BOTTOM_RIGHT, -5, -14);
	
	lv_obj_set_style_text_font(set_bck_slider_label_picture2, &lv_font_montserrat_20, 0);
	lv_label_set_text(set_bck_slider_label_picture2, LV_SYMBOL_MINUS);
	lv_obj_align(set_bck_slider_label_picture2, LV_ALIGN_BOTTOM_LEFT, 5, -14);
}
