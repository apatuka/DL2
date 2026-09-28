// FUN_00474718 @ 00474718 size=450 sig=undefined FUN_00474718() cc=unknown
// callers: FUN_0043bd5c
// callees: FUN_0045df90,FUN_00472fb4,FUN_004050ac,FUN_00484270,sprintf,FUN_0046d2e8,FUN_0044a000,FUN_00441128,memset

undefined4 FUN_00474718(int param_1,int param_2,undefined1 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  byte bVar4;
  int iVar5;
  
  iVar1 = DAT_004d5aec;
  if (*(char *)(param_1 + 0x20) == -1) {
    if ((((*(char *)(param_1 + 0x21) == '\0') || (*(char *)(param_1 + 0x21) == '\x05')) ||
        (*(char *)(param_1 + 0x7e) == '\0')) || ((*(byte *)(param_1 + 0x1d) & 1) != 0)) {
      uVar3 = 2;
    }
    else if (DAT_004d5aec < 7) {
      bVar4 = (byte)DAT_004d5aec;
      DAT_0059f0fc = DAT_0059f0fc | '\x01' << (bVar4 & 0x1f);
      DAT_004d5aec = DAT_004d5aec + 1;
      (&DAT_0059f161)[iVar1 * 0x2d8] = 1;
      (&DAT_0059f160)[iVar1 * 0x2d8] = bVar4;
      (&DAT_0059f16c)[iVar1 * 0xb6] = 500;
      (&DAT_0059f19e)[iVar1 * 0x2d8] = 0;
      (&DAT_0059f16b)[iVar1 * 0x2d8] = 2;
      (&DAT_0059f19a)[iVar1 * 0xb6] = 0;
      memset(&DAT_0059f3da + iVar1 * 0xb6,0,0x1c);
      puVar2 = &DAT_0052245c + iVar1 * 7;
      for (iVar5 = 0; iVar5 < DAT_004d5aec; iVar5 = iVar5 + 1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      (&DAT_0059f198)[iVar1 * 0x2d8] = 0x7f;
      (&DAT_005a0548)[iVar1] = param_3;
      (&DAT_0059f162)[iVar1 * 0x2d8] = (undefined1)param_2;
      sprintf(&DAT_0059f413 + iVar1 * 0x2d8,(&PTR_s_Sting_00509938)[param_2]);
      FUN_0046d2e8(iVar1,param_1);
      FUN_004050ac();
      FUN_00472fb4(iVar1);
      DAT_004c5b50 = (int)(short)(&DAT_0059f166)[DAT_0058f1f4 * 0x16c];
      FUN_0045df90();
      (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] = (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] | 1;
      FUN_00441128();
      FUN_00484270(iVar1);
      FUN_0044a000();
      uVar3 = 0;
    }
    else {
      uVar3 = 3;
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

