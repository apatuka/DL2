// FUN_004845d4 @ 004845d4 size=41 sig=undefined FUN_004845d4() cc=unknown
// callers: FUN_00484600,FUN_004835bc
// callees: FUN_00491bd5

void FUN_004845d4(uint param_1)

{
  if (*(int *)(&DAT_00508f9c + (param_1 & 1) * 4) != 0) {
    FUN_00491bd5(*(int *)(&DAT_00508f9c + (param_1 & 1) * 4));
    *(undefined4 *)(&DAT_00508f9c + (param_1 & 1) * 4) = 0;
  }
  return;
}

