// FUN_0046b3dc @ 0046b3dc size=241 sig=undefined FUN_0046b3dc() cc=unknown
// callers: FUN_0046b818
// callees: SyncDisbandUnit,FUN_00423690,FUN_0044ddf4

void FUN_0046b3dc(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined1 local_44 [4];
  int local_40;
  int local_10;
  int local_c;
  undefined2 *local_8;
  
  local_8 = (undefined2 *)0x0;
  local_c = 10000;
  local_10 = -1;
  iVar4 = 0;
  piVar3 = &DAT_005904dc;
  do {
    iVar1 = *piVar3;
    iVar2 = iVar1 * 0x5c;
    if (((&DAT_00645370 + iVar1 * 0x2e != (undefined2 *)0x0) && ((&DAT_00645376)[iVar2] != '\0')) &&
       ((char)(&DAT_00645378)[iVar2] == param_1)) {
      FUN_0044ddf4(&DAT_0059f160 + param_1 * 0x2d8,(int)(char)(&DAT_00645376)[iVar2],local_44);
      if ((local_10 < local_40) ||
         ((local_40 == local_10 && (*(short *)(&DAT_00645398 + iVar2) < local_c)))) {
        local_10 = local_40;
        local_c = (int)*(short *)(&DAT_00645398 + iVar2);
        local_8 = &DAT_00645370 + iVar1 * 0x2e;
      }
    }
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar4 < 0x230);
  if (local_8 != (undefined2 *)0x0) {
    FUN_00423690((int)*(char *)(local_8 + 4),3,(int)local_8 + 0xb,*(undefined4 *)(local_8 + 0x1e),0,
                 0);
    SyncDisbandUnit(local_8);
  }
  return;
}

