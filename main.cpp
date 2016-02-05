#include "ninjaskit/ninjaskit.h"

using namespace etk;

void hard_fault_handler(void)
{
    while(true)
    {
    	Serial1.print("Hard fault\r\n");
    	sleep_ms(1000);
    }
}

void green_led_task(void)
{
	while(true)
	{
		Serial1.print("red task\r\n");
		etk::sleep_ms(100);
		yield();
	}
}

void blue_led_task(void)
{
	while(true)
	{
		Serial1.print("blue task\r\n");
		etk::sleep_ms(250);
		yield();
	}
}


int main(void)
{
    clock_setup();
    
    Serial1.begin(57600);
    
    configure_as_output({PA, 5});
    configure_as_input({PB, 1});
    
    const struct task_data task_table[2] = {
		create_task<green_led_task, 256, 0>(),
		create_task<blue_led_task, 256, 1>()};
	
    scheduler_init<2>(&task_table[0]);

	yield();
    
    while(1)
    {
    }
}


