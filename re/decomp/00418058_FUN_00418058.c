// FUN_00418058 @ 00418058 size=86 sig=undefined FUN_00418058() cc=unknown
// callers: FUN_004180b0
// callees: 

undefined4 FUN_00418058(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  int in_stack_00000040;
  int in_stack_0000004c;
  
  if (((param_2._3_1_ == '\x04') || (param_2._3_1_ == '\x13')) || (param_2._3_1_ == '\t')) {
    if (((param_2._3_1_ == '\t') && (in_stack_0000004c != 0)) &&
       (*(int *)(in_stack_0000004c + 0x3c) == in_stack_00000040)) {
      return 1;
    }
  }
  else {
    iVar2 = 0;
    piVar1 = &stack0x0000004c;
    do {
      if (*piVar1 != 0) {
        return 1;
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar2 < 3);
  }
  return 0;
}

