// FUN_00446fd4 @ 00446fd4 size=185 sig=undefined FUN_00446fd4() cc=unknown
// callers: FUN_00447090
// callees: FUN_00446b3c

void FUN_00446fd4(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int local_c;
  int local_8;
  
  iVar4 = 5;
  if ((1 << ((byte)param_2 & 0x1f) & (int)DAT_004fbe04) == 0) {
    iVar4 = 4;
  }
  FUN_00446b3c(param_1,iVar4,3,param_2,0x2000 << ((byte)param_2 & 0x1f));
  for (puVar1 = &DAT_005a4eac; puVar1 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar1 = puVar1 + 0x2b7) {
    iVar3 = (int)*(short *)((int)puVar1 + param_2 * 2 + 0xa70);
    if (iVar3 <= iVar4) {
      if (iVar4 == iVar3) {
        local_8 = 0xb;
      }
      else if (iVar4 - iVar3 == 1) {
        local_8 = 10;
      }
      else {
        local_8 = 9;
      }
      local_c = (int)*(char *)((int)puVar1 + param_2 + 0x6d);
      if (local_c < local_8) {
        piVar2 = &local_c;
      }
      else {
        piVar2 = &local_8;
      }
      *(char *)((int)puVar1 + param_2 + 0x6d) = (char)*piVar2;
    }
  }
  return;
}

