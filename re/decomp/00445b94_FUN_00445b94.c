// FUN_00445b94 @ 00445b94 size=321 sig=undefined FUN_00445b94() cc=unknown
// callers: FUN_00446440,FUN_004467e8,FUN_00446084,FUN_00445d30,FUN_0040d5c0,FUN_00445ae4,FUN_0044da3c,SetRetreat
// callees: FUN_0044d1e4,FUN_00445940,FUN_0045951c,FUN_004594b8

uint FUN_00445b94(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 local_bc;
  undefined1 local_b5;
  undefined4 local_60;
  undefined1 local_59;
  
  iVar1 = *(int *)(param_1 + 0x76);
  if ((((DAT_004d5aa0 == '\0') && ((&DAT_004faf87)[param_2 * 0x24] == '\t')) && (param_2 != 0x24))
     && (iVar2 = FUN_0044d1e4(param_1,10,0), iVar2 == -1)) {
    uVar3 = 0;
  }
  else if ((*(char *)(param_1 + 0x21) == '\0') && ((&DAT_004faf8d)[param_2 * 0x24] == '\x01')) {
    uVar3 = FUN_00445940(iVar1);
  }
  else if ((*(char *)(param_1 + 0x21) == '\0') || ((&DAT_004faf8d)[param_2 * 0x24] != '\x02')) {
    if (*(char *)(param_1 + 0x21) == '\0') {
      puVar6 = &DAT_004c51d4;
      puVar7 = &local_60;
      for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      iVar2 = 0;
      local_59 = (&DAT_004faf87)[param_2 * 0x24];
      iVar4 = FUN_004594b8(&local_60);
      for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x54)) {
        iVar5 = FUN_004594b8(iVar1);
        if (iVar4 == iVar5) {
          iVar2 = iVar2 + 1;
        }
      }
      uVar3 = (uint)(iVar2 < (int)(&DAT_004faf6c)[iVar4]);
    }
    else {
      puVar6 = &DAT_004c5230;
      puVar7 = &local_bc;
      for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      iVar2 = 0;
      local_b5 = (&DAT_004faf87)[param_2 * 0x24];
      iVar4 = FUN_0045951c(&local_bc);
      for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x54)) {
        iVar5 = FUN_0045951c(iVar1);
        if (iVar4 == iVar5) {
          iVar2 = iVar2 + 1;
        }
      }
      uVar3 = (uint)(iVar2 < (int)(&DAT_004faf5c)[iVar4]);
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

