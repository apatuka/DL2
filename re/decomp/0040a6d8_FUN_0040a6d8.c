// FUN_0040a6d8 @ 0040a6d8 size=54 sig=undefined FUN_0040a6d8() cc=unknown
// callers: 
// callees: 

undefined4 FUN_0040a6d8(byte param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = 1 << (param_1 & 0x1f);
  if (((uVar2 & (int)DAT_004fbefe) == 0) && ((uVar2 & (int)DAT_004fc34a) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

