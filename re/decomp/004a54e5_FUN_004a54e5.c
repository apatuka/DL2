// FUN_004a54e5 @ 004a54e5 size=368 sig=undefined FUN_004a54e5() cc=unknown
// callers: 
// callees: FUN_004a54b0,FUN_004989de,FUN_00498aab,GlobalLock,GlobalUnlock,FUN_0048fe90,FUN_0048f7f1,FUN_004906e3,FUN_00498b98

int FUN_004a54e5(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  int *piVar1;
  LPVOID pvVar2;
  int iVar3;
  short *psVar4;
  int iVar5;
  int iVar6;
  short local_14;
  ushort local_12;
  int *local_10;
  int local_c;
  int local_8;
  
  iVar6 = 0;
  if (param_5 == 2) {
    if (*(int *)(param_4 + 0x1c) != 0) {
      pvVar2 = GlobalLock(*(HGLOBAL *)(param_4 + 0x1c));
      FUN_004a54b0(pvVar2);
      GlobalUnlock(*(HGLOBAL *)(param_4 + 0x1c));
      FUN_004989de(*(undefined4 *)(param_4 + 0x1c));
      FUN_0048fe90(param_4);
    }
    iVar6 = 1;
  }
  else if (param_5 == 3) {
    local_c = *(int *)(param_4 + 0x14);
    iVar3 = FUN_004906e3(param_1,local_c,4,&local_14);
    if (iVar3 == 0) {
      iVar3 = local_14 + 1;
      iVar5 = 0x408;
      if ((local_12 & 1) == 0) {
        iVar5 = 0;
      }
      local_8 = iVar3 * 8 + iVar5 + 0xc;
      iVar5 = FUN_00498b98(local_8);
      if (iVar5 != 0) {
        local_8 = 0x408;
        if ((local_12 & 1) == 0) {
          local_8 = 0;
        }
        local_8 = iVar3 * 4 + local_8;
        psVar4 = (short *)FUN_00498aab(iVar5,1);
        iVar6 = FUN_004906e3(param_1,0xffffffff,local_8,psVar4 + 6);
        if (iVar6 == 0) {
          *psVar4 = local_14;
          psVar4[1] = local_12;
          *(undefined4 *)(psVar4 + 2) = param_1;
          *(int *)(psVar4 + 4) = local_c;
          local_10 = (int *)(psVar4 + iVar3 * 2 + 6);
          piVar1 = (int *)(psVar4 + iVar3 * 4 + 6);
          if ((local_12 & 1) != 0) {
            FUN_0048f7f1(local_10,piVar1,0x408);
          }
          while( true ) {
            local_10 = local_10 + -1;
            if (iVar3 == 0) break;
            piVar1[-2] = *local_10 + local_c;
            piVar1[-1] = 0;
            iVar3 = iVar3 + -1;
            piVar1 = piVar1 + -2;
          }
          FUN_00498aab(iVar5,0);
        }
        else {
          FUN_004989de(iVar5);
        }
        *(int *)(param_4 + 0x1c) = iVar5;
        iVar6 = param_4;
      }
    }
  }
  return iVar6;
}

