// FUN_00496a5c @ 00496a5c size=59 sig=undefined FUN_00496a5c() cc=unknown
// callers: 
// callees: FUN_0048e656
// strings: \"..\\\\src\\\\img.c\"

int FUN_00496a5c(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  if (param_1 == 0) {
    FUN_0048e656(0x218,s____src_img_c_0051e126);
  }
  piVar2 = (int *)(param_1 + 0x18);
  iVar1 = 0;
  while( true ) {
    if (*(int *)(param_1 + 0x14) <= iVar1) {
      return -1;
    }
    if (param_2 == *piVar2) break;
    piVar2 = piVar2 + 2;
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

