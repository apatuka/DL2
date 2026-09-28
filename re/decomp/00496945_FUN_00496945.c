// FUN_00496945 @ 00496945 size=69 sig=undefined FUN_00496945() cc=unknown
// callers: FUN_00494c15,FUN_004966f3,FUN_00496a97,FUN_0049659f,FUN_004940f0
// callees: FUN_0048e656
// strings: \"..\\\\src\\\\img.c\"

int FUN_00496945(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 == 0) {
    FUN_0048e656(0x1c0,s____src_img_c_0051e0ff);
  }
  piVar1 = (int *)(param_1 + 0x18);
  iVar2 = *(int *)(param_1 + 0x14);
  while( true ) {
    if (iVar2 == 0) {
      return 0;
    }
    if (param_2 == *piVar1) break;
    piVar1 = piVar1 + 2;
    iVar2 = iVar2 + -1;
  }
  return param_1 + piVar1[1];
}

