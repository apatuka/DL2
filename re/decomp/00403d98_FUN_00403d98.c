// FUN_00403d98 @ 00403d98 size=35 sig=undefined FUN_00403d98() cc=unknown
// callers: FUN_00408a88
// callees: FUN_00403ce8

void FUN_00403d98(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_2;
  do {
    FUN_00403ce8(param_1,*puVar1);
    puVar1 = (undefined4 *)puVar1[1];
  } while (param_2 != puVar1);
  return;
}

