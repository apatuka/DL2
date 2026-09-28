// FUN_0046b074 @ 0046b074 size=110 sig=undefined FUN_0046b074() cc=unknown
// callers: FUN_00405b38,FUN_00409d68,FUN_00409f6c,FUN_0046b0e4,FUN_0047fc84,FUN_00409e2c,FUN_0046b1ac
// callees: FUN_0044d1a4

int FUN_0046b074(int param_1)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  
  iVar3 = 0;
  if ((*(char *)(param_1 + 0x21) == '\0') && (iVar1 = FUN_0044d1a4(param_1,0x14,0), iVar1 != -1)) {
    iVar3 = 2000;
  }
  else {
    iVar1 = 0;
    puVar2 = (ushort *)(param_1 + 0x142);
    do {
      if ((*puVar2 & 0xff) < 5) {
        iVar3 = iVar3 + 1;
      }
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 0x1a;
    } while (iVar1 < 0x24);
    iVar3 = ((iVar3 * 0x8b + 0x32) / 100) * 100;
  }
  return iVar3;
}

