// FUN_00496a97 @ 00496a97 size=72 sig=undefined FUN_00496a97() cc=unknown
// callers: FUN_00494c15,FUN_00496bae,FUN_00496496,FUN_00496b64,FUN_004940f0,FUN_004a26e8,FUN_00496b2c
// callees: FUN_0048e656,FUN_00496945
// strings: \"..\\\\src\\\\img.c\"

int FUN_00496a97(int param_1,undefined4 param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 == 0) {
    FUN_0048e656(0x231,s____src_img_c_0051e133);
  }
  piVar1 = (int *)FUN_00496945(param_1,param_2);
  if (piVar1 == (int *)0x0) {
    iVar2 = 0;
  }
  else if (param_3 < *piVar1) {
    iVar2 = piVar1[param_3 + 0x10] + (int)piVar1;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

