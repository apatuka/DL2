// FUN_004a7c94 @ 004a7c94 size=136 sig=undefined FUN_004a7c94() cc=unknown
// callers: FUN_004a7d1c,Local_unwind
// callees: FUN_004a7c1f,__assertfail
// strings: \"XX.CPP\"|\"argType\"

void FUN_004a7c94(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = DAT_0069f3a8;
  if (*(char *)(param_1 + 0x44) != '\0') {
    if ((*(byte *)(param_1 + 0x1a) & 2) != 0) {
      FUN_004a7c1f(param_1 + 0x46,param_1,*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x28),
                   *(undefined2 *)(*(int *)(param_1 + 0x14) + 0x2c));
    }
    DAT_0069f3a8 = uVar2;
    *(undefined1 *)(param_1 + 0x44) = 0;
  }
  if (*(char *)(param_1 + 0x45) != '\0') {
    iVar1 = *(int *)(param_1 + 0x3c);
    if (iVar1 == 0) {
      __assertfail(s_argType_0051f36f,s_XX_CPP_0051f377,0x5ac);
    }
    if (((*(byte *)(iVar1 + 4) & 2) != 0) && ((*(byte *)(iVar1 + 0xc) & 2) != 0)) {
      FUN_004a7c1f(*(undefined4 *)(param_1 + 0x40),iVar1,*(undefined4 *)(iVar1 + 0x28),
                   *(undefined2 *)(iVar1 + 0x2c));
    }
    *(undefined1 *)(param_1 + 0x45) = 0;
  }
  return;
}

