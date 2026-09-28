// FUN_004a9d10 @ 004a9d10 size=315 sig=undefined FUN_004a9d10() cc=unknown
// callers: FUN_0041287c
// callees: FUN_004ab648,FUN_004a67a8,FUN_004aa618,FUN_004ab710,memcpy

undefined1 * FUN_004a9d10(undefined1 *param_1,int param_2,int *param_3)

{
  int *piVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  undefined1 *puVar5;
  uint unaff_EDI;
  uint local_8;
  
  FUN_004ab648(param_3);
  puVar5 = param_1;
  if (param_3[3] == 0) {
    unaff_EDI = 0;
    while ((unaff_EDI != 10 && (param_2 = param_2 + -1, 0 < param_2))) {
      piVar1 = param_3 + 2;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 < 0) {
        unaff_EDI = FUN_004aa618(param_3);
      }
      else {
        pbVar3 = (byte *)*param_3;
        *param_3 = *param_3 + 1;
        unaff_EDI = (uint)*pbVar3;
      }
      if (unaff_EDI == 0xffffffff) break;
      *puVar5 = (char)unaff_EDI;
      puVar5 = puVar5 + 1;
    }
  }
  else {
    uVar2 = param_2 - 1;
    do {
      while( true ) {
        if ((int)uVar2 < 0) goto LAB_004a9e1f;
        local_8 = param_3[2];
        if ((int)local_8 < 1) break;
        if (uVar2 <= local_8) {
          local_8 = uVar2;
        }
        iVar4 = FUN_004a67a8(*param_3,10,local_8);
        if (iVar4 != 0) {
          local_8 = (iVar4 - *param_3) + 1;
        }
        memcpy(puVar5,*param_3,local_8);
        *param_3 = *param_3 + local_8;
        param_3[2] = param_3[2] - local_8;
        puVar5 = puVar5 + local_8;
        uVar2 = uVar2 - local_8;
        if ((iVar4 != 0) || (uVar2 == 0)) {
          unaff_EDI = 10;
          goto LAB_004a9e1f;
        }
      }
      piVar1 = param_3 + 2;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 < 0) {
        unaff_EDI = FUN_004aa618(param_3);
      }
      else {
        pbVar3 = (byte *)*param_3;
        *param_3 = *param_3 + 1;
        unaff_EDI = (uint)*pbVar3;
      }
      if (unaff_EDI == 0xffffffff) {
        *(ushort *)((int)param_3 + 0x12) = *(ushort *)((int)param_3 + 0x12) | 0x20;
        break;
      }
      *puVar5 = (char)unaff_EDI;
      puVar5 = puVar5 + 1;
      uVar2 = uVar2 - 1;
    } while (unaff_EDI != 10);
  }
LAB_004a9e1f:
  if ((unaff_EDI == 0xffffffff) && (puVar5 == param_1)) {
    param_1 = (undefined1 *)0x0;
  }
  else {
    *puVar5 = 0;
    if ((*(byte *)((int)param_3 + 0x12) & 0x10) != 0) {
      param_1 = (undefined1 *)0x0;
    }
  }
  FUN_004ab710(param_3);
  return param_1;
}

