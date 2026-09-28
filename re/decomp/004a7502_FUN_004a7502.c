// FUN_004a7502 @ 004a7502 size=194 sig=undefined FUN_004a7502() cc=unknown
// callers: FUN_004a8257,_ExceptionHandler
// callees: FUN_004a9335

bool FUN_004a7502(int param_1,undefined4 param_2,int param_3,byte param_4)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  
  iVar3 = FUN_004a9335(param_1,param_3,0,param_2);
  if (iVar3 != 0) {
    return true;
  }
  uVar1 = *(ushort *)(param_1 + 4);
  uVar2 = *(ushort *)(param_3 + 4);
  if ((uVar2 & 0x20) != 0) {
    iVar3 = FUN_004a9335(param_1,*(undefined4 *)(param_3 + 8),1,param_2);
    if (iVar3 != 0) {
      return true;
    }
    uVar2 = *(ushort *)(*(int *)(param_3 + 8) + 4);
    if ((uVar2 & 0x10) == 0) {
      return false;
    }
    iVar3 = FUN_004a9335(param_1,*(int *)(param_3 + 8),0,param_2);
    if (iVar3 != 0) {
      return true;
    }
  }
  if ((uVar2 & 0x10) != 0) {
    if ((param_4 & 1) != 0) {
      return true;
    }
    if ((uVar1 & 0x10) == 0) {
      return false;
    }
    if ((uVar2 & 0x40) != 0) {
      return (uVar1 & 0x300) == (uVar2 & 0x300);
    }
  }
  return false;
}

