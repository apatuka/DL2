// FUN_00437668 @ 00437668 size=173 sig=undefined FUN_00437668() cc=unknown
// callers: FUN_00437718
// callees: FUN_004375f4,FUN_0048db5d,FUN_00426594,FUN_004a2cb5,FUN_004371e4,FUN_004375ec

int FUN_00437668(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int local_8;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_004371e4();
  iVar1 = FUN_004a2cb5(DAT_004c4670,&local_8);
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004c4670 + 100) == 0)) {
    if (local_8 == 10) {
      FUN_00426594(&DAT_004d2d9c);
      DAT_004d59a4 = 0;
      return local_8;
    }
    if (local_8 == 0xb) {
      FUN_004375f4(param_1,param_2);
      DAT_004d59a4 = 0;
      return local_8;
    }
    if (local_8 == 0xc) {
      FUN_004375ec();
      DAT_004d59a4 = 0;
      return local_8;
    }
  }
  DAT_004d59a4 = 0;
  return 0;
}

