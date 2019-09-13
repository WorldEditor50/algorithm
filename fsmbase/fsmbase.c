#include "fsmbase.h"

/* event regrist */
void fsm_regist(Fsm *fsm, Event *events)
{
	if (fsm == NULL || events == NULL) {
		return;
	}
	fsm->events = events;
    return;
}

void fsm_transit(Fsm *fsm, int next_state)
{
	if (fsm == NULL) {
		return;
	}
	fsm->state = next_state;
    return;
}

/* event handle */
int fsm_eventHandle(Fsm *fsm, int event_id)
{
	if (fsm == NULL || fsm->events == NULL) {
		return FSM_ERR;
	}
	Event *ev = NULL;
	int i = 0;
    /* find event next state and event handle function */
	for(i = 0; i < fsm->max_event_num; i++) {
		if (fsm->events[i].event_id == event_id) {
			ev = &(fsm->events[i]);
			break;
		}
	}
	/* handle event and transit state */
	if (ev != NULL && ev->action != NULL) {
		ev->action();
		fsm->state = ev->next_state;
	}
    return FSM_OK;
}

/* event listen */
int fsm_eventListening(Fsm *fsm, int initial_event_id, void (*trigger)(int *event_id))
{
	if (fsm == NULL || trigger == NULL) {
		return FSM_ERR;
	}
	int event_id = initial_event_id;
	while (1) {
		fsm_eventHandle(fsm, event_id);
		trigger(&event_id);
		sleep(2);
	}
    return FSM_OK;
}

