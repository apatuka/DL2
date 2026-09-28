// FUN_0043d990 @ 0043d990 size=110 sig=undefined FUN_0043d990() cc=unknown
// callers: FUN_0043df90
// callees: FUN_00482ac4,FUN_0046ca40,FUN_00448284

uint FUN_0043d990(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  for (iVar5 = *(int *)(param_1 + 0x74); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x44)) {
    iVar1 = FUN_00448284(iVar5);
    if (iVar1 != 0) {
      iVar6 = iVar6 + 1;
    }
  }
  uVar2 = FUN_0046ca40();
  uVar2 = uVar2 % 5;
  uVar3 = FUN_0046ca40();
  uVar4 = uVar3 / 0x32;
  if (uVar3 % 0x32 == 0) {
    uVar2 = uVar2 + 5;
  }
  iVar5 = 0;
  if (0 < iVar6) {
    do {
      uVar4 = FUN_00482ac4(uVar2 + 0x31,0,1,0,0,0);
      iVar5 = iVar5 + 1;
    } while (iVar5 < iVar6);
  }
  return uVar4;
}

