// FUN_00428824 @ 00428824 size=58 sig=undefined FUN_00428824() cc=unknown
// callers: FUN_0045c704,FUN_0045ca3c
// callees: FUN_00428620,FUN_00428468,CheckMoveStuff,FUN_00428408

undefined4 FUN_00428824(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00428468(param_1,param_2,param_3);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    FUN_00428408();
    do {
      iVar1 = CheckMoveStuff();
    } while (iVar1 == 0);
    FUN_00428620();
    uVar2 = DAT_00557ba0;
  }
  return uVar2;
}

