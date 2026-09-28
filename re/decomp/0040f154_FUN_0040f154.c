// FUN_0040f154 @ 0040f154 size=242 sig=undefined FUN_0040f154() cc=unknown
// callers: FUN_0040f248
// callees: FUN_00401440,FUN_004412d4

undefined * FUN_0040f154(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  ushort *local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined *local_c;
  
  cVar1 = *(char *)(param_1 + 8);
  local_c = (undefined *)0x0;
  local_10 = -1000000;
  local_14 = 0;
  local_1c = (ushort *)(param_2 + 0x890);
  do {
    uVar4 = *local_1c;
    for (iVar7 = 0; (uVar4 != 0 && (iVar7 < 0x10)); iVar7 = iVar7 + 1) {
      if ((uVar4 & 1) != 0) {
        iVar2 = local_14 * 0x10 + iVar7;
        iVar5 = iVar2 * 0xadc;
        puVar6 = &DAT_005a43d0 + iVar5;
        iVar3 = (int)(char)(&DAT_005a43f0)[iVar5];
        if ((iVar3 != -1) && (iVar3 != cVar1)) {
          iVar3 = FUN_004412d4((int)cVar1,iVar3,2);
          if (iVar3 == 0) goto LAB_0040f215;
        }
        local_18 = (&DAT_005a4de2)[iVar2 * 0x2b7] - *(int *)(&DAT_005a4e30 + iVar5);
        iVar2 = FUN_00401440(param_1,puVar6,0);
        if (iVar2 != 0) {
          local_18 = local_18 + 100000000;
        }
        iVar2 = FUN_00401440(param_1,puVar6,1);
        if ((iVar2 != 0) && (local_10 < local_18)) {
          local_10 = local_18;
          local_c = puVar6;
        }
      }
LAB_0040f215:
      uVar4 = (short)uVar4 >> 1;
    }
    local_14 = local_14 + 1;
    local_1c = local_1c + 1;
    if (6 < local_14) {
      return local_c;
    }
  } while( true );
}

