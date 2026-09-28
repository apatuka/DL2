// FUN_0046ac44 @ 0046ac44 size=358 sig=undefined FUN_0046ac44() cc=unknown
// callers: FUN_00414b64,FUN_00408bf4,FUN_0041f7f0,FUN_004055f8,FUN_004500d8,FUN_004437c4,FUN_00408e3c,FUN_0041b330,WinMain,FUN_00436a44,FUN_00408fdc,FUN_004489e0,FUN_00415624,FUN_004076ac,FUN_0043c78c
// callees: FUN_0046ab18,FUN_00483c4c,FUN_0046b4d0,FUN_0046f89c,memset

void FUN_0046ac44(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  
  puVar6 = &DAT_005a43d0;
  iVar1 = param_2 * 0x2d8;
  memset(param_1,0,0x78);
  FUN_0046f89c();
  *(undefined4 *)(param_1 + 0x20) = (&DAT_0059f16c)[param_2 * 0xb6];
  if ((1 << ((byte)param_2 & 0x1f) & (int)DAT_004fc4da) != 0) {
    *(int *)(param_1 + 0x4c) = *(int *)(param_1 + 0x4c) + 0xfa;
  }
  for (iVar4 = 1; iVar4 <= DAT_004d5b18; iVar4 = iVar4 + 1) {
    if (((puVar6[0x1d] & 1) == 0) && ((char)puVar6[0x20] == param_2)) {
      FUN_0046ab18(puVar6,param_1);
    }
    puVar6 = puVar6 + 0xadc;
  }
  iVar4 = 0;
  iVar5 = 0;
  do {
    iVar2 = iVar5 * 0x5c;
    if (((iVar2 != -0x645370) && ((&DAT_00645376)[iVar2] != '\0')) &&
       ((char)(&DAT_00645378)[iVar2] == param_2)) {
      iVar4 = iVar4 + 1;
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x230);
  *(int *)(param_1 + 0x50) =
       *(int *)(param_1 + 0x50) -
       ((short)(&DAT_0055a156)[(char)(&DAT_0059f162)[param_2 * 0x2d8]] * iVar4) / 100;
  iVar4 = FUN_0046b4d0(param_2);
  *(int *)(param_1 + 0x4c) = (*(int *)(param_1 + 0xc) + *(int *)(param_1 + 8)) - iVar4;
  if (DAT_004d5804 == 0) {
    (&DAT_0059f1a0)[param_2 * 0x16c] = *(undefined2 *)(param_1 + 0x10);
  }
  *(int *)(param_1 + 0x14) = (int)(char)(&DAT_0059f19e)[iVar1];
  uVar3 = FUN_00483c4c(&DAT_0059f160 + iVar1,(int)(char)(&DAT_0059f19e)[iVar1]);
  *(undefined4 *)(param_1 + 0x1c) = uVar3;
  return;
}

