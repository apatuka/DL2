// FUN_00484600 @ 00484600 size=59 sig=undefined FUN_00484600() cc=unknown
// callers: FUN_00465e20
// callees: FUN_004845d4,FUN_00490ab3

bool FUN_00484600(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  FUN_004845d4(param_2 & 1);
  iVar1 = FUN_00490ab3(0,0x544e4f46,param_1,0,0x80000000);
  *(int *)(&DAT_00508f9c + (param_2 & 1) * 4) = iVar1;
  return iVar1 != 0;
}

