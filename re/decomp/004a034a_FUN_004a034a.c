// FUN_004a034a @ 004a034a size=133 sig=undefined FUN_004a034a() cc=unknown
// callers: FUN_004a0e79
// callees: FUN_0048c85e,FUN_0049ff48,FUN_0049f09b,FUN_0049fe03

undefined4 FUN_004a034a(int param_1,int param_2)

{
  uint uVar1;
  undefined1 local_24 [16];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_0049f09b(param_2,local_24);
  uVar1 = *(uint *)(param_2 + 0x24) & 0x1f;
  if (uVar1 == 2) {
    FUN_0049fe03(param_2,local_24);
    FUN_0049ff48(param_2,local_24);
  }
  else if ((uVar1 == 4) && (*(int *)(param_2 + 0x38) != 0)) {
    local_14 = 0;
    local_10 = 0;
    local_8 = *(undefined4 *)(*(int *)(param_2 + 0x38) + 8);
    local_c = *(undefined4 *)(*(int *)(param_2 + 0x38) + 4);
    FUN_0048c85e(*(undefined4 *)(param_2 + 0x38),*(undefined4 *)(param_1 + 0x3c),&local_14,local_24,
                 0,&DAT_0065e580,0);
  }
  return 1;
}

