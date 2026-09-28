// FUN_00490ab3 @ 00490ab3 size=279 sig=undefined FUN_00490ab3() cc=unknown
// callers: FUN_00484600,FUN_0041beac,FUN_004a3de6,DrawCAGuyPool,FUN_004a1607,FUN_00496e80,FUN_00415274,FUN_0043e198,FUN_0043b50c,FUN_00459230,FUN_0049659f,FUN_004a17b0,FUN_0043b2c4,FUN_00496199,FUN_004961e8,FUN_0041ba74,FUN_00418704,FUN_0049117e,FUN_0049d7f4,FUN_004a3cc8,FUN_0047e074,FUN_004a578e,FUN_0049112c,FUN_00496cc3,FUN_00487e34,FUN_00496c61,FUN_004a57e0,FUN_00480150,FUN_004a1835,FUN_004a1715,FUN_0049585a,FUN_00496ffb
// callees: FUN_004905e5,FUN_004901c6,FUN_00498aab

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00490ab3(int param_1,undefined4 param_2,int *param_3,int param_4,uint param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  int *piVar6;
  
  if (DAT_0051daf8 == (short *)0x0) {
    uVar1 = 0;
  }
  else {
    if ((param_4 == 2) && (*param_3 == -1)) {
      param_3 = param_3 + 1;
      param_4 = 1;
    }
    if (param_1 == 0) {
      iVar4 = 0;
      psVar5 = DAT_0051daf8 + 2;
      for (iVar3 = (int)*DAT_0051daf8; 0 < iVar3; iVar3 = iVar3 + -1) {
        param_1 = *(int *)(psVar5 + 1);
        uVar1 = param_2;
        piVar6 = param_3;
        iVar4 = param_4;
        uVar2 = FUN_00498aab(param_1,1);
        iVar4 = FUN_004905e5(uVar2,uVar1,piVar6,iVar4);
        if (iVar4 != 0) break;
        FUN_00498aab(param_1,0);
        psVar5 = psVar5 + 0x85;
      }
      if (iVar4 == 0) {
        return 0;
      }
    }
    else {
      uVar1 = param_2;
      piVar6 = param_3;
      uVar2 = FUN_00498aab(param_1,1);
      iVar4 = FUN_004905e5(uVar2,uVar1,piVar6,param_4);
      if (iVar4 == 0) {
        FUN_00498aab(param_1,0);
        return 0;
      }
    }
    if (*(int *)(iVar4 + 0x1c) == 0) {
      uVar1 = 5;
      if ((param_5 & 0x40000000) == 0) {
        uVar1 = 3;
      }
      FUN_004901c6(param_1,param_2,param_3,iVar4,uVar1,param_5 & 0xff,0);
    }
    if ((*(int *)(iVar4 + 0x1c) != 0) && ((param_5 & 0x80000000) != 0)) {
      *(int *)(iVar4 + 0x20) = *(int *)(iVar4 + 0x20) + 1;
    }
    DAT_0065eba0 = iVar4;
    _DAT_0065eba4 = param_1;
    FUN_00498aab(param_1,0);
    uVar1 = *(undefined4 *)(iVar4 + 0x1c);
  }
  return uVar1;
}

