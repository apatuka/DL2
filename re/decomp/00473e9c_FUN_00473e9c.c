// FUN_00473e9c @ 00473e9c size=829 sig=undefined FUN_00473e9c() cc=unknown
// callers: @EditTerritoryResourcesDialog$qqspvuiuil
// callees: FUN_00449dec,FUN_00482f94,FUN_00449fe8,EndDialog,SetDlgItemInt,FUN_0046c1f0,FUN_0046e56c,GetDlgItemInt,FUN_0046b0e4,FUN_0044bea8

undefined4 FUN_00473e9c(HWND param_1,undefined4 param_2)

{
  int iVar1;
  short sVar2;
  UINT UVar3;
  int iVar4;
  short *psVar5;
  short sVar6;
  short local_8;
  short local_6;
  
  iVar1 = DAT_004c5b50;
  sVar6 = (short)param_2;
  iVar4 = (int)sVar6;
  sVar2 = (short)((uint)param_2 >> 0x10);
  if (iVar4 < 0x65) {
    if (iVar4 != 100) {
      if (iVar4 == 1) {
        UVar3 = GetDlgItemInt(param_1,100,(BOOL *)0x0,0);
        local_6 = (short)UVar3;
        if ((0 < local_6) && (*(char *)(DAT_00657de0 + 0x20) == -1)) {
          FUN_0046e56c(DAT_00657de0,DAT_0058f1f4);
        }
        FUN_0046c1f0();
        sVar2 = FUN_0046b0e4(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
        _local_8 = CONCAT22(local_6,sVar2);
        if ((local_6 != DAT_006534a4) && ((local_6 <= sVar2 || (sVar2 != DAT_006534a4)))) {
          if (local_6 < sVar2) {
            psVar5 = &local_6;
          }
          else {
            psVar5 = &local_8;
          }
          _local_8 = CONCAT22(*psVar5,sVar2);
          (&DAT_005a4400)[DAT_004c5b50 * 0x56e] = *psVar5;
          FUN_0044bea8(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
          FUN_00449fe8();
          FUN_00449dec();
        }
        if ((char)(&DAT_005a43f0)[DAT_004c5b50 * 0xadc] == DAT_0058f1f4) {
          FUN_00482f94(PTR_DAT_004d5988);
        }
        EndDialog(param_1,1);
        return 1;
      }
      if (iVar4 != 2) {
        return 0;
      }
      if (DAT_006534c5 != '\0') {
        iVar4 = DAT_004c5b50 * 0xadc;
        (&DAT_005a4400)[DAT_004c5b50 * 0x56e] = (undefined2)DAT_006534a4;
        (&DAT_005a440e)[iVar1 * 0x2b7] = (int)DAT_00653498;
        (&DAT_005a4412)[iVar1 * 0x2b7] = (int)DAT_0065349c;
        *(int *)(&DAT_005a4416 + iVar4) = (int)DAT_0065349a;
        *(int *)(&DAT_005a441a + iVar4) = (int)DAT_0065349e;
        *(undefined4 *)(&DAT_005a441e + iVar4) = DAT_006534ac;
        *(int *)(&DAT_005a4422 + iVar4) = (int)DAT_006534a0;
        *(undefined4 *)(&DAT_005a4426 + iVar4) = DAT_006534b0;
        *(undefined4 *)(&DAT_005a442a + iVar4) = DAT_006534b4;
        *(undefined4 *)(&DAT_005a442e + iVar4) = DAT_006534b8;
        *(undefined4 *)(&DAT_005a4432 + iVar4) = DAT_006534bc;
      }
      EndDialog(param_1,1);
      return 1;
    }
    if (sVar2 == 0x300) {
      UVar3 = GetDlgItemInt(param_1,(int)sVar6,(BOOL *)0x0,0);
      if ((int)UVar3 < 0x2711) {
        if ((int)UVar3 < 0) {
          SetDlgItemInt(param_1,(int)sVar6,0,0);
        }
      }
      else {
        SetDlgItemInt(param_1,(int)sVar6,10000,0);
      }
      DAT_006534c5 = '\x01';
    }
  }
  else if (iVar4 == 0x65) {
    if (sVar2 == 0x300) {
      UVar3 = GetDlgItemInt(param_1,(int)sVar6,(BOOL *)0x0,0);
      if ((int)UVar3 < 0x186a1) {
        if ((int)UVar3 < 0) {
          UVar3 = 0;
          SetDlgItemInt(param_1,0x65,0,0);
        }
      }
      else {
        UVar3 = 100000;
        SetDlgItemInt(param_1,0x65,100000,0);
      }
      *(UINT *)(PTR_DAT_004d5988 + 0xc) = UVar3;
      DAT_006534c5 = '\x01';
    }
  }
  else {
    if (9 < iVar4 - 0x66U) {
      return 0;
    }
    if (sVar2 == 0x300) {
      UVar3 = GetDlgItemInt(param_1,(int)sVar6,(BOOL *)0x0,0);
      if ((int)UVar3 < 0x2711) {
        if ((int)UVar3 < 0) {
          UVar3 = 0;
          SetDlgItemInt(param_1,(int)sVar6,0,0);
        }
      }
      else {
        UVar3 = 10000;
        SetDlgItemInt(param_1,(int)sVar6,10000,0);
      }
      *(UINT *)(&DAT_005a4276 + sVar6 * 4 + DAT_004c5b50 * 0xadc) = UVar3;
      DAT_006534c5 = '\x01';
    }
  }
  return 0;
}

