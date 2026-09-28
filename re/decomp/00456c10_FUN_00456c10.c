// FUN_00456c10 @ 00456c10 size=47 sig=undefined FUN_00456c10() cc=unknown
// callers: FUN_00457624
// callees: FUN_004568c8

void FUN_00456c10(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00657de0;
  DAT_00657de0 = param_1;
  FUN_004568c8(param_1);
  DAT_00657de0 = uVar1;
  return;
}

