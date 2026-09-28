// FUN_004a9335 @ 004a9335 size=271 sig=undefined FUN_004a9335() cc=unknown
// callers: FUN_004a7502
// callees: FUN_004a9103,FUN_004a91de

undefined4 FUN_004a9335(int param_1,int param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  
  while( true ) {
    while( true ) {
      if (param_2 == param_1) {
        return 1;
      }
      uVar2 = *(ushort *)(param_1 + 4);
      uVar3 = *(ushort *)(param_2 + 4);
      if ((uVar3 & uVar2 & 0x10) == 0) break;
      uVar6 = uVar2 & 0x300;
      uVar1 = uVar3 & 0x300;
      if (uVar6 != uVar1) {
        if ((param_3 != 0) || (uVar6 == uVar1)) {
          return 0;
        }
        if ((byte)(~(byte)(uVar1 >> 8) & (byte)(uVar6 >> 8)) != 0) {
          return 0;
        }
      }
      param_3 = 1;
      param_1 = *(int *)(param_1 + 8);
      param_2 = *(int *)(param_2 + 8);
    }
    if ((uVar3 & uVar2 & 0x400) == 0) break;
    if ((*(int *)(param_1 + 0xc) != *(int *)(param_2 + 0xc)) &&
       ((param_3 != 0 || (*(int *)(param_1 + 0xc) != 0 || *(int *)(param_2 + 0xc) != 0)))) {
      return 0;
    }
    param_3 = 1;
    param_1 = *(int *)(param_1 + 8);
    param_2 = *(int *)(param_2 + 8);
  }
  iVar4 = FUN_004a9103(param_1,param_2);
  if (iVar4 != 0) {
    return 1;
  }
  if ((((uVar2 & 2) != 0) && ((uVar3 & 1) != 0)) && ((*(byte *)(param_1 + 0xc) & 4) != 0)) {
    uVar5 = FUN_004a91de(param_1,param_2,param_4,1);
    return uVar5;
  }
  return 0;
}

