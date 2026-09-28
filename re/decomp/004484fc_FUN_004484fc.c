// FUN_004484fc @ 004484fc size=235 sig=undefined FUN_004484fc() cc=unknown
// callers: MoveHousingLabor,FUN_00448700,FUN_004485e8
// callees: FUN_0044eeb4,FUN_0044c718,FUN_004023dc

int FUN_004484fc(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_004023dc(param_3,param_1);
  if (param_1 == 2) {
    iVar2 = FUN_0044eeb4(&DAT_0059f160 + *(char *)(param_2 + 0x20) * 0x2d8,param_2,
                         (int)*(char *)(param_3 + 7),iVar1,
                         *(undefined4 *)(param_3 + 0x18 + iVar1 * 4));
    iVar2 = *(short *)(param_3 + 0x14) - iVar2;
    if (0 < iVar2) {
      iVar2 = 10000 - iVar2;
    }
  }
  else if (param_1 == 0x15) {
    iVar2 = FUN_0044c718(param_3);
    iVar2 = iVar2 - *(short *)(param_3 + 0x16);
    iVar1 = FUN_0044eeb4(&DAT_0059f160 + *(char *)(param_2 + 0x20) * 0x2d8,param_2,
                         (int)*(char *)(param_3 + 7),iVar1,
                         *(undefined4 *)(param_3 + 0x18 + iVar1 * 4));
    iVar2 = iVar2 - iVar1;
    if (0 < iVar2) {
      iVar2 = 10000 - iVar2;
    }
  }
  else {
    iVar2 = FUN_0044eeb4(&DAT_0059f160 + *(char *)(param_2 + 0x20) * 0x2d8,param_2,
                         (int)*(char *)(param_3 + 7),iVar1,1);
  }
  return iVar2;
}

