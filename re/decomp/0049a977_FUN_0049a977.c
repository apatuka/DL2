// FUN_0049a977 @ 0049a977 size=112 sig=undefined FUN_0049a977() cc=unknown
// callers: FUN_0049aa64
// callees: 

undefined4 FUN_0049a977(int *param_1)

{
  undefined4 uVar1;
  
  if (param_1[1] < DAT_0065e570) {
    param_1[1] = DAT_0065e570;
  }
  if (DAT_0065e578 < param_1[3]) {
    param_1[3] = DAT_0065e578;
  }
  if (*param_1 < DAT_0065e574) {
    *param_1 = DAT_0065e574;
  }
  if (DAT_0065e57c < param_1[2]) {
    param_1[2] = DAT_0065e57c;
  }
  if ((*param_1 < param_1[2]) && (param_1[1] < param_1[3])) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

