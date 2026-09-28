// FUN_00458bc8 @ 00458bc8 size=162 sig=undefined FUN_00458bc8() cc=unknown
// callers: FUN_00439e98,FUN_00468214
// callees: DirectPlayCreate

undefined4 FUN_00458bc8(void)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int *piVar4;
  int **ppiStack_14;
  int *piStack_10;
  int *local_c;
  undefined4 local_8;
  int local_4;
  
  local_c = (int *)0x0;
  local_8 = 0;
  local_4 = 0;
  piStack_10 = (int *)0x0;
  ppiStack_14 = &local_c;
  iVar1 = DirectPlayCreate(&DAT_0051e750);
  if (iVar1 < 0) {
    uVar2 = 0xffffffff;
  }
  else {
    piStack_10 = &local_4;
    ppiStack_14 = (int **)&DAT_004d1ad0;
    piVar3 = local_c;
    iVar1 = (**(code **)*local_c)();
    if (iVar1 < 0) {
      piVar4 = (int *)&DAT_004d1ac0;
      iVar1 = (**(code **)*piVar3)(piVar3,&DAT_004d1ac0,&ppiStack_14);
      if (iVar1 < 0) {
        (**(code **)(*piVar3 + 8))(piVar3);
        uVar2 = 1;
      }
      else {
        (**(code **)(*piVar4 + 8))();
        (**(code **)(*piVar4 + 8))(piVar4);
        uVar2 = 2;
      }
    }
    else {
      piVar3 = piStack_10;
      (**(code **)(*piStack_10 + 8))();
      (**(code **)(*piVar3 + 8))(piVar3);
      uVar2 = 3;
    }
  }
  return uVar2;
}

