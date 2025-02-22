/*
 * File: z_en_bh.c
 * Overlay: ovl_En_Bh
 * Description: Brown Bird (on the Moon)
 */

#include "z_en_bh.h"

#define FLAGS 0x00000000

#define THIS ((EnBh*)thisx)

void EnBh_Init(Actor* thisx, PlayState* play);
void EnBh_Destroy(Actor* thisx, PlayState* play);
void EnBh_Update(Actor* thisx, PlayState* play);
void EnBh_Draw(Actor* thisx, PlayState* play);

#if 0
const ActorInit En_Bh_InitVars = {
    ACTOR_EN_BH,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BH,
    sizeof(EnBh),
    (ActorFunc)EnBh_Init,
    (ActorFunc)EnBh_Destroy,
    (ActorFunc)EnBh_Update,
    (ActorFunc)EnBh_Draw,
};

#endif

extern UNK_TYPE D_06000074;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bh/EnBh_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bh/EnBh_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bh/func_80C22DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bh/EnBh_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bh/EnBh_Draw.s")
