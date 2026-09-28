// FUN_004a7be0 @ 004a7be0 size=63 sig=undefined FUN_004a7be0() cc=unknown
// callers: 
// callees: FUN_004a7466

void FUN_004a7be0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_44;
  
  if (param_2 == (undefined4 *)0x0) {
    local_54 = 0x26;
    local_50 = 2;
    param_2 = &local_54;
    local_44 = 0;
  }
  param_2[1] = param_2[1] | 2;
  FUN_004a7466();
  return;
}

