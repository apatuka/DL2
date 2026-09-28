// FUN_004b28e0 @ 004b28e0 size=118 sig=undefined FUN_004b28e0() cc=unknown
// callers: FUN_004b17e8
// callees: FUN_004b2834,FUN_004b2830

void FUN_004b28e0(void)

{
  code *pcVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  
  while (pcVar1 = (code *)FUN_004b2834(&DAT_0069f874,1), pcVar1 != (code *)0x0) {
    (*pcVar1)();
  }
  while (pcVar1 = (code *)FUN_004b2834(&DAT_0069f83c,1), pcVar1 != (code *)0x0) {
    (*pcVar1)();
  }
  piVar2 = (int *)FUN_004b2830();
  if (piVar2 != (int *)0x0) {
    while (pcVar1 = (code *)FUN_004b2834(piVar2,1), pcVar1 != (code *)0x0) {
      (*pcVar1)();
    }
    piVar3 = piVar2;
    for (iVar4 = 0; piVar3 = piVar3 + 1, iVar4 < *piVar2; iVar4 = iVar4 + 1) {
      (**(code **)(*piVar3 + 0x18))(1,*(undefined4 *)(*piVar3 + 0x14));
    }
  }
  return;
}

