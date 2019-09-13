#include "test.h"
void init(Fsm *fsm, Event *events, int max_num)
{
	/* FSM regist */
	fsm_regist(fsm, events);	
	/* max */
	fsm->max_event_num = max_num;
}
int main()
{
	Fsm fsm;
	/* init */
	init(&fsm, g_events, 7);
	/* event listen */
	fsm_eventListening(&fsm, EVENT1, trigger);
	return 0;
}
