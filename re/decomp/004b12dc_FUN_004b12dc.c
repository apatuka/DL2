// FUN_004b12dc @ 004b12dc size=38 sig=undefined FUN_004b12dc() cc=unknown
// callers: FUN_004b1304
// callees: 

void FUN_004b12dc(undefined1 *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  uint uVar2;
  
  for (uVar2 = 0; uVar2 < DAT_0069f780; uVar2 = uVar2 + 1) {
    uVar1 = *param_2;
    *param_2 = *param_1;
    param_2 = param_2 + 1;
    *param_1 = uVar1;
    param_1 = param_1 + 1;
  }
  return;
}

