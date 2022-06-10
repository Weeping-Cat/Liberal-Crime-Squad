




/*
	File created by Chris Johnson.
	These were previously all in game.cpp.

	This file includes all the the enums, defines, and included headers required globally by all components.

	All code released under GNU GPL.
*/
#include <windows.h>
#include <vector>
#include <map>
#include <deque>
#include "cmarkup/Markup.h"
using namespace std;

#include "includesLen.h"
#include <iostream>
#include "includesDeprecated.h"



enum Laws
{
	LAW_STALIN = -2, // not a real law: this is -2 and is actually calculated based on views >=0 and <VIEWNUM-3
	LAW_MOOD, // not a real law: this is -1 and is likewise calculated based on views >=0 and <VIEWNUM-3
	LAW_ABORTION, // law #0, the first one that is actually in the law[] array
	LAW_ANIMALRESEARCH,
	LAW_POLICEBEHAVIOR,
	LAW_PRIVACY,
	LAW_DEATHPENALTY,
	LAW_NUCLEARPOWER,
	LAW_POLLUTION,
	LAW_LABOR,
	LAW_GAY,
	LAW_CORPORATE,
	LAW_FREESPEECH,
	LAW_FLAGBURNING,
	LAW_GUNCONTROL,
	LAW_TAX,
	LAW_WOMEN,
	LAW_CIVILRIGHTS,
	LAW_DRUGS,
	LAW_IMMIGRATION,
	LAW_ELECTIONS,
	LAW_MILITARY,
	LAW_PRISONS,
	LAW_TORTURE,
	LAWNUM
};

#include "includesRandom.h"
/* This is declared again lower down, just needed here for this header. */
std::string tostring(long i);

//just a float that is initialized to 0
#include "floatZero.h"
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.
#include "activityST.h"

//int get_associated_attribute(int skill_type);

#include "includesSDS.h"
#include "includesSDS2.h"
//#ifdef	DATE_CPP
// date.cpp

#include "../creature/creature.h"
////

#include "../creature/deprecatedCreatureA.h"
////
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
/* character info at top of screen */
void printcreatureinfo(DeprecatedCreature* cr, unsigned char knowledge = 255);
// for  addstr
/* common - tests if the person is a wanted criminal */
bool iscriminal(CreatureJustice cr);
/* Determines the number of loveslaves a creature may recruit,
based on their maxand the number they already command */
int loveslavesleft(const DeprecatedCreature & cr);
// Prompt to convert a new recruit into a sleeper
void sleeperize_prompt(DeprecatedCreature& converted, DeprecatedCreature& recruiter, int y);
// Determines the number of love slaves a creature has
int loveslaves(const DeprecatedCreature& cr);
/* common - applies a crime to a person */
void criminalize(DeprecatedCreature& cr, short crime);
// for int loveslavesleft(const Creature&)
void addjuice(DeprecatedCreature& cr, long juice, long cap);

#include "../common/getnames.h"
// for void enter_name(int,int,char *,int,const char *=NULL)
int getarmortype(const string &idname);
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../common/creaturePoolCreature.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"

extern class Ledger ledger;
extern int stat_kidnappings;
extern int stat_recruits;
extern Log gamelog;
extern MusicClass music;
extern short lawList[LAWNUM];
extern vector<DeprecatedCreature *> pool;

enum DateResults
{
	DATERESULT_MEETTOMORROW,
	DATERESULT_BREAKUP,
	DATERESULT_JOINED,
	DATERESULT_ARRESTED
};
//So dates can see masks.
void printWeirdMask(const string tkname, const int tkalign, const int line);
int getpoolcreature(int id);
char completedate(Deprecateddatest &d, int p);
void removesquadinfo(DeprecatedCreature &cr);
char completevacation(Deprecateddatest &d, int p);
//#endif//DATE_CPP
//#endif// INCLUDES_H_INCLUDED
