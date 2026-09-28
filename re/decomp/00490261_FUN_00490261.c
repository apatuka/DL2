// FUN_00490261 @ 00490261 size=45 sig=undefined FUN_00490261() cc=unknown
// callers: FUN_0049028e
// callees: 

undefined4 FUN_00490261(int *param_1)

{
  undefined4 uVar1;
  
  if (((*param_1 == 0x424c5943) && (param_1[1] == 0x20204350)) && (0xffff < param_1[2])) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

