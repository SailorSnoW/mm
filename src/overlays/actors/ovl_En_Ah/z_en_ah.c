/*
 * File: z_en_ah.c
 * Overlay: ovl_En_Ah
 * Description: Anju's Mother
 */

#include "z_en_ah.h"
#include "objects/object_ah/object_ah.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnAh*)thisx)

void EnAh_Init(Actor* thisx, PlayState* play);
void EnAh_Destroy(Actor* thisx, PlayState* play);
void EnAh_Update(Actor* thisx, PlayState* play);
void EnAh_Draw(Actor* thisx, PlayState* play);

void func_80BD36B8(EnAh* this, PlayState* play);
void func_80BD3768(EnAh* this, PlayState* play);

static u8 D_80BD3DB0[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x21 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x0B - 0x08),
    /* 0x08 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x0B */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(2, 0x20 - 0x0F),
    /* 0x0F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(21, 0, 23, 0, 0x1D - 0x15),
    /* 0x15 */ SCHEDULE_CMD_CHECK_FLAG_S(0x32, 0x20, 0x1C - 0x19),
    /* 0x19 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x1C */ SCHEDULE_CMD_RET_NONE(),
    /* 0x1D */ SCHEDULE_CMD_RET_VAL_L(3),
    /* 0x20 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x21 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_OMOYA, 0x37 - 0x25),
    /* 0x25 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x36 - 0x29),
    /* 0x29 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 6, 0, 0x30 - 0x2F),
    /* 0x2F */ SCHEDULE_CMD_RET_NONE(),
    /* 0x30 */ SCHEDULE_CMD_RET_TIME(18, 0, 6, 0, 2),
    /* 0x36 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x37 */ SCHEDULE_CMD_RET_NONE(),
};

s32 D_80BD3DE8[] = { 0x0E28FF0C, 0x10000000 };

s32 D_80BD3DF0[] = { 0x0E29000C, 0x10000000 };

s32 D_80BD3DF8[] = { 0x00330100, 0x050E28FE, 0x0C100E28, -0x03F3F000 };

s32 D_80BD3E08[] = { 0x0E28FD0C, 0x0F29540C, 0x10000000 };

const ActorInit En_Ah_InitVars = {
    ACTOR_EN_AH,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AH,
    sizeof(EnAh),
    (ActorFunc)EnAh_Init,
    (ActorFunc)EnAh_Destroy,
    (ActorFunc)EnAh_Update,
    (ActorFunc)EnAh_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 10, 68, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfoS sAnimations[] = {
    { &object_ah_Anim_001860, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_ah_Anim_001860, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_ah_Anim_002280, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_ah_Anim_000968, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_ah_Anim_000DDC, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
};

s16 D_80BD3EBC[] = { 0, 0, 1, 0 };

PosRot D_80BD3EC4 = { { 100.0f, 0.0f, 67.0f }, { 0, 0x349C, 0 } };

PosRot D_80BD3ED8 = { { 855.0f, 260.0f, 31.0f }, { 0, 0x7FF8, 0 } };

PosRot D_80BD3EEC = { { -395.0f, 210.0f, -162.0f }, { 0, 0xBE98, 0 } };

Vec3f D_80BD3F00 = { 1000.0f, 0.0f, 0.0f };

TexturePtr D_80BD3F0C[] = { object_ah_Tex_008D70, object_ah_Tex_009570 };

TexturePtr D_80BD3F14[] = {
    object_ah_Tex_006D70, object_ah_Tex_007570, object_ah_Tex_007D70, object_ah_Tex_007570, object_ah_Tex_008570,
};

s32 func_80BD2A30(EnAh* this, PlayState* play, u8 actorCat, s16 actorId) {
    Actor* tempActor;
    Actor* foundActor = NULL;

    while (true) {
        foundActor = SubS_FindActor(play, foundActor, actorCat, actorId);

        if ((foundActor == NULL) || (((EnAh*)foundActor != this) && (foundActor->update != NULL))) {
            break;
        }

        tempActor = foundActor->next;
        if (tempActor == NULL) {
            foundActor = NULL;
            break;
        }
        foundActor = tempActor;
    }

    return foundActor;
}

void func_80BD2AE0(EnAh* this) {
    this->skelAnime.playSpeed = this->unk_2DC;
    SkelAnime_Update(&this->skelAnime);
}

s32 func_80BD2B0C(EnAh* this, s32 arg1) {
    s32 phi_v1 = false;
    s32 ret = false;

    if ((arg1 == 0) || (arg1 == 1)) {
        if ((this->unk_300 != 0) && (this->unk_300 != 1)) {
            phi_v1 = true;
        }
    } else if (arg1 != this->unk_300) {
        phi_v1 = true;
    }

    if (phi_v1) {
        this->unk_300 = arg1;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, arg1);
        this->unk_2DC = this->skelAnime.playSpeed;
    }
    return ret;
}

void func_80BD2BA4(EnAh* this, PlayState* play) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

s32 func_80BD2BE8(EnAh* this, PlayState* play) {
    s32 ret = false;

    if (this->unk_2D8 & 7) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            SubS_UpdateFlags(&this->unk_2D8, 0, 7);
            ret = true;
            this->unk_2D8 |= 8;
            this->actionFunc = func_80BD3768;
        }
    }

    return ret;
}

void func_80BD2C6C(EnAh* this) {
    s32 phi_a3 = false;

    if (this->unk_2D8 & 0x40) {
        if (DECR(this->unk_2F8) == 0) {
            switch (this->unk_2F6) {
                case 1:
                case 2:
                    if ((this->unk_2FA == 4) || (this->unk_2FA == 2)) {
                        phi_a3 = true;
                        this->unk_2FA = 4;
                    }
                    break;
            }

            if (!phi_a3 && (this->unk_2FA == 4)) {
                this->unk_2FA = 0;
            }

            if (!phi_a3) {
                this->unk_2FA++;
                if (this->unk_2FA >= 4) {
                    if (this->unk_2F6 == 0) {
                        this->unk_2F8 = Rand_S16Offset(30, 30);
                    } else {
                        this->unk_2F8 = 8;
                    }
                    this->unk_2FA = 0;
                    phi_a3 = true;
                }
            }
        }
    }

    if (phi_a3 == true) {
        this->unk_2FC = D_80BD3EBC[this->unk_2F6];
    }
}

Actor* func_80BD2DA0(EnAh* this, PlayState* play) {
    Actor* actor;

    if (this->unk_1DC == 3) {
        actor = this->actor.child;
    } else {
        actor = &GET_PLAYER(play)->actor;
    }
    return actor;
}

void func_80BD2DC8(EnAh* this) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    s16 sp32;

    Math_Vec3f_Copy(&sp40, &this->unk_1E4->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);

    sp32 = Math_Vec3f_Yaw(&sp34, &sp40);

    Math_ApproachS(&this->unk_2EE, (sp32 - this->unk_2F2) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_2EE = CLAMP(this->unk_2EE, -0x1FFE, 0x1FFE);

    Math_ApproachS(&this->unk_2F2, (sp32 - this->unk_2EE) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_2F2 = CLAMP(this->unk_2F2, -0x1C70, 0x1C70);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    if (this->unk_1E4->id == ACTOR_PLAYER) {
        sp40.y = ((Player*)this->unk_1E4)->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_1E4->focus.pos);
    }

    Math_ApproachS(&this->unk_2EC, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_2F0, 4, 0x2AA8);
    this->unk_2EC = CLAMP(this->unk_2EC, -0x1554, 0x1554);

    Math_ApproachS(&this->unk_2F0, Math_Vec3f_Pitch(&sp34, &sp40) - this->unk_2EC, 4, 0x2AA8);
    this->unk_2F0 = CLAMP(this->unk_2F0, -0xE38, 0xE38);
}

void func_80BD2FD0(EnAh* this, PlayState* play) {
    this->unk_1E4 = func_80BD2DA0(this, play);

    if ((this->unk_2D8 & 8) && (this->unk_1E4 != NULL)) {
        if (DECR(this->unk_2F4) == 0) {
            func_80BD2DC8(this);
            this->unk_2F0 = 0;
            this->unk_2F2 = 0;
            this->unk_2D8 &= ~0x80;
            this->unk_2D8 |= 0x20;
            return;
        }
    }

    if (this->unk_2D8 & 0x20) {
        this->unk_2D8 &= ~0x20;
        this->unk_2EC = 0;
        this->unk_2EE = 0;
        this->unk_2F0 = 0;
        this->unk_2F2 = 0;
        this->unk_2F4 = 20;
    } else if (DECR(this->unk_2F4) == 0) {
        this->unk_2D8 |= 0x80;
    }
}

s32 func_80BD30C0(EnAh* this, PlayState* play) {
    switch (this->unk_1DC) {
        case 1:
            func_80BD2B0C(this, 0);
            break;

        case 2:
            func_80BD2B0C(this, 4);
            break;
    }
    return false;
}

void func_80BD3118(EnAh* this, PlayState* play) {
    if (this->unk_2FE == 0) {
        func_80BD2B0C(this, 2);
        this->unk_2FE++;
    } else if ((this->unk_2FE == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80BD2B0C(this, 3);
        this->unk_2FE++;
    }
}

s32 func_80BD3198(EnAh* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u16 temp = play->msgCtx.currentTextId;

    if (player->stateFlags1 & 0x40) {
        if (this->unk_2DA != temp) {
            if (temp == 0x2954) {
                this->unk_18C = func_80BD3118;
                this->unk_2FE = 0;
            }

            switch (temp) {
                case 0x28FD:
                    this->unk_2F6 = 1;
                    this->unk_2F8 = 8;
                    break;

                case 0x2954:
                    this->unk_2F6 = 2;
                    this->unk_2F8 = 8;
                    break;
            }
        }
        this->unk_2DA = temp;
        this->unk_2D8 |= 0x100;
    } else if (this->unk_2D8 & 0x100) {
        this->unk_18C = NULL;
        this->unk_2DA = 0;
        this->unk_2D8 &= ~0x100;
        this->unk_2F6 = 0;
        this->unk_2F8 = 4;
        func_80BD30C0(this, play);
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, play);
    }

    return false;
}

s32* func_80BD3294(EnAh* this, PlayState* play) {
    s32 mask = Player_GetMask(play);

    if (PLAYER_MASK_KAFEIS_MASK == mask) {
        return D_80BD3E08;
    }

    switch (this->unk_1DC) {
        case 1:
            if (gSaveContext.save.day == 2) {
                return D_80BD3DF0;
            }
            return D_80BD3DE8;

        case 2:
            return D_80BD3DF8;
    }
    return NULL;
}

s32 func_80BD3320(EnAh* this, PlayState* play, u8 actorCat, s16 actorId) {
    s32 pad;
    s32 ret = false;
    Actor* temp_v0 = func_80BD2A30(this, play, actorCat, actorId);

    if (temp_v0 != NULL) {
        this->actor.child = temp_v0;
        ret = true;
    }
    return ret;
}

s32 func_80BD3374(EnAh* this, PlayState* play, ScheduleResult* arg2) {
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80BD3EC4.pos);
    Math_Vec3s_Copy(&this->actor.world.rot, &D_80BD3EC4.rot);
    Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
    func_80BD2B0C(this, 0);
    SubS_UpdateFlags(&this->unk_2D8, 3, 7);
    this->unk_2D8 |= 0x40;
    return true;
}

s32 func_80BD33FC(EnAh* this, PlayState* play, ScheduleResult* arg2) {
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80BD3ED8.pos);
    Math_Vec3s_Copy(&this->actor.world.rot, &D_80BD3ED8.rot);
    Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
    func_80BD2B0C(this, 4);
    SubS_UpdateFlags(&this->unk_2D8, 3, 7);
    this->unk_2D8 |= (0x40 | 0x10);
    return true;
}

s32 func_80BD3484(EnAh* this, PlayState* play, ScheduleResult* arg2) {
    s32 ret = false;

    if (func_80BD3320(this, play, ACTORCAT_NPC, ACTOR_EN_AN)) {
        if (sREG(81) == 0) {
            Math_Vec3f_Copy(&this->actor.world.pos, &D_80BD3EEC.pos);
            Math_Vec3s_Copy(&this->actor.world.rot, &D_80BD3EEC.rot);
            Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        }
        func_80BD2B0C(this, 4);
        this->unk_2D8 |= (0x40 | 0x8);
        this->unk_2D8 |= 0x10;
        this->unk_2D8 |= 0x80;
        this->actor.gravity = 0.0f;
        ret = true;
    }
    return ret;
}

s32 func_80BD3548(EnAh* this, PlayState* play, ScheduleResult* arg2) {
    s32 ret;

    this->unk_2D8 = 0;

    switch (arg2->result) {
        default:
            ret = false;
            break;

        case 1:
            ret = func_80BD3374(this, play, arg2);
            break;

        case 2:
            ret = func_80BD33FC(this, play, arg2);
            break;

        case 3:
            ret = func_80BD3484(this, play, arg2);
            break;
    }
    return ret;
}

s32 func_80BD35BC(EnAh* this, PlayState* play) {
    s16 temp;
    s16 temp2;

    switch (this->unk_1DC) {
        default:
            return false;

        case 2:
            temp = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y);
            temp2 = ABS_ALT(temp);
            if (temp2 < 0x3800) {
                SubS_UpdateFlags(&this->unk_2D8, 3, 7);
            } else {
                SubS_UpdateFlags(&this->unk_2D8, 0, 7);
            }
            return false;
    }
}

void func_80BD3658(EnAh* this, PlayState* play) {
    if ((this->unk_1DC == 1) || (this->unk_1DC == 2) || (this->unk_1DC == 3)) {
        func_80BD35BC(this, play);
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void func_80BD36B8(EnAh* this, PlayState* play) {
    ScheduleResult sp18;

    if (!Schedule_RunScript(play, D_80BD3DB0, &sp18) ||
        ((this->unk_1DC != sp18.result) && !func_80BD3548(this, play, &sp18))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_1;
        sp18.result = 0;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
    }
    this->unk_1DC = sp18.result;
    func_80BD3658(this, play);
}

void func_80BD3768(EnAh* this, PlayState* play) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;

    if (func_8010BF58(&this->actor, play, func_80BD3294(this, play), NULL, &this->unk_1E0)) {
        SubS_UpdateFlags(&this->unk_2D8, 3, 7);
        this->unk_2D8 &= ~8;
        this->unk_2D8 |= 0x80;
        this->unk_2F4 = 20;
        this->unk_1E0 = 0;
        this->actionFunc = func_80BD36B8;
    } else if (this->unk_1DC != 2) {
        if (this->unk_1E4 != NULL) {
            Math_Vec3f_Copy(&sp40, &this->unk_1E4->world.pos);
            Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
            Math_ApproachS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&sp34, &sp40), 4, 0x2AA8);
        }
    }
}

void EnAh_Init(Actor* thisx, PlayState* play) {
    EnAh* this = THIS;

    if (func_80BD2A30(this, play, ACTORCAT_NPC, ACTOR_EN_AH)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_ah_Skel_009E70, NULL, this->jointTable, this->morphTable, 17);
    this->unk_300 = -1;
    func_80BD2B0C(this, 0);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    this->actor.targetMode = 6;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_1DC = 0;
    this->unk_2D8 = 0;

    this->actionFunc = func_80BD36B8;
    this->actionFunc(this, play);
}

void EnAh_Destroy(Actor* thisx, PlayState* play) {
    EnAh* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnAh_Update(Actor* thisx, PlayState* play) {
    EnAh* this = THIS;
    f32 radius;
    f32 height;

    func_80BD2BE8(this, play);

    this->actionFunc(this, play);

    if (this->unk_1DC != 0) {
        func_80BD3198(this, play);
        func_80BD2AE0(this);
        func_80BD2C6C(this);
        func_80BD2FD0(this, play);
        radius = this->collider.dim.radius + 60;
        height = this->collider.dim.height + 10;

        func_8013C964(&this->actor, play, radius, height, EXCH_ITEM_NONE, this->unk_2D8 & 7);
        if (!(this->unk_2D8 & 0x10)) {
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 4);
        }
        func_80BD2BA4(this, play);
    }
}

void EnAh_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnAh* this = THIS;

    if (limbIndex == 7) {
        Matrix_MultVec3f(&D_80BD3F00, &this->actor.focus.pos);
        Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
    }
}

void EnAh_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnAh* this = THIS;
    s32 stepRot;
    s32 overrideRot;

    if (!(this->unk_2D8 & 0x80)) {
        if (this->unk_2D8 & 0x20) {
            overrideRot = true;
        } else {
            overrideRot = false;
        }
        stepRot = true;
    } else {
        stepRot = false;
        overrideRot = false;
    }

    if (limbIndex == 7) {
        SubS_UpdateLimb(BINANG_ADD(this->unk_2EC + this->unk_2F0, 0x4000),
                        BINANG_ADD(this->unk_2EE + this->unk_2F2 + this->actor.shape.rot.y, 0x4000), this->unk_1E8,
                        this->unk_200, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk_1E8[0].x, this->unk_1E8[0].y, this->unk_1E8[0].z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk_200[0].y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk_200[0].x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_200[0].z, MTXMODE_APPLY);
        Matrix_Push();
    } else if (limbIndex == 2) {
        SubS_UpdateLimb(BINANG_ADD(this->unk_2F0, 0x4000), BINANG_ADD(this->unk_2F2 + this->actor.shape.rot.y, 0x4000),
                        &this->unk_1E8[1], &this->unk_200[1], stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk_1E8[1].x, this->unk_1E8[1].y, this->unk_1E8[1].z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk_200[1].y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk_200[1].x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_200[1].z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

void EnAh_Draw(Actor* thisx, PlayState* play) {
    EnAh* this = THIS;

    if (this->unk_1DC != 0) {
        OPEN_DISPS(play->state.gfxCtx);

        func_8012C28C(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80BD3F14[this->unk_2FA]));
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80BD3F0C[this->unk_2FC]));

        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, NULL, EnAh_PostLimbDraw, EnAh_TransformLimbDraw,
                                       &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
