// DrawSprite @ 00444cf4 size=379 sig=undefined DrawSprite() cc=unknown
// callers: FUN_00445190
// callees: wsprintfA,FUN_00445040,DebugMessage,BlitSprite8
// strings: \"Sprite #%d, type#%d, has bad parent %d, type#%d\"|\"Null pointer in DrawSprite: sprite #%d, type#%d\"|\"Null sprite in DrawSprite\"

/* Draws one sprite/anim frame (with parent linkage) */

void DrawSprite(byte *param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  byte *pbVar4;
  short unaff_SI;
  short unaff_DI;
  CHAR local_a4 [80];
  CHAR local_54 [80];
  
  if (((*param_1 & 0x10) == 0) || (*(short *)(param_1 + 0x32) == -1)) {
    unaff_SI = (short)((uint)*(undefined4 *)(param_1 + 6) >> 8) + **(short **)(param_1 + 0x16);
    *(short *)(param_1 + 0xe) = unaff_SI;
    unaff_DI = (short)((uint)*(undefined4 *)(param_1 + 10) >> 8) +
               *(short *)(*(int *)(param_1 + 0x16) + 2);
    *(short *)(param_1 + 0x10) = unaff_DI;
  }
  else {
    iVar3 = *(short *)(param_1 + 0x32) * 0x40;
    if (*(int *)(&DAT_00561a4a + iVar3) == 0) {
      pbVar4 = param_1 + -0x561a34;
      if ((int)pbVar4 < 0) {
        pbVar4 = param_1 + -0x5619f5;
      }
      wsprintfA(local_54,s_Sprite___d__type__d__has_bad_par_004c50c5,(int)pbVar4 >> 6,
                (int)*(short *)(param_1 + 2),(int)*(short *)(param_1 + 0x32),
                (int)*(short *)(&DAT_00561a36 + iVar3));
      DebugMessage(local_54);
    }
    else {
      unaff_SI = (*(short *)(&DAT_00561a42 + iVar3) - **(short **)(&DAT_00561a4a + iVar3)) +
                 **(short **)(param_1 + 0x16);
      *(short *)(param_1 + 0xe) = unaff_SI;
      unaff_DI = (*(short *)(&DAT_00561a44 + iVar3) -
                 *(short *)(*(int *)(&DAT_00561a4a + iVar3) + 2)) +
                 *(short *)(*(int *)(param_1 + 0x16) + 2);
      *(short *)(param_1 + 0x10) = unaff_DI;
      if (*(short *)(&DAT_00561a64 + iVar3) != *(short *)(param_1 + 0x30)) {
        *(short *)(param_1 + 0x30) = *(short *)(&DAT_00561a64 + iVar3);
        FUN_00445040(param_1,CONCAT22((short)((uint)(&DAT_00561a34 + iVar3) >> 0x10),
                                      *(undefined2 *)(param_1 + 0x2c)),1);
      }
    }
  }
  sVar1 = *(short *)(*(int *)(param_1 + 0x16) + 4);
  *(short *)(param_1 + 0x12) = sVar1;
  sVar2 = *(short *)(*(int *)(param_1 + 0x16) + 6);
  *(short *)(param_1 + 0x14) = sVar2;
  if ((param_1 == (byte *)0x0) || (*(int *)(param_1 + 0x16) == 0)) {
    if (param_1 == (byte *)0x0) {
      wsprintfA(local_a4,s_Null_sprite_in_DrawSprite_004c5125);
    }
    else {
      pbVar4 = param_1 + -0x561a34;
      if ((int)pbVar4 < 0) {
        pbVar4 = param_1 + -0x5619f5;
      }
      wsprintfA(local_a4,s_Null_pointer_in_DrawSprite__spri_004c50f5,(int)pbVar4 >> 6,
                (int)*(short *)(param_1 + 2));
    }
    DebugMessage(local_a4);
  }
  else {
    BlitSprite8(*(undefined4 *)(*(int *)(param_1 + 0x16) + 8),(int)unaff_SI,(int)unaff_DI,(int)sVar1
                ,(int)sVar2,(int)sVar1,0);
  }
  return;
}

