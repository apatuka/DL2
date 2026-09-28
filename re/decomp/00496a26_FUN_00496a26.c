// FUN_00496a26 @ 00496a26 size=54 sig=undefined FUN_00496a26() cc=unknown
// callers: FUN_00496496
// callees: FUN_0048e656
// strings: \"..\\\\src\\\\img.c\"

undefined4 FUN_00496a26(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    FUN_0048e656(0x206,s____src_img_c_0051e119);
  }
  if ((param_2 < *(int *)(param_1 + 0x14)) && (-1 < param_2)) {
    uVar1 = *(undefined4 *)(param_1 + 0x18 + param_2 * 8);
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

