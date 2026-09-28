// FUN_0048937d @ 0048937d size=55 sig=undefined FUN_0048937d() cc=unknown
// callers: FUN_00488e62,FUN_0048e530
// callees: FUN_004a6964,FUN_00489320

void FUN_0048937d(undefined4 param_1,int param_2)

{
  undefined1 *puVar1;
  
  FUN_004a6964(param_2,param_1);
  puVar1 = (undefined1 *)FUN_00489320(param_2);
  if (((undefined1 *)(param_2 + 2) <= puVar1) && (*(char *)(param_2 + 1) == ':')) {
    param_2 = param_2 + 2;
  }
  if ((undefined1 *)(param_2 + 1) < puVar1) {
    puVar1 = puVar1 + -1;
  }
  *puVar1 = 0;
  return;
}

