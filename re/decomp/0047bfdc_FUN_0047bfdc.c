// FUN_0047bfdc @ 0047bfdc size=95 sig=undefined FUN_0047bfdc() cc=unknown
// callers: FUN_0047c53c
// callees: FUN_0044cabc,memcpy,FUN_004750c4

void FUN_0047bfdc(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  memcpy(&DAT_005f0410,param_1,0x54f60);
  iVar3 = 0;
  piVar2 = &DAT_005f052a;
  do {
    if (*piVar2 != 0) {
      iVar1 = FUN_004750c4(*piVar2);
      *piVar2 = iVar1;
    }
    if (piVar2[1] != 0) {
      iVar1 = FUN_004750c4(piVar2[1]);
      piVar2[1] = iVar1;
    }
    iVar3 = iVar3 + 1;
    piVar2 = (int *)((int)piVar2 + 0x122);
  } while (iVar3 < 0x4b0);
  FUN_0044cabc();
  return;
}

