#include "lvgl_func.h"
#include "tim.h"
extern lv_indev_t * indev_keypad;
extern uint8_t Lcd_Bck_Pwm;
extern unsigned char gImage_setting[];

static lv_group_t * g;
static lv_obj_t * set_bck_slider;
static lv_obj_t * set_bck_slider_label;
static void btn_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch(code)
	{
		case LV_EVENT_PRESSED:
			lv_ShowPicture(0, 0, 120, 120, gImage_setting);
			break;
	}
}
static void slider_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch(code)
	{
		case LV_EVENT_VALUE_CHANGED:
			lv_label_set_text_fmt(set_bck_slider_label, "%d%%", (int)lv_slider_get_value(set_bck_slider));
			Lcd_Bck_Pwm = (uint8_t)lv_slider_get_value(set_bck_slider);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, Lcd_Bck_Pwm);
			break;
	}
}

void lvgl_init(void)
{
	g = lv_group_create();
	lv_group_set_default(g);
	lv_indev_set_group(indev_keypad, g);
}

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


void demo(void)
{
	lv_group_t *g = lv_group_create();
	lv_group_set_default(g);
	lv_indev_set_group(indev_keypad, g);
	
	lv_obj_t *btn = lv_btn_create(lv_scr_act());
	lv_obj_t *slider = lv_slider_create(lv_scr_act());
	
	lv_obj_center(btn);
	lv_obj_set_size(btn, 60, 60);
	lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);
}	

void set_bck(void)
{
	set_bck_slider = lv_slider_create(lv_scr_act());
	set_bck_slider_label = lv_label_create(lv_scr_act());
	lv_obj_t *set_bck_slider_name_label = lv_label_create(lv_scr_act());
	
	lv_obj_center(set_bck_slider);
	lv_obj_add_event_cb(set_bck_slider, slider_event_cb, LV_EVENT_ALL, NULL);
	lv_slider_set_value(set_bck_slider, Lcd_Bck_Pwm, LV_ANIM_OFF);
	lv_obj_set_size(set_bck_slider, 160, 20);
	lv_slider_set_range(set_bck_slider, 0, 100);
	
	lv_obj_align_to(set_bck_slider_label, set_bck_slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
	lv_label_set_text_fmt(set_bck_slider_label, "%d%%", Lcd_Bck_Pwm);
	
	lv_obj_align_to(set_bck_slider_name_label, set_bck_slider, LV_ALIGN_OUT_BOTTOM_MID, -10, -45);
	lv_label_set_text(set_bck_slider_name_label, "set bck");
}
