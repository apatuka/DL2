// FUN_00444274 @ 00444274 size=102 sig=undefined FUN_00444274() cc=unknown
// callers: FUN_0040350c,FUN_00407290,FUN_00406b1c,FUN_00406a58
// callees: 

undefined4 FUN_00444274(int param_1)

{
  undefined4 uVar1;
  
  if ((param_1 < 0) || (DAT_004d5aec < param_1)) {
    uVar1 = 0;
  }
  else if ((&DAT_0059f161)[param_1 * 0x2d8] == '\0') {
    uVar1 = 0;
  }
  else if (DAT_004d5b00 == '\0') {
    uVar1 = (&DAT_0065e3cc)[param_1];
  }
  else if (DAT_004d5b00 == '\x01') {
    uVar1 = (&DAT_0065e3b0)[param_1];
  }
  else if (DAT_004d5b00 == '\x02') {
    uVar1 = (&DAT_0065e3e8)[param_1];
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

