// FUN_00407be8 @ 00407be8 size=66 sig=undefined FUN_00407be8() cc=unknown
// callers: FUN_00408a88
// callees: FUN_0040774c,FUN_00407794,FUN_004076ac,FUN_00407714,FUN_00407ad8

void FUN_00407be8(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = 1;
  do {
    FUN_004076ac(param_1);
    uVar1 = FUN_0040774c(iVar2,100);
    FUN_00407794(param_1,iVar2,uVar1);
    uVar1 = FUN_00407714(iVar2,500);
    FUN_00407ad8(param_1,iVar2,uVar1);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xb);
  return;
}

