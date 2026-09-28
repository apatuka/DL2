// FUN_00409544 @ 00409544 size=355 sig=undefined FUN_00409544() cc=unknown
// callers: FUN_004096a8
// callees: FUN_004412d4,FUN_0040be04,FUN_0040c68c

void FUN_00409544(int param_1,int param_2)

{
  char cVar1;
  bool bVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  ushort uVar6;
  ushort *local_20;
  int local_1c;
  int local_18;
  undefined *local_10;
  undefined *local_c;
  
  cVar1 = (&DAT_0059f1bf)[param_1 * 0x2d8];
  local_c = (undefined *)0x0;
  local_10 = (undefined *)0x0;
  bVar2 = false;
  local_18 = 0;
  local_20 = (ushort *)(param_2 + 0x890);
  do {
    uVar6 = *local_20;
    for (local_1c = 0; (uVar6 != 0 && (local_1c < 0x10)); local_1c = local_1c + 1) {
      puVar3 = local_c;
      if ((uVar6 & 1) != 0) {
        iVar4 = local_18 * 0x10 + local_1c;
        iVar5 = iVar4 * 0xadc;
        if ((&DAT_005a43f1)[iVar5] == '\0') {
          if ((param_1 == (char)(&DAT_005a43f0)[iVar5]) && ((&DAT_005a4400)[iVar4 * 0x56e] != 0)) {
            bVar2 = true;
          }
          else if (((((char)(&DAT_005a43f0)[iVar5] != -1) &&
                    (param_1 != (char)(&DAT_005a43f0)[iVar5])) ||
                   (puVar3 = &DAT_005a43d0 + iVar5, (&DAT_005a4400)[iVar4 * 0x56e] != 0)) &&
                  (((iVar4 = (int)(char)(&DAT_005a43f0)[iVar5], puVar3 = local_c, param_1 != iVar4
                    && (iVar4 != -1)) && (iVar4 = FUN_004412d4(param_1,iVar4,2), iVar4 == 0)))) {
            local_10 = &DAT_005a43d0 + iVar5;
          }
        }
      }
      local_c = puVar3;
      uVar6 = (short)uVar6 >> 1;
    }
    local_18 = local_18 + 1;
    local_20 = local_20 + 1;
  } while (local_18 < 7);
  if (((local_c == (undefined *)0x0) || (bVar2)) ||
     (iVar4 = FUN_0040c68c(param_1,10,local_c), iVar4 != 0)) {
    if (((local_10 != (undefined *)0x0) && (!bVar2)) &&
       (iVar4 = FUN_0040c68c(param_1,0x13,local_10), iVar4 == 0)) {
      FUN_0040be04(param_1,0xffffffff,(int)(char)local_10[0x20],local_10,0x13,(int)cVar1);
    }
  }
  else {
    FUN_0040be04(param_1,0xffffffff,0xffffffff,local_c,10,(int)cVar1);
  }
  return;
}

