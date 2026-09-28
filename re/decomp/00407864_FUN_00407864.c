// FUN_00407864 @ 00407864 size=625 sig=undefined FUN_00407864() cc=unknown
// callers: FUN_00407ad8
// callees: FUN_00430b1c,FUN_00476760,FUN_004727dc,FUN_00430b94,FUN_00477f9c,FUN_0040526c,FUN_004767f0,FUN_0047691c,FUN_0044d1e4

undefined4 FUN_00407864(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_20;
  undefined4 local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  local_c = 0;
  local_10 = 0;
  local_14 = 100;
  local_18 = -8;
  local_1c = 0;
  piVar1 = &DAT_00521bb4;
  do {
    iVar2 = *(int *)(*piVar1 + 0x3a + param_2 * 4);
    if (local_10 <= iVar2) {
      local_10 = iVar2;
      local_c = *piVar1;
    }
    piVar1 = (int *)piVar1[1];
  } while (piVar1 != &DAT_00521bb4);
  if (local_10 < param_3) {
    piVar1 = &local_10;
  }
  else {
    piVar1 = &param_3;
  }
  local_10 = *piVar1;
  if ((local_c == 0) || (local_10 == 0)) {
    return 0;
  }
  for (puVar5 = &DAT_005a4eac; puVar5 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar5 = puVar5 + 0x2b7) {
    if (((param_1 != *(char *)(puVar5 + 8)) && (*(char *)(puVar5 + 8) != -1)) &&
       (iVar2 = FUN_0044d1e4(puVar5,0x11,0), iVar2 != -1)) {
      iVar2 = *(int *)(&DAT_005220a4 + *(char *)(puVar5 + 8) * 4 + param_1 * 0x1c);
      iVar3 = FUN_004727dc(local_c,puVar5);
      if (((local_18 <= iVar2) && (iVar3 <= local_14)) &&
         ((1 << (*(byte *)(puVar5 + 8) & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0)) {
        local_18 = iVar2;
        local_14 = iVar3;
        local_8 = puVar5;
      }
    }
  }
  if (local_8 == (undefined4 *)0x0) {
    return 0;
  }
  iVar2 = FUN_00430b94(param_2);
  iVar2 = iVar2 - local_14;
  iVar3 = FUN_00430b94(param_2);
  iVar4 = FUN_00430b1c(param_2);
  iVar2 = iVar2 - ((iVar3 - iVar4) *
                  (*(int *)(&DAT_005220a4 +
                           *(char *)(local_8 + 8) * 4 + *(char *)(local_c + 0x20) * 0x1c) + 8)) /
                  0x3a;
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  local_20 = (int)(&DAT_0059f16c)[*(char *)(local_8 + 8) * 0xb6] / ((local_14 + iVar2) * 2);
  if (local_10 < local_20) {
    piVar1 = &local_10;
  }
  else {
    piVar1 = &local_20;
  }
  local_10 = *piVar1;
  if (local_10 < 1) {
    return 0;
  }
  FUN_004767f0(param_1,2);
  FUN_0047691c(local_c,local_8,param_2,local_10,iVar2);
  while (*(int *)(&DAT_006534fc + param_1 * 4) == 2) {
    FUN_00477f9c();
  }
  iVar3 = *(int *)(&DAT_006534fc + param_1 * 4);
  if (iVar3 != 0) {
    if (iVar3 == 1) goto LAB_00407ac1;
    if (iVar3 == 3) {
      FUN_00476760(local_c,local_8,param_2,local_10,iVar2);
      FUN_0040526c(param_1,(int)*(char *)(local_8 + 8),4);
      local_1c = 1;
      goto LAB_00407ac1;
    }
    if (iVar3 != 4) goto LAB_00407ac1;
  }
  FUN_0040526c(param_1,(int)*(char *)(local_8 + 8),0xfffffffc);
LAB_00407ac1:
  FUN_004767f0(param_1,0);
  return local_1c;
}

