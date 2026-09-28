// FUN_00404b68 @ 00404b68 size=267 sig=undefined FUN_00404b68() cc=unknown
// callers: FUN_00408a88
// callees: FUN_004412d4,FUN_0046ca40,FUN_0045093c

void FUN_00404b68(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  int local_8;
  
  uVar1 = FUN_0046ca40();
  if (uVar1 % 100 < param_2) {
    for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
        puVar3 = puVar3 + 0x2b7) {
      iVar2 = (int)*(char *)(puVar3 + 8);
      if (((((iVar2 != -1) && (iVar2 != param_1)) && ((char)(&DAT_0059f161)[iVar2 * 0x2d8] < '\x03')
           ) && (('\x02' < *(char *)((int)puVar3 + param_1 + 0x66) &&
                 (iVar2 = FUN_004412d4(param_1,iVar2,4), iVar2 == 0)))) &&
         (uVar1 = FUN_0046ca40(), uVar1 % param_2 == 0)) {
        piVar4 = puVar3 + 0x55;
        local_8 = 0;
        do {
          iVar2 = *piVar4;
          if (((iVar2 != 0) && (*(char *)(iVar2 + 5) != '\v')) &&
             (uVar1 = FUN_0046ca40(), (uVar1 & 7) == 0)) {
            FUN_0045093c(param_1,1 << (*(byte *)(puVar3 + 8) & 0x1f),0xffffffff,8,
                         (int)*(char *)(iVar2 + 4),(int)*(short *)((int)puVar3 + 0x1a),0);
            return;
          }
          local_8 = local_8 + 1;
          piVar4 = piVar4 + 0xd;
        } while (local_8 < 0x24);
      }
    }
  }
  return;
}

