// FUN_00419154 @ 00419154 size=651 sig=undefined FUN_00419154() cc=unknown
// callers: FUN_00419710
// callees: FUN_00416e70,FUN_0049eb44,FUN_00419110,FUN_00417188,FUN_004190c0,FUN_00491a2b,sprintf,FUN_00491ace
// strings: \"No Mission\"

void FUN_00419154(void)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined **ppuVar6;
  char cVar7;
  int local_dc;
  undefined1 local_d8 [200];
  
  cVar7 = '\0';
  iVar3 = FUN_0049eb44(DAT_004b76b4,0x2c,1,0x1a,0,0);
  iVar3 = iVar3 + -10;
  local_dc = *(int *)(DAT_004b76b4 + 0x38);
  if (((local_dc != 0) || (iVar4 = FUN_0049eb44(DAT_004b76b4,0x2c,1,0x10,0,&local_dc), iVar4 != 0))
     && (local_dc != 0)) {
    FUN_00491a2b(local_dc);
  }
  FUN_004190c0(cVar7,iVar3);
  if (DAT_004b76b8 == '\0') {
    ppuVar6 = &PTR_s_No_Mission_00509dcc;
    iVar4 = 0;
    cVar1 = (&DAT_0059f162)[*(char *)(DAT_004b76bc + 8) * 0x2d8];
    do {
      cVar2 = FUN_00416e70(DAT_004b76bc,iVar4,(int)cVar1);
      if (cVar2 != '\0') {
        sprintf(local_d8,&DAT_004b76c8,*ppuVar6);
        if (local_dc != 0) {
          FUN_00419110(local_d8,iVar3);
        }
        iVar5 = FUN_0049eb44(DAT_004b76b4,0x2c,1,0x26,0xffffffff,local_d8);
        (&DAT_0053b217)[iVar5] = (char)iVar4;
        if (iVar4 == *(char *)(DAT_004b76bc + 0x25)) {
          cVar7 = '\x01';
          DAT_0053b250 = iVar5 + -1;
          FUN_0049eb44(DAT_004b76b4,0x2c,1,0x1b,iVar5 + -1,0);
          FUN_0049eb44(DAT_004b76b4,0x2c,1,0x21,iVar5 + -1,1);
          sprintf(local_d8,&DAT_004b76c8,*ppuVar6);
          FUN_0049eb44(DAT_004b76b4,0x2b,1,0xf,0,local_d8);
        }
      }
      iVar4 = iVar4 + 1;
      ppuVar6 = ppuVar6 + 1;
    } while (iVar4 < 0x1b);
  }
  else {
    ppuVar6 = &PTR_s_No_Mission_00509dcc;
    iVar4 = 0;
    cVar1 = (&DAT_0059f162)[*(char *)(DAT_004b76bc + 8) * 0x2d8];
    do {
      cVar2 = FUN_00417188(iVar4,(int)cVar1);
      if (cVar2 != '\0') {
        sprintf(local_d8,&DAT_004b76c8,*ppuVar6);
        FUN_00419110(local_d8,iVar3);
        iVar5 = FUN_0049eb44(DAT_004b76b4,0x2c,1,0x26,0xffffffff,local_d8);
        (&DAT_0053b217)[iVar5] = (char)iVar4;
      }
      iVar4 = iVar4 + 1;
      ppuVar6 = ppuVar6 + 1;
    } while (iVar4 < 0x1b);
  }
  if (local_dc != 0) {
    FUN_00491ace();
  }
  if (cVar7 == '\0') {
    DAT_0053b250 = 0;
    FUN_0049eb44(DAT_004b76b4,0x2c,1,0x1b,0,0);
    sprintf(local_d8,&DAT_004b76c8,PTR_s_No_Mission_00509dcc);
    FUN_0049eb44(DAT_004b76b4,0x2b,1,0xf,0,local_d8);
  }
  FUN_0049eb44(DAT_004b76b4,0x2d,1,0x31,0x2c,1);
  return;
}

