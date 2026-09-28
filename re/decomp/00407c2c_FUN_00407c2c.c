// FUN_00407c2c @ 00407c2c size=307 sig=undefined FUN_00407c2c() cc=unknown
// callers: FUN_0047681c
// callees: FUN_0040774c,FUN_004076ac,FUN_004727dc,FUN_00407714,FUN_00430b94,FUN_0046ca40,FUN_0040526c

bool FUN_00407c2c(int param_1,int param_2,undefined4 param_3,int param_4,int param_5)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  int local_c;
  
  bVar7 = false;
  bVar1 = *(byte *)(param_1 + 0x20);
  iVar5 = (int)(char)bVar1;
  iVar6 = (int)*(char *)(param_2 + 0x20);
  local_c = 0;
  iVar2 = FUN_004727dc(param_1,param_2);
  FUN_004076ac(iVar6);
  if ((100 < DAT_00522520 - (param_5 + iVar2) * param_4) &&
     (iVar3 = FUN_00430b94(param_3), param_5 + iVar2 < iVar3 * 2)) {
    if ((-0x14 < *(int *)(&DAT_005220a4 + iVar5 * 4 + iVar6 * 0x1c)) &&
       ((1 << (bVar1 & 0x1f) & *(uint *)(&DAT_0052222c + iVar6 * 4)) == 0)) {
      iVar3 = FUN_00407714(param_3,500);
      if (iVar3 == 0) {
        local_c = 0x19;
      }
      iVar3 = FUN_0040774c(param_3,100);
      if (iVar3 != 0) {
        local_c = local_c + 0x19;
      }
      local_c = local_c + (*(int *)(&DAT_005220a4 + iVar5 * 4 + iVar6 * 0x1c) * 0x28 + 800) / 0x46;
      iVar3 = FUN_00430b94(param_3);
      if (iVar2 + param_5 < iVar3) {
        local_c = local_c + 10;
      }
    }
    uVar4 = FUN_0046ca40();
    bVar7 = (int)(uVar4 % 100) < local_c;
    if (bVar7) {
      FUN_0040526c(iVar6,iVar5,4);
    }
  }
  return bVar7;
}

