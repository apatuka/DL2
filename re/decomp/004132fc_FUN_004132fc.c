// FUN_004132fc @ 004132fc size=76 sig=undefined FUN_004132fc() cc=unknown
// callers: FUN_00412cd4
// callees: 

undefined4 FUN_004132fc(int *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*param_1 == 0) {
    uVar1 = 0;
  }
  else if (*(int *)((int)param_1 + 0xe) == 0) {
    if (param_1 + 1 == (int *)0x0) {
      uVar1 = 0xfffffffe;
    }
    else {
      iVar2 = (**(code **)*param_2)(param_2,param_1 + 1);
      *(int *)((int)param_1 + 0xe) = iVar2;
      if (iVar2 == 0) {
        uVar1 = 0xffffffff;
      }
      else {
        uVar1 = 0;
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

