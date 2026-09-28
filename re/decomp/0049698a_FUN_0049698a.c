// FUN_0049698a @ 0049698a size=110 sig=undefined FUN_0049698a() cc=unknown
// callers: FUN_004969f8,FUN_00496cc3,FUN_00496adf,FUN_00496ffb,FUN_00496e80
// callees: FUN_0048e656
// strings: \"..\\\\src\\\\img.c\"

int FUN_0049698a(int param_1,uint param_2,int param_3,uint *param_4)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 == 0) {
    FUN_0048e656(0x1d6,s____src_img_c_0051e10c);
  }
  puVar1 = (uint *)(param_1 + 0x18);
  iVar2 = *(int *)(param_1 + 0x14);
  while( true ) {
    if (iVar2 == 0) {
      return 0;
    }
    iVar3 = param_3;
    if (((param_2 & 0xffffff) == (*puVar1 & 0xffffff)) && (iVar3 = param_3 + -1, param_3 == 0))
    break;
    puVar1 = puVar1 + 2;
    iVar2 = iVar2 + -1;
    param_3 = iVar3;
  }
  if (param_4 != (uint *)0x0) {
    *param_4 = *puVar1;
  }
  return param_1 + puVar1[1];
}

