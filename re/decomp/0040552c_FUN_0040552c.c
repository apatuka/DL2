// FUN_0040552c @ 0040552c size=151 sig=undefined FUN_0040552c() cc=unknown
// callers: FUN_00410870,FUN_004489e0,FUN_0040d228,FUN_0040d080,FUN_004055f8,FUN_004055c4
// callees: FUN_0044eeb4,FUN_004023dc,FUN_0044ba40

int FUN_0040552c(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int local_8;
  
  local_8 = 0;
  iVar5 = 0;
  piVar4 = (int *)(param_1 + 0x154);
  do {
    iVar3 = *piVar4;
    if (iVar3 != 0) {
      iVar1 = FUN_004023dc(iVar3,param_2);
      if (param_3 == 0) {
        uVar2 = *(undefined4 *)(iVar3 + 0x18 + iVar1 * 4);
      }
      else {
        uVar2 = FUN_0044ba40(iVar3);
      }
      if (iVar1 != -1) {
        iVar3 = FUN_0044eeb4(&DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8,param_1,
                             (int)*(char *)(iVar3 + 7),iVar1,uVar2);
        local_8 = local_8 + iVar3;
      }
    }
    iVar5 = iVar5 + 1;
    piVar4 = piVar4 + 0xd;
  } while (iVar5 < 0x24);
  return local_8;
}

