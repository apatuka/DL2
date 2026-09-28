// FUN_00458d80 @ 00458d80 size=344 sig=undefined FUN_00458d80() cc=unknown
// callers: FUN_00458f14,FUN_00458ed8
// callees: FUN_0049a8ed,FUN_0048d2e7,FUN_0048d32c,FUN_0049aa95,FUN_00463da8,FUN_00463d00,FUN_00496c61,FUN_0049a93f,BlitSprite8,FUN_00498aab,FUN_0049a760,InvalidateRect,FUN_0049a9e7

void FUN_00458d80(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int *piVar2;
  uint uVar3;
  uint local_8;
  
  if (((DAT_00583d38 == 0) || (DAT_00583d44 == 0)) || (DAT_00583d48 == 0)) {
    if (((DAT_00583d58 != 0) && (DAT_00583d44 != 0)) && (DAT_00583d48 != 0)) {
      uVar1 = FUN_00498aab(DAT_00583d58,1);
      piVar2 = (int *)FUN_00496c61(uVar1,DAT_00583d5c,DAT_00583d60,0,0,0,0,&local_8);
      if ((piVar2 != (int *)0x0) && ((local_8 & 0x40000000) == 0)) {
        FUN_0048d2e7(DAT_004d5c28);
        uVar3 = 8;
        if ((*(byte *)(*piVar2 + 8) & 3) != 0) {
          uVar3 = 0x10;
        }
        uVar1 = FUN_0049a760(*(int *)(DAT_0051bddc + 0xc) << 0x10 | uVar3);
        FUN_0049a8ed();
        FUN_0049a9e7(DAT_0051bddc + 0x2c);
        FUN_0049aa95(*piVar2,param_1,param_2,(int)*(short *)(*piVar2 + 0xe),0);
        FUN_0049a93f();
        FUN_0049a760(uVar1);
        FUN_0048d32c();
      }
      FUN_00498aab(DAT_00583d58,0);
    }
  }
  else {
    FUN_00463da8(1);
    FUN_00463d00(0,0,DAT_0058f1c0,DAT_0058f1c4);
    BlitSprite8(DAT_00583d38,param_1,param_2,DAT_00583d44,DAT_00583d48,DAT_00583d44,0);
    InvalidateRect(DAT_00583d50,(RECT *)0x0,0);
  }
  return;
}

