#define BUTTON_INPUT
#include <general_define.h>
#include <button_input_pub.h>
#include <button_scan_pub.h>

#include <relay_controller.h>

void button_get_event_v()
{

	//button state reading
	if (button_scan_readButtonSta_ub(0)){
		t_event_e = KEY_MOD;

	}
	else if (button_scan_readButtonSta_ub(1)){
		t_event_e = KEY_INC;

	}
	else if (button_scan_readButtonSta_ub(2)){
		t_event_e = KEY_OK;
	}
	else
	{
		t_event_e = KEY_INVALID;

	}
//	relay_set(0, t_event_e == KEY_MOD);
//	relay_set(1, t_event_e == KEY_INC);
//	relay_set(2, t_event_e == KEY_OK);
}
