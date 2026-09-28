// FUN_0049e47a @ 0049e47a size=444 sig=undefined FUN_0049e47a() cc=unknown
// callers: FUN_004a0e79
// callees: FUN_00491a2b,FUN_0049de78,FUN_00492036,FUN_00491ace,FUN_0049ddf8,FUN_00492d67,FUN_00491efa,FUN_0049f664,FUN_00491fe9,FUN_004935fc,FUN_0049eb9f,FUN_00491b5e,FUN_0049eafa,FUN_004931b0,FUN_0049f09b,FUN_00491e02

undefined4 FUN_0049e47a(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_28 [4];
  short local_24;
  short local_22;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  uVar4 = 0;
  FUN_0049f09b(param_2,&local_1c);
  iVar1 = FUN_0049eafa(param_2);
  uVar2 = *(uint *)(param_2 + 0x24) & 0x1f;
  if ((uVar2 == 0) || ((uVar2 != 8 && (uVar2 == 0x10)))) {
    if ((*(int *)(param_2 + 0x34) != 0) || ((*(byte *)(param_2 + 0x24) & 0x80) != 0)) {
      FUN_00491a2b(0);
      iVar3 = FUN_0049eb9f(param_2,0);
      if (iVar3 != 0) {
        if (((*(byte *)(param_2 + 0x24) & 0x80) != 0) && (iVar1 == 1)) {
          iVar1 = 0;
        }
        if ((*(byte *)(param_2 + 0xab + iVar1 * 4) & 0x40) == 0) {
          uVar4 = *(undefined4 *)(param_2 + 0xa8 + iVar1 * 4);
        }
        else {
          uVar4 = *(undefined4 *)(param_1 + 0xf0 + iVar1 * 4);
        }
        FUN_00491efa(uVar4);
        if ((*(byte *)(param_2 + 0x9f + iVar1 * 4) & 0x40) == 0) {
          uVar4 = *(undefined4 *)(param_2 + 0x9c + iVar1 * 4);
        }
        else {
          uVar4 = *(undefined4 *)(param_1 + 0xc0 + iVar1 * 4);
        }
        FUN_00491e02(uVar4);
        if ((*(byte *)(param_2 + 0xc3 + iVar1 * 4) & 0x40) == 0) {
          uVar4 = *(undefined4 *)(param_2 + 0xc0 + iVar1 * 4);
        }
        else {
          uVar4 = *(undefined4 *)(param_1 + 0xd8 + iVar1 * 4);
        }
        FUN_00491fe9(uVar4);
        if ((*(byte *)(param_2 + 0xb7 + iVar1 * 4) & 0x40) == 0) {
          uVar4 = *(undefined4 *)(param_2 + 0xb4 + iVar1 * 4);
        }
        else {
          uVar4 = *(undefined4 *)(param_1 + 0xcc + iVar1 * 4);
        }
        FUN_00492036(uVar4);
        iVar1 = FUN_0049ddf8(param_2);
        if ((((iVar1 != 0) && (FUN_00492d67(iVar1), (*(byte *)(param_2 + 0x24) & 0x80) != 0)) &&
            (FUN_0049de78(iVar1), (*(byte *)(param_2 + 0xfb) & 0xc0) == 0)) &&
           (((*(int *)(iVar1 + 0x18) == *(int *)(iVar1 + 0x1c) &&
             (iVar3 = FUN_0049f664(param_2), iVar3 != 0)) && ((*(byte *)(param_2 + 0x28) & 4) == 0))
           )) {
          FUN_004931b0(*(undefined4 *)(param_2 + 0x34),local_14 - local_1c,local_10 - local_18,
                       *(undefined4 *)(iVar1 + 0x1c),&local_8,&local_c,0,
                       *(undefined4 *)(iVar1 + 0x14));
          FUN_00491b5e(local_28);
          FUN_004935fc(local_1c + local_8,local_18 + local_c,local_1c + local_8 + 1,
                       local_18 + local_c + (int)local_24 + (int)local_22,0x80ffffff);
        }
      }
      FUN_00491ace();
    }
    uVar4 = 1;
  }
  return uVar4;
}

