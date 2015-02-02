#ifndef _BUTTON_INPUT_H_
#define _BUTTON_INPUT_H_

#ifdef BUTTON_INPUT
#define EXTERN
#else
#define EXTERN extern
#endif

typedef enum
{
	KEY_MOD,
	KEY_INC,
	KEY_OK,
	KEY_INVALID
}key_e;


EXTERN key_e t_event_e;

#undef EXTERN
void button_get_event_v();

#endif
