// I learned how to do this from: https://twhl.info/wiki/page/Tutorial:_Coding_NPCs_in_GoldSrc#h6007fc334e468
// Most of the comments are from them ^^

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "schedule.h"

//=========================
//--Monster's Anim Events--
//=========================
#define PDRONE_FIRE_SPIKE  ( 1 )
#define PDRONE_MELEE_LEFT  ( 3 )
#define PDRONE_MELEE_RIGHT ( 8 )
#define PDRONE_MELEE_BOTH  ( 6 )

//=========================
//--Monster's Extra Defs---
//=========================

//-Body Groups
#define BODYGROUP_BODY              1
#define BODYGROUP_SPIKES            2

//-Spike Groups
#define BODY_NO_SPIKES              0
#define BODY_SIX_SPIKES             1
#define BODY_FIVE_SPIKES            2
#define BODY_FOUR_SPIKES            3
#define BODY_THREE_SPIKES           4
#define BODY_TWO_SPIKES             5
#define BODY_ONE_SPIKES             6

class CRapeMonster : public CBaseMonster
{
public:
    void Spawn(void);
    void Precache(void);
    int iSpikes;
    int Classify(void);
    void SetYawSpeed(void);
};

LINK_ENTITY_TO_CLASS(monster_rapemonster, CRapeMonster);

void CRapeMonster::Spawn()
{
    Precache(); // So the model loads

    SET_MODEL(ENT(pev), "models/friendly.mdl"); // So you can see him

    UTIL_SetSize(pev, VEC_HUMAN_HULL_MIN, VEC_HUMAN_HULL_MAX); // Let's make his size human. If you're smart enough (or have lots of patience) you can get replace the VEC_ stuff with "Vector( x, y, z)".

    pev->solid = SOLID_SLIDEBOX; // They see me slidin', they hating. This actually tells the engine for it to be Solid. Snakes can GTHO.
    pev->movetype = MOVETYPE_STEP; // 'cause monsters walk - they don't drive (Nightmares will follow)
    m_bloodColor = BLOOD_COLOR_GREEN; // Green blood - just like this comment. Freaked out much? (The blood's actually yellow, though)
    pev->health = 100; // Health - let's keep it as an integer, as opposed to a changeable variable for now.
    pev->view_ofs = Vector(0, 0, 20); // Eyes' offset (He sees you doing stuff you shouldn't)
    m_flFieldOfView = 0.5; // How far he can see.
    m_MonsterState = MONSTERSTATE_NONE; // Afet he spawns, make him sit there like an idiot, doing nothing.

    MonsterInit(); // Starts the monsters AI

    iSpikes = 6; // Default, he's fully loaded with spikes. AGAIN, NO PUNS YOU SICKOS!
}

void CRapeMonster::Precache()
{
    PRECACHE_MODEL("models/friendly.mdl");
}

int CRapeMonster::Classify(void)
{
    return CLASS_ALIEN_MONSTER;
}

void CRapeMonster::SetYawSpeed(void) {
    pev->yaw_speed = 90;
}