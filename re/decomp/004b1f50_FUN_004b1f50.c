// FUN_004b1f50 @ 004b1f50 size=98 sig=undefined FUN_004b1f50() cc=unknown
// callers: FUN_004b1fb4
// callees: strlen,FUN_004a6bf8,FUN_004b0b44

undefined1 * FUN_004b1f50(int *param_1)

{
  int iVar1;
  undefined1 *puVar2;
  int *piVar3;
  int iVar4;
  undefined1 *puVar5;
  
  iVar4 = 1;
  for (piVar3 = param_1; *piVar3 != 0; piVar3 = piVar3 + 1) {
    iVar1 = strlen(*piVar3);
    iVar4 = iVar1 + iVar4 + 1;
  }
  puVar2 = (undefined1 *)FUN_004b0b44(iVar4);
  puVar5 = puVar2;
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = (undefined1 *)0x0;
  }
  else {
    for (; *param_1 != 0; param_1 = param_1 + 1) {
      iVar4 = FUN_004a6bf8(puVar5,*param_1);
      puVar5 = (undefined1 *)(iVar4 + 1);
    }
    *puVar5 = 0;
  }
  return puVar2;
}

