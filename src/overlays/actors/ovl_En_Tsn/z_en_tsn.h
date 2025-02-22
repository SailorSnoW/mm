#ifndef Z_EN_TSN_H
#define Z_EN_TSN_H

#include "global.h"

struct EnTsn;

typedef void (*EnTsnActionFunc)(struct EnTsn*, PlayState*);

#define ENTSN_GET_F(thisx) ((thisx)->params & 0xF)
#define ENTSN_GET_100(thisx) ((thisx)->params & 0x100)
#define ENTSN_GET_Z(thisx) ((thisx)->home.rot.z)
#define ENTSN_SET_Z(thisx, state) ((thisx)->home.rot.z = state)

#define ENTSN_F_0 0
#define ENTSN_F_1 1

typedef struct EnTsn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnTsnActionFunc actionFunc;
    /* 0x01D8 */ struct EnTsn* unk_1D8;
    /* 0x01DC */ UNK_TYPE1 unk1DC[0x44];
    /* 0x0220 */ u16 unk_220;
    /* 0x0222 */ Vec3s unk_222;
    /* 0x0228 */ Vec3s unk_228;
    /* 0x022E */ s16 unk_22E;
    /* 0x0230 */ s16 unk_230;
} EnTsn; // size = 0x234

extern const ActorInit En_Tsn_InitVars;

#endif // Z_EN_TSN_H
