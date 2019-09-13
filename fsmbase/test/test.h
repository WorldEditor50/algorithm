#ifndef _TEST_H
#define _TEST_H
#include "fsm_test.h"
/* FSM table */ 
Event g_events[] = {
	{ EVENT1, GET_UP, GO_TO_WORK, goToWork },
	{ EVENT2, GO_TO_WORK, HAVE_LUNCH, haveLunch },
	{ EVENT3, HAVE_LUNCH, GO_HOME, goHome },
	{ EVENT4, GO_HOME, HAVE_DINNER, haveDinner },
	{ EVENT5, HAVE_DINNER, PLAY_GAME, playGame },
	{ EVENT6, PLAY_GAME, GO_TO_BED, goToBed },
	{ EVENT7, GO_TO_BED, GET_UP, getUp }
};
#endif //_TEST_H
