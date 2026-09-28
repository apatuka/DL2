// FUN_0040e9f4 @ 0040e9f4 size=230 sig=undefined FUN_0040e9f4() cc=unknown
// callers: FUN_0040eadc
// callees: FUN_0040c538,FUN_004412d4

undefined * FUN_0040e9f4(int param_1)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  ushort *local_14;
  int local_10;
  undefined *local_c;
  int local_8;
  
  iVar4 = *(int *)(param_1 + 0x10);
  local_8 = -1000000;
  local_c = (undefined *)0x0;
  if ((iVar4 != 0) && ((int)*(char *)(iVar4 + 0x20) == (int)*(short *)(param_1 + 8))) {
    local_14 = (ushort *)(iVar4 + 0x890);
    local_10 = 0;
    do {
      uVar2 = *local_14;
      for (iVar4 = 0; (uVar2 != 0 && (iVar4 < 0x10)); iVar4 = iVar4 + 1) {
        if ((uVar2 & 1) != 0) {
          iVar3 = (local_10 * 0x10 + iVar4) * 0xadc;
          iVar1 = (int)(char)(&DAT_005a43f0)[iVar3];
          if ((iVar1 != -1) && (iVar1 != *(short *)(param_1 + 10))) {
            iVar1 = FUN_004412d4((int)*(short *)(param_1 + 10),iVar1,2);
            if (iVar1 == 0) goto LAB_0040eaad;
          }
          iVar1 = FUN_0040c538(param_1,&DAT_005a43d0 + iVar3,1);
          if ((iVar1 != 0) &&
             (local_8 < *(int *)(&DAT_005a4dda + iVar3) - *(int *)(&DAT_005a4e30 + iVar3))) {
            local_c = &DAT_005a43d0 + iVar3;
            local_8 = *(int *)(&DAT_005a4dda + iVar3) - *(int *)(&DAT_005a4e30 + iVar3);
          }
        }
LAB_0040eaad:
        uVar2 = (short)uVar2 >> 1;
      }
      local_10 = local_10 + 1;
      local_14 = local_14 + 1;
    } while (local_10 < 7);
  }
  return local_c;
}

