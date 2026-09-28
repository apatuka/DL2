// FUN_00448d1c @ 00448d1c size=119 sig=undefined FUN_00448d1c() cc=unknown
// callers: FUN_00448d94
// callees: FUN_004487b8,FUN_004489e0

void FUN_00448d1c(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  bool bVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int local_c;
  
  bVar2 = true;
  local_c = DAT_00564404;
  while ((bVar2 && (local_c != 0))) {
    bVar2 = false;
    iVar5 = 0;
    puVar4 = &DAT_004c53f4;
    do {
      uVar1 = *puVar4;
      iVar3 = FUN_004489e0(param_1,uVar1,param_2);
      if ((iVar3 != 0) && (local_c != 0)) {
        bVar2 = true;
        FUN_004487b8(param_1,0x14,uVar1);
        local_c = local_c + -1;
      }
      iVar5 = iVar5 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar5 < 0x17);
  }
  return;
}

