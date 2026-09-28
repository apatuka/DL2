// FUN_004021e0 @ 004021e0 size=313 sig=undefined FUN_004021e0() cc=unknown
// callers: FUN_00403a10
// callees: FUN_0044ba40,FUN_0044eeb4,FUN_004023dc,FUN_0044ba18

int FUN_004021e0(int param_1,undefined4 param_2,char *param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int local_18;
  int local_10;
  
  piVar3 = param_4;
  local_10 = 0;
  local_18 = 0;
  do {
    iVar1 = *param_4;
    iVar6 = 0;
    piVar7 = (int *)(iVar1 + 0x154);
    do {
      iVar2 = *piVar7;
      if ((iVar2 != 0) &&
         (((param_3 == (char *)0x0 || (*param_3 == *(char *)(iVar2 + 0xe))) &&
          ((*(byte *)(iVar2 + 2) & 4) != 0)))) {
        iVar4 = FUN_0044ba18(iVar2);
        iVar5 = FUN_0044ba40(iVar2);
        if ((iVar4 < iVar5) && (*(short *)(iVar2 + 0x12) == 0)) {
          iVar4 = FUN_004023dc(iVar2,param_2);
          if (iVar4 != -1) {
            iVar5 = FUN_0044eeb4(&DAT_0059f160 + param_1 * 0x2d8,iVar1,iVar6,iVar4,
                                 *(int *)(iVar2 + 0x18 + iVar4 * 4) + 1);
            iVar4 = FUN_0044eeb4(&DAT_0059f160 + param_1 * 0x2d8,iVar1,iVar6,iVar4,
                                 *(undefined4 *)(iVar2 + 0x18 + iVar4 * 4));
            if ((local_18 < iVar5 - iVar4) || (local_18 == 0)) {
              local_18 = iVar5 - iVar4;
              local_10 = iVar2;
            }
          }
        }
      }
      iVar6 = iVar6 + 1;
      piVar7 = piVar7 + 0xd;
    } while (iVar6 < 0x24);
    param_4 = (int *)param_4[1];
  } while (param_4 != piVar3);
  return local_10;
}

