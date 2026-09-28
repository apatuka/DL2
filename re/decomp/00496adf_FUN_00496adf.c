// FUN_00496adf @ 00496adf size=77 sig=undefined FUN_00496adf() cc=unknown
// callers: 
// callees: FUN_0048e656,FUN_0049698a
// strings: \"..\\\\src\\\\img.c\"

int FUN_00496adf(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 == 0) {
    FUN_0048e656(0x24f,s____src_img_c_0051e140);
  }
  piVar1 = (int *)FUN_0049698a(param_1,param_2,param_3,0);
  if (piVar1 == (int *)0x0) {
    iVar2 = 0;
  }
  else if (param_4 < *piVar1) {
    iVar2 = piVar1[param_4 + 0x10] + (int)piVar1;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

