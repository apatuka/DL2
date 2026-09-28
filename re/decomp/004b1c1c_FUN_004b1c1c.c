// FUN_004b1c1c @ 004b1c1c size=45 sig=undefined FUN_004b1c1c() cc=unknown
// callers: FUN_004b1dac
// callees: FUN_004b18ac,FUN_004b1c4c

void FUN_004b1c1c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)FUN_004b18ac(param_2);
  if (puVar1 == (undefined *)0x0) {
    puVar1 = &DAT_00521370;
  }
  FUN_004b1c4c(param_1,puVar1,param_3);
  return;
}

