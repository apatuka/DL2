// FUN_004745b0 @ 004745b0 size=358 sig=undefined FUN_004745b0() cc=unknown
// callers: @EditTileResourcesDialog$qqspvuiuil
// callees: FUN_004743d0,SendDlgItemMessageA,EndDialog,FUN_0047450c,FUN_0044a000,FUN_004669d8

undefined4 FUN_004745b0(HWND param_1,undefined4 param_2)

{
  WPARAM wParam;
  LRESULT LVar1;
  undefined4 uVar2;
  short sVar3;
  int iVar4;
  
  iVar4 = DAT_006534c0;
  sVar3 = (short)param_2;
  if (sVar3 == 1) {
    FUN_0044a000();
    EndDialog(param_1,1);
    uVar2 = 1;
  }
  else if (sVar3 == 2) {
    if (DAT_006534c5 == '\0') {
      EndDialog(param_1,1);
      uVar2 = 1;
    }
    else {
      *(undefined2 *)(DAT_006534c0 + 8) = DAT_00653498;
      *(undefined2 *)(iVar4 + 10) = DAT_0065349a;
      *(undefined2 *)(iVar4 + 6) = DAT_0065349c;
      *(undefined2 *)(iVar4 + 0xc) = DAT_0065349e;
      *(undefined2 *)(iVar4 + 0xe) = DAT_006534a0;
      *(undefined1 *)(iVar4 + 4) = DAT_006534c4;
      *(undefined2 *)(iVar4 + 2) = DAT_006534a2;
      FUN_0044a000();
      EndDialog(param_1,1);
      uVar2 = 1;
    }
  }
  else if (sVar3 == 0x12d) {
    FUN_0047450c(param_1);
    uVar2 = 1;
  }
  else if (sVar3 == 0x12e) {
    if ((short)((uint)param_2 >> 0x10) == 1) {
      wParam = SendDlgItemMessageA(param_1,0x12e,0x188,0,0);
      LVar1 = SendDlgItemMessageA(param_1,0x12e,0x199,wParam,0);
      if (LVar1 == 6) {
        LVar1 = 0xff;
      }
      *(ushort *)(DAT_006534c0 + 2) = *(ushort *)(DAT_006534c0 + 2) & 0xff00 | (ushort)LVar1;
      FUN_0047450c(param_1);
      FUN_004669d8(0);
      iVar4 = 0;
      do {
        FUN_004743d0(param_1,iVar4);
        iVar4 = iVar4 + 1;
      } while (iVar4 < 5);
      DAT_006534c5 = '\x01';
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

