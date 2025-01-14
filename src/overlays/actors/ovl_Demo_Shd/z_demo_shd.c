/*
 * File: z_demo_shd.c
 * Overlay: ovl_Demo_Shd
 * Description:
 */

#include "z_demo_shd.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DemoShd*)thisx)

void DemoShd_Init(Actor* thisx, PlayState* play);
void DemoShd_Destroy(Actor* thisx, PlayState* play);
void DemoShd_Update(Actor* thisx, PlayState* play);
void DemoShd_Draw(Actor* thisx, PlayState* play);

const ActorInit Demo_Shd_InitVars = {
    ACTOR_DEMO_SHD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FWALL,
    sizeof(DemoShd),
    (ActorFunc)DemoShd_Init,
    (ActorFunc)DemoShd_Destroy,
    (ActorFunc)DemoShd_Update,
    (ActorFunc)DemoShd_Draw,
};

void DemoShd_Init(Actor* thisx, PlayState* play) {
}
void DemoShd_Destroy(Actor* thisx, PlayState* play) {
}
void DemoShd_Update(Actor* thisx, PlayState* play) {
}
void DemoShd_Draw(Actor* thisx, PlayState* play) {
}
