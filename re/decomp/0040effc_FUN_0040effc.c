// FUN_0040effc @ 0040effc size=98 sig=undefined FUN_0040effc() cc=unknown
// callers: FUN_0040f2e0
// callees: FUN_0040be04,FUN_0040c68c

void FUN_0040effc(int param_1)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = (int)*(short *)(param_1 + 10);
  sVar1 = *(short *)(param_1 + 8);
  uVar2 = *(undefined4 *)(param_1 + 0x10);
  iVar3 = FUN_0040c68c(iVar4,0x12,uVar2);
  if (iVar3 == 0) {
    FUN_0040be04(iVar4,0,(int)sVar1,uVar2,0x12,(int)*(short *)(param_1 + 0xe));
  }
  iVar3 = FUN_0040c68c(iVar4,0x11,uVar2);
  if (iVar3 == 0) {
    FUN_0040be04(iVar4,0,(int)sVar1,uVar2,0x11,(int)*(short *)(param_1 + 0xe));
  }
  return;
}

