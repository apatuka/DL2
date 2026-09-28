// FUN_004064a0 @ 004064a0 size=31 sig=undefined FUN_004064a0() cc=unknown
// callers: FUN_00408a88
// callees: FUN_00475d60

void FUN_004064a0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_2;
  do {
    FUN_00475d60(*puVar1);
    puVar1 = (undefined4 *)puVar1[1];
  } while (param_2 != puVar1);
  return;
}

