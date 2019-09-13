#ifndef FSM_TEST_H
#define FSM_TEST_H
#include "../fsmbase.h"
/* states */
enum {
	GET_UP,
	GO_TO_WORK,
	HAVE_LUNCH,
	GO_HOME,
	HAVE_DINNER,
	PLAY_GAME,
	GO_TO_BED
};
/* events */
enum {
	EVENT1 = 1,
	EVENT2,
	EVENT3,
	EVENT4,
	EVENT5,
	EVENT6,
	EVENT7
};
/* event action */
void getUp();
void goToWork();
void haveLunch();
void goHome();
void haveDinner();
void playGame();
void goToBed();
/* event trigger */
void trigger(int *event_id);

#endif// FSM_TEST_H
