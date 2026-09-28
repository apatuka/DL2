// FUN_004b298c @ 004b298c size=358 sig=undefined FUN_004b298c() cc=unknown
// callers: entry
// callees: GetEnvironmentStrings,FUN_004b185c,FUN_004b2834,FUN_004ae050,FUN_004a9eb4,FUN_004a744c,FUN_004ae578,GetCommandLineA,FUN_004b1910,FUN_004b282c,GetModuleHandleA

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004b298c(int param_1)

{
  char cVar1;
  int *piVar2;
  code *pcVar3;
  HMODULE pHVar4;
  char cVar5;
  int *piVar6;
  char *pcVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int local_10;
  undefined1 local_c [8];
  
  _DAT_0069f880 = *(uint *)(param_1 + 0x10) & 1;
  FUN_004ae050();
  FUN_004ae578(*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(param_1 + 0x20));
  FUN_004a9eb4(*(undefined4 *)(param_1 + 0x28));
  _DAT_0069f874 = 1;
  _DAT_0069f878 = param_1;
  DAT_0069f844 = local_c;
  FUN_004a744c();
  DAT_0069f848 = GetEnvironmentStrings();
  DAT_0069f850 = GetCommandLineA();
  FUN_004b1910();
  piVar2 = (int *)FUN_004b282c();
  if (piVar2 != (int *)0x0) {
    piVar2[*piVar2 + 1] = -1;
    while (pcVar3 = (code *)FUN_004b2834(piVar2,0), pcVar3 != (code *)0x0) {
      (*pcVar3)();
    }
    piVar6 = piVar2;
    for (local_10 = 0; piVar6 = piVar6 + 1, local_10 < *piVar2; local_10 = local_10 + 1) {
      (**(code **)(*piVar6 + 0x18))(0,*(undefined4 *)(*piVar6 + 0x14));
    }
  }
  while (pcVar3 = (code *)FUN_004b2834(&DAT_0069f874,0), pcVar3 != (code *)0x0) {
    (*pcVar3)();
  }
  pcVar7 = DAT_0069f850;
  if ((*(byte *)(param_1 + 0x10) & 1) == 0) {
    uVar8 = (**(code **)(param_1 + 0x18))(DAT_0069f860,DAT_0069f864,DAT_0069f868);
    FUN_004b185c(uVar8);
  }
  else {
    for (; (*pcVar7 == ' ' || (*pcVar7 == '\t')); pcVar7 = pcVar7 + 1) {
    }
    if (*pcVar7 == '\"') {
      cVar5 = '\"';
      pcVar7 = pcVar7 + 1;
    }
    else {
      cVar5 = ' ';
    }
    for (; ((cVar1 = *pcVar7, cVar1 != '\0' && (cVar5 != cVar1)) && (cVar1 != '\t'));
        pcVar7 = pcVar7 + 1) {
    }
    if (*pcVar7 == '\"') {
      pcVar7 = pcVar7 + 1;
    }
    for (; ((cVar5 = *pcVar7, cVar5 != '\0' && (cVar5 == ' ')) || (cVar5 == '\t'));
        pcVar7 = pcVar7 + 1) {
    }
    uVar9 = 10;
    uVar8 = 0;
    pHVar4 = GetModuleHandleA((LPCSTR)0x0);
    uVar8 = (**(code **)(param_1 + 0x18))(pHVar4,uVar8,pcVar7,uVar9);
    FUN_004b185c(uVar8);
  }
  return;
}

