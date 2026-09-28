// FUN_00403970 @ 00403970 size=158 sig=undefined FUN_00403970() cc=unknown
// callers: FUN_00403a10
// callees: FUN_0044eb4c,FUN_004023dc,FUN_0044ba18

int FUN_00403970(int param_1,undefined4 param_2)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  int local_1c [5];
  int local_8;
  
  local_8 = 0;
  for (puVar4 = &DAT_005f0410; puVar4 < &DAT_00645370; puVar4 = puVar4 + 0x91) {
    sVar1 = puVar4[4];
    if ((((char)(&DAT_005a43f0)[sVar1 * 0xadc] == param_1) && ((*(byte *)(puVar4 + 1) & 4) != 0)) &&
       ((*(byte *)(puVar4 + 1) & 2) != 0)) {
      iVar2 = FUN_004023dc(puVar4,param_2);
      if (iVar2 != -1) {
        uVar3 = FUN_0044ba18(puVar4);
        FUN_0044eb4c(&DAT_0059f160 + param_1 * 0x2d8,&DAT_005a43d0 + sVar1 * 0xadc,
                     (int)*(char *)((int)puVar4 + 7),local_1c,uVar3);
        local_8 = local_8 + local_1c[iVar2];
      }
    }
  }
  return local_8;
}

