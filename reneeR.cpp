/*  
   Layout of Levels
*/

#include <iostream>
using namespace std;
#include <stdio.h>
#include "fonts.h"
#include <stdlib.h>
#include <ctime>
#include "haleyH.h"
#include "flu_fighters.h"
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
extern void spawnGBola();
extern int drawPre(int);
extern int drawPost();
extern void spawnGBola();
extern void spawnSalmonella();
double temp = 0.0;

void wave_one();
void wave_two();
void wave_threee();
void wave_start(Gamestate gameState, Global *gl, State *s);
void wave_clear(Gamestate gameState, Global *gl, State *s);

int waves(Game *g, Gamestate gameState, Global *gl)
{
		if(gameState == WAVE1) 
		{
			w1 = new State;
			struct timespec w1_t;
			clock_gettime(CLOCK_REALTIME, &w1_t);
			double tw = timeDiff(w1->stateTimer, &ws);
			wave_start(gameState, gl, w1);	
			if(gl->thyme >= w1->stateTimer + 4)
			{
				wave_one();	
			}
			if (g->nGbola == 0 && gl->thyme >= w1->stateTimer + 4.5)
			{
				gameState = CUT1;
				c1 = new State;
				struct timespec c1_t;
				clock_gettime(CLOCK_REALTIME, &c1_t);
				double tw = timeDiff(c1->stateTimer, &ws);
			}

		}else if( g->nGbola == 0 && gameState == CUT1){ 
			cout << "wave clear in here\n";
			wave_clear(gameState, gl,&c1);
			if(gl->thyme >= c1->stateTimer + 4)
			{
				gameState = WAVE2;
				w2 = new State;
			}

		}else if (gameState == WAVE2){
			wave_start(gameState, gl, w2);
		 	if (gl->thyme >= w2->stateTimer + 4)
		 	{
				cout << "in wave two" << endl;
				wave_two();
			}
			if (g->nGbola == 0 && gl->thyme >= w2->stateTimer + 4.5)
			{
				gameState = CUT2;
				cout << "leaving wave two" << endl;
				c2 = new State;
			}
		}else if( g->nGbola == 0 && g->nSalmonella == 0 && gameState == CUT3){
			wave_clear(gameState, gl, c2);
			if(gl->thyme >= c2->stateTimer + 4)
			{
				gameState = WAVE3;
				w3 = new State;
			}
		}else{
			gameState = GAMEOVER;
			//wave_start(gameState, gl);
		}
	cout << "gameState as gameState from waves: " << gameState << endl;
	cout << "gameState as int from waves: " << (int)gameState << endl;
	return (int)gameState;
}

void wave_start(Gamestate gameState, Global *gl, State *st)
{
	struct timespec ws;
	clock_gettime(CLOCK_REALTIME, &ws);
	double tw = timeDiff(st->stateTimer, &ws);
	while (tw < 4)
	{
		if (gameState == WAVE1 || gameState == WAVE2 || gameState == WAVE3) 
		{
			if (tw < 0.5 || tw >1.0 && tw  <  1.5 || tw > 2.0 && tw < 2.5) {
				drawPre(gameState);
			}
		}		
	}
}

void wave_clear(Gamestate gameState, Global *gl, State *s)
{
	struct timespec wc;
	clock_gettime(CLOCK_REALTIME, &wc);
	double tw = timeDiff(s->stateTimer, &wc);
	while (tw < 4)
	{	
		if (gameState == CUT1 || gameState == CUT2 || gameState == CUT3) 
		{
			if (tw < 0.5 || tw >1.0 && tw  <  1.5 || tw > 2.0 && tw < 2.5)  {
				cout << "in clear\n";
				drawPost();
			}
		}
	}
}
void wave_one()
{	

	static int enemyCounter = 4;
	while(enemyCounter > 0)
	{
		spawnGBola();	
		enemyCounter--;	
	}	
}

void wave_two()
{
	static int GbolaEnemyCounter = 2;
	static int SalmonellaEnemyCounter = 4;
	while(GbolaEnemyCounter > 0)
	{
		spawnGBola();
		GbolaEnemyCounter--;

	}
	while(SalmonellaEnemyCounter > 0)
	{
		spawnSalmonella();
		SalmonellaEnemyCounter--;

	}
}

void wave_threee()
{
	static int GbolaEnemyCounter = 4;
	static int SalmonellaEnemyCounter = 7;
	while(GbolaEnemyCounter > 0)
	{
		spawnGBola();
		GbolaEnemyCounter--;

	}
	while(SalmonellaEnemyCounter > 0)
	{
		spawnSalmonella();
		SalmonellaEnemyCounter--;

	}	
}

