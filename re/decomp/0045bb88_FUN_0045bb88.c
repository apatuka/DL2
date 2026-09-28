// FUN_0045bb88 @ 0045bb88 size=136 sig=undefined FUN_0045bb88() cc=unknown
// callers: FUN_0045bc10,FUN_0045dd18
// callees: FUN_00418d18,FUN_00418cf4,FUN_00419e0c,FUN_00419678,FUN_004197a8,FUN_004197dc

void FUN_0045bb88(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (DAT_004d59b4 != 0x22) {
    FUN_00419678();
  }
  if ((999 < param_2) && (param_2 < 9000)) {
    param_2 = param_2 + -1000;
    if (param_2 == 5) {
      param_2 = 1;
    }
    iVar1 = FUN_00419e0c(param_2);
  }
  if (iVar1 == 0) {
    if (DAT_004d59b4 != 0x22) {
      FUN_004197dc(param_1,0);
    }
  }
  else {
    if (DAT_004d59b4 == 0x22) {
      FUN_004197a8();
    }
    else {
      FUN_004197dc(param_1,1);
    }
    FUN_00418d18();
    FUN_00418cf4();
  }
  return;
}

