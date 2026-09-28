// FUN_0044cce4 @ 0044cce4 size=106 sig=undefined FUN_0044cce4() cc=unknown
// callers: FUN_0044f3f0,_DeleteBuilding
// callees: 

void FUN_0044cce4(int param_1,int param_2,int param_3,int param_4)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  
  for (iVar3 = param_3; iVar2 = param_2, param_3 - param_4 < iVar3; iVar3 = iVar3 + -1) {
    for (; iVar2 < param_4 + param_2; iVar2 = iVar2 + 1) {
      puVar1 = (ushort *)(param_1 + 0x142 + (iVar3 * 6 + iVar2) * 0x34);
      *puVar1 = *puVar1 & 0xff;
    }
  }
  *(undefined4 *)(param_1 + 0x154 + (param_2 + param_3 * 6) * 0x34) = 0;
  return;
}

