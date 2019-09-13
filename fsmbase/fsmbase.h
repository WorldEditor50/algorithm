#ifndef FSMBASE_H
#define FSMBASE_H
#include "../basetyp.h"
#define FSM_OK      0
#define FSM_ERR     1
typedef struct Event {
	int event_id;
	int current_state;
	int next_state;
	void (*action)();	
} Event;

typedef struct FiniteStateMachine {
	Event *events;
	int    state;
	int    max_event_num;
} Fsm;
/* event regrist */
void fsm_regist(Fsm *fsm, Event *events);
/* state transit */
void fsm_transit(Fsm *fsm, int next_state);
/* event handle */
int fsm_eventHandle(Fsm *fsm, int event_id);
/* event listen */
int fsm_eventListening(Fsm *fsm, int initial_event_id, void (*trigger)(int *event_id));
#endif// FSMBASE_H
