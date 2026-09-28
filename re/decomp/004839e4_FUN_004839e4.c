// FUN_004839e4 @ 004839e4 size=43 sig=undefined FUN_004839e4() cc=unknown
// callers: FUN_0043ca24
// callees: FUN_004838fc,FUN_004839bc

void FUN_004839e4(undefined4 *param_1,undefined4 param_2)

{
  FUN_004839bc(param_2);
  for (; param_1 != (undefined4 *)0x0; param_1 = (undefined4 *)param_1[1]) {
    FUN_004838fc(param_2,*param_1);
  }
  return;
}

