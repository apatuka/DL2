// FUN_0041ba74 @ 0041ba74 size=424 sig=undefined FUN_0041ba74() cc=unknown
// callers: FUN_0041c258,FUN_0041e0a8,FUN_0041bc1c
// callees: FUN_0049f22b,FUN_00490ab3,FUN_00498aab,FUN_0041ba04,FUN_0048c85e,FUN_0049a93f,FUN_00496e80,FUN_0048c434,FUN_0049aa64,FUN_00490796,DebugMessage,FUN_0049a8ed
// strings: \"gpBuilding NULL in in_build.c - DrawGuyPool\"

int FUN_0041ba74(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int unaff_ESI;
  undefined1 local_24 [16];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_10 = DAT_0051bddc;
  if (DAT_004b7758 == 0) {
    DebugMessage(s_gpBuilding_NULL_in_in_build_c___D_004b78c6);
    unaff_ESI = 0;
  }
  else {
    FUN_0048c434(*(undefined4 *)(DAT_004b7758 + 0x3c));
    if (0x32 < param_2) {
      param_2 = 0x32;
    }
    iVar3 = 0;
    if (0 < param_2) {
      do {
        unaff_ESI = 0;
        iVar1 = iVar3;
        if (0xb < iVar3) {
          if (iVar3 < 0x19) {
            unaff_ESI = 1;
            iVar1 = iVar3 + -0xc;
          }
          else if (iVar3 < 0x26) {
            unaff_ESI = 2;
            iVar1 = iVar3 + -0x19;
          }
          else {
            unaff_ESI = 3;
            iVar1 = iVar3 + -0x26;
          }
        }
        FUN_0041ba04(&local_8,&local_c,unaff_ESI,iVar1);
        FUN_0049a8ed();
        FUN_0049f22b(DAT_004b7758,local_24);
        FUN_0049aa64(local_24);
        if ((&DAT_004b7760)[unaff_ESI * 0xd + iVar1] == 1) {
          local_14 = 0x3f4;
        }
        else if (iVar3 < param_3) {
          local_14 = 0x3f0;
          (&DAT_004b7760)[unaff_ESI * 0xd + iVar1] = 2;
        }
        else {
          local_14 = 0x3f1;
          (&DAT_004b7760)[unaff_ESI * 0xd + iVar1] = 3;
        }
        iVar1 = FUN_00490ab3(0,0x47414d49,0x31305542,0,0);
        if (iVar1 != 0) {
          uVar2 = FUN_00498aab(iVar1,1);
          FUN_00496e80(uVar2,local_14,param_1,0,local_8,local_c,0xffffffff);
          FUN_00498aab(iVar1,0);
          FUN_00490796(iVar1,0);
        }
        FUN_0049a93f();
        iVar3 = iVar3 + 1;
      } while (iVar3 < param_2);
    }
    if (((DAT_004b7758 != 0) && (*(int *)(DAT_004b7758 + 0x3c) != 0)) &&
       ((*(byte *)(DAT_004b7758 + 0x1c) & 2) != 0)) {
      FUN_0048c85e(*(undefined4 *)(DAT_004b7758 + 0x3c),&DAT_0065e644,local_24,local_24,0,
                   &DAT_0065e580,0);
    }
    FUN_0048c434(local_10);
  }
  return unaff_ESI;
}

