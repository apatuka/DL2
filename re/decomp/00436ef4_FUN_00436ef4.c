// FUN_00436ef4 @ 00436ef4 size=527 sig=undefined FUN_00436ef4() cc=unknown
// callers: FUN_0044930c
// callees: FUN_00436d90,FUN_0047654c,FUN_00426594,FUN_00436a44,FUN_00436ec8,FUN_004a2cb5,FUN_004765a8,FUN_00436d84

undefined8 FUN_00436ef4(void)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  char *pcVar4;
  int local_c;
  
  DAT_0051b824 = 1;
  iVar1 = FUN_004a2cb5(DAT_004c4664,&local_c);
  if (((iVar1 != 0) || (local_c == 0)) || (*(int *)(DAT_004c4664 + 100) != 0))
  goto switchD_00436f40_default;
  switch(local_c) {
  case 4:
    FUN_0047654c(DAT_0058f1f4,(int)(char)PTR_DAT_004d5988[0xb]);
    iVar1 = 0;
    pcVar4 = &DAT_005a43f0;
    do {
      if (*pcVar4 == DAT_0058f1f4) {
        FUN_004765a8(DAT_0058f1f4,iVar1,(int)pcVar4[6]);
      }
      iVar1 = iVar1 + 1;
      pcVar4 = pcVar4 + 0xadc;
    } while (iVar1 < 0x70);
    FUN_00436ec8();
    iVar1 = local_c;
    goto LAB_0043712f;
  case 5:
    iVar1 = 0;
    puVar2 = &DAT_00558eb5;
    PTR_DAT_004d5988[0xb] = DAT_00558eb4;
    puVar3 = &DAT_005a43f6;
    do {
      *puVar3 = *puVar2;
      iVar1 = iVar1 + 1;
      puVar3 = puVar3 + 0xadc;
      puVar2 = puVar2 + 1;
    } while (iVar1 < 0x70);
    FUN_00436ec8();
    iVar1 = local_c;
    goto LAB_0043712f;
  case 6:
    FUN_00426594(&DAT_004d29d0);
    break;
  case 7:
    PTR_DAT_004d5988[0xb] = 0;
    FUN_00436a44();
    FUN_00436d90();
    break;
  case 8:
    PTR_DAT_004d5988[0xb] = 1;
    FUN_00436a44();
    FUN_00436d90();
    break;
  case 9:
    PTR_DAT_004d5988[0xb] = 2;
    FUN_00436a44();
    FUN_00436d90();
    break;
  case 10:
    PTR_DAT_004d5988[0xb] = 3;
    FUN_00436a44();
    FUN_00436d90();
    break;
  case 0xb:
    PTR_DAT_004d5988[0xb] = 4;
    FUN_00436a44();
    FUN_00436d90();
    break;
  case 0xc:
    PTR_DAT_004d5988[0xb] = 5;
    FUN_00436a44();
    FUN_00436d90();
    break;
  case 0xd:
    (&DAT_005a43f6)[DAT_004c5b50 * 0xadc] = 0xff;
    FUN_00436a44();
    FUN_00436d90();
    break;
  case 0xe:
    (&DAT_005a43f6)[DAT_004c5b50 * 0xadc] = 0;
    FUN_00436a44();
    FUN_00436d90();
    break;
  case 0xf:
    (&DAT_005a43f6)[DAT_004c5b50 * 0xadc] = 1;
    FUN_00436a44();
    FUN_00436d90();
  }
switchD_00436f40_default:
  FUN_00436d84();
  iVar1 = 0;
LAB_0043712f:
  return CONCAT44(local_c,iVar1);
}

