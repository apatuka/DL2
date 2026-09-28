// FUN_004968c8 @ 004968c8 size=62 sig=undefined FUN_004968c8() cc=unknown
// callers: FUN_00496906
// callees: FUN_0048e656
// strings: \"..\\\\src\\\\img.c\"

int * FUN_004968c8(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 == 0) {
    FUN_0048e656(0x198,s____src_img_c_0051e0f2);
  }
  piVar1 = (int *)(param_1 + 0x18);
  iVar2 = *(int *)(param_1 + 0x14);
  while( true ) {
    if (iVar2 == 0) {
      return (int *)0x0;
    }
    if (param_2 == *piVar1) break;
    piVar1 = piVar1 + 2;
    iVar2 = iVar2 + -1;
  }
  return piVar1;
}

