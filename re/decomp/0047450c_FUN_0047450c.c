// FUN_0047450c @ 0047450c size=162 sig=undefined FUN_0047450c() cc=unknown
// callers: FUN_004745b0
// callees: IsDlgButtonChecked,FUN_004743d0,CheckDlgButton

void FUN_0047450c(HWND param_1)

{
  UINT UVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 local_18 [5];
  
  uVar3 = (int)*(short *)(DAT_006534c0 + 2) & 0xff;
  puVar4 = &DAT_004d6440;
  puVar5 = local_18;
  for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  if (uVar3 < 5) {
    UVar1 = IsDlgButtonChecked(param_1,0x12d);
    if (UVar1 == 0) {
      *(undefined1 *)(DAT_006534c0 + 4) = 0;
    }
    else {
      *(undefined1 *)(DAT_006534c0 + 4) = *(undefined1 *)(local_18 + uVar3);
    }
    FUN_004743d0(param_1,uVar3);
    DAT_006534c5 = 1;
  }
  else {
    UVar1 = IsDlgButtonChecked(param_1,0x12d);
    if (UVar1 != 0) {
      DAT_006534c5 = 1;
    }
    *(undefined1 *)(DAT_006534c0 + 4) = 0;
    CheckDlgButton(param_1,0x12d,0);
  }
  return;
}

