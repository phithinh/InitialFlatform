#include <general_define.h>
#include <relay_controller.h>
#include <motor.h>

void motor_activate_v()
{
	relay_set(0, 1);

}
void motor_deactivate_v()
{
	relay_set(0, 0);
}
