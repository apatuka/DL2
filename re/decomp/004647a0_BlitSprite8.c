// BlitSprite8 @ 004647a0 size=541 sig=undefined BlitSprite8() cc=unknown
// callers: FUN_00464b90,FUN_0045a91c,FUN_00458d80,DrawSTileBuilding,FUN_0045a0bc,FUN_0045a3e4,FUN_0044081c,StillPic,FUN_00421fc4,FUN_0047f178,DrawSpriteCentered,FUN_004818ac,FUN_0047f5cc,DrawSprite,FUN_0045a038,FUN_0047fc38,FUN_0042f224,FUN_0045940c,FUN_0045a6e4,CreateWinGWindow,FUN_00482320,FUN_0045a50c,FUN_00465478,FUN_00432824,FUN_00413428,FUN_0047f9a0
// callees: FUN_0048d2e7,FUN_0049b268,FUN_0048d32c,DebugMessage,FUN_00499840,FUN_0049a760
// strings: \"Null Pointer in ClipBlit!\"

/* 8bpp blit with clipping into the back buffer */

undefined4
BlitSprite8(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (param_1 == 0) {
    DebugMessage(s_Null_Pointer_in_ClipBlit__004d2378);
  }
  else {
    if (param_3 < DAT_0058df38) {
      param_1 = param_1 + (DAT_0058df38 - param_3) * param_6;
      param_5 = param_5 - (DAT_0058df38 - param_3);
      param_3 = DAT_0058df38;
    }
    if (param_2 < DAT_0058df34) {
      param_1 = param_1 + (DAT_0058df34 - param_2);
      param_4 = param_4 - (DAT_0058df34 - param_2);
      param_2 = DAT_0058df34;
    }
    if ((((param_2 < DAT_0058df3c) && (param_3 < DAT_0058df40)) && (0 < param_4)) && (0 < param_5))
    {
      if (DAT_0058df3c < param_4 + param_2) {
        param_4 = DAT_0058df3c - param_2;
      }
      if (DAT_0058df40 < param_5 + param_3) {
        param_5 = DAT_0058df40 - param_3;
      }
      if ((-1 < param_4) && (-1 < param_5)) {
        FUN_0048d2e7(*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c));
        FUN_00499840(param_2,param_3);
        uVar1 = FUN_0049a760(*(int *)(DAT_0051bddc + 0xc) << 0x10 | 8);
        if (DAT_0051e35c == 0x100008) {
          uVar2 = 1;
          if (*(short *)(DAT_0051bddc + 0x26) != 2) {
            uVar2 = 2;
          }
          FUN_0049b268(DAT_0058df44,uVar2);
          if (param_7 == 0) {
            if (*DAT_0069ee98 != 0) {
              (*(code *)*DAT_0069ee98)
                        (param_1,param_5,param_4,param_6 - param_4,DAT_0058df44 + 8,DAT_0051c3c4,
                         DAT_0051c3c0);
            }
          }
          else if ((param_7 == 1) && (*DAT_0069ee94 != 0)) {
            (*(code *)*DAT_0069ee94)
                      (param_1,param_5,param_4,param_6 - param_4,DAT_0058df44 + 8,DAT_0051c3c4,
                       DAT_0051c3c0);
          }
        }
        else if (param_7 == 0) {
          if (*DAT_0069ee98 != 0) {
            (*(code *)*DAT_0069ee98)
                      (param_1,param_5,param_4,param_6 - param_4,DAT_0051c3c4,DAT_0051c3c0);
          }
        }
        else if ((param_7 == 1) && (*DAT_0069ee94 != 0)) {
          (*(code *)*DAT_0069ee94)
                    (param_1,param_5,param_4,param_6 - param_4,DAT_0051c3c4,DAT_0051c3c0);
        }
        FUN_0049a760(uVar1);
        FUN_0048d32c();
        return 1;
      }
    }
  }
  return 0;
}

