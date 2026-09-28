// FUN_004839a4 @ 004839a4 size=21 sig=undefined FUN_004839a4() cc=unknown
// callers: FUN_00483bd4,FUN_0043c78c,FUN_0043cbf8
// callees: 

undefined4 FUN_004839a4(undefined4 *param_1)

{
  undefined4 uVar1;
  
  if (param_1 == (undefined4 *)0x0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = *param_1;
  }
  return uVar1;
}

