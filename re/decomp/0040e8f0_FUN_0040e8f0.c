// FUN_0040e8f0 @ 0040e8f0 size=162 sig=undefined FUN_0040e8f0() cc=unknown
// callers: FUN_0040e994
// callees: FUN_0040d614,FUN_0040c538

undefined4 * FUN_0040e8f0(int param_1,int param_2)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  int local_10;
  undefined4 *local_c;
  
  sVar1 = *(short *)(param_1 + 10);
  uVar2 = *(undefined4 *)(param_2 + 0x38);
  local_c = (undefined4 *)0x0;
  local_10 = 1000000;
  for (puVar4 = &DAT_005a4eac; puVar4 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar4 = puVar4 + 0x2b7) {
    if ((*(char *)((int)puVar4 + 0x7e) != '\0') && (puVar4[sVar1 + 0x25e] == -1)) {
      iVar3 = FUN_0040c538(param_1,puVar4,1);
      if (iVar3 != 0) {
        iVar3 = FUN_0040d614(uVar2,puVar4,(int)*(short *)(param_1 + 10),
                             (int)(char)(&DAT_004faf8d)[*(char *)(param_2 + 6) * 0x24]);
        if (iVar3 < local_10) {
          local_10 = iVar3;
          local_c = puVar4;
        }
      }
    }
  }
  return local_c;
}

