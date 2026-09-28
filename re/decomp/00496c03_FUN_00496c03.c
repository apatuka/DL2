// FUN_00496c03 @ 00496c03 size=94 sig=undefined FUN_00496c03() cc=unknown
// callers: FUN_0049659f,FUN_00496c61
// callees: FUN_0048e656,FUN_00496b64
// strings: \"..\\\\src\\\\img.c\"

undefined4
FUN_00496c03(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,int *param_6,int *param_7)

{
  short *psVar1;
  undefined4 uVar2;
  
  if (param_1 == 0) {
    FUN_0048e656(0x2ca,s____src_img_c_0051e14d);
  }
  psVar1 = (short *)FUN_00496b64(param_1,param_2,param_3,param_4,param_5);
  if (psVar1 == (short *)0x0) {
    uVar2 = 0xffffffff;
  }
  else {
    if (param_6 != (int *)0x0) {
      *param_6 = (int)*psVar1;
    }
    if (param_7 != (int *)0x0) {
      *param_7 = (int)psVar1[1];
    }
    uVar2 = *(undefined4 *)(psVar1 + 2);
  }
  return uVar2;
}

