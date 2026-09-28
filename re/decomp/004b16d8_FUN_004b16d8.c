// FUN_004b16d8 @ 004b16d8 size=91 sig=undefined FUN_004b16d8() cc=unknown
// callers: FUN_004b1570
// callees: FUN_004ace78,FUN_004acfa4,strlen,FUN_004b1678,FUN_004ac4cc

void FUN_004b16d8(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_004acfa4(param_1,0x4141,0x180);
  if (iVar1 != -1) {
    uVar2 = FUN_004b1678();
    uVar3 = strlen(uVar2);
    FUN_004ac4cc(iVar1,uVar2,uVar3);
    uVar2 = strlen(param_2);
    FUN_004ac4cc(iVar1,param_2,uVar2);
    FUN_004ace78(iVar1);
  }
  return;
}

