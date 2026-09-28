// FUN_0047fffc @ 0047fffc size=309 sig=undefined FUN_0047fffc() cc=unknown
// callers: FUN_00480150
// callees: FUN_0048d2e7,FUN_0049a93f,FUN_0047e074,FUN_00498aab,FUN_0049a9e7,FUN_0049aa95,FUN_00496c61,FUN_0049a8ed,FUN_0049a760,FUN_0048d32c

void FUN_0047fffc(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined1 auStack_24 [3];
  byte local_21;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  uVar6 = 0;
  switch(DAT_00559da0) {
  case 0:
    goto switchD_0048000f_caseD_0;
  case 1:
    uVar6 = 0x3f0;
    break;
  case 2:
    uVar6 = 0x3f1;
    break;
  case 3:
    uVar6 = 0x3f2;
    break;
  case 4:
    uVar6 = 0x3f3;
    break;
  case 5:
    uVar6 = 0x3f4;
  }
  iVar2 = FUN_0047e074();
  if (iVar2 != 0) {
    uVar3 = FUN_00498aab(iVar2,1);
    piVar4 = (int *)FUN_00496c61(uVar3,uVar6,0,0,0,0,0,auStack_24);
    if ((piVar4 != (int *)0x0) && ((local_21 & 0x40) == 0)) {
      FUN_0048d2e7(DAT_004d5c28);
      uVar5 = 8;
      if ((*(byte *)(*piVar4 + 8) & 3) != 0) {
        uVar5 = 0x10;
      }
      uVar6 = FUN_0049a760(*(int *)(DAT_0051bddc + 0xc) << 0x10 | uVar5);
      local_20 = DAT_004c5458;
      local_18 = DAT_004c5458 + DAT_004c5460;
      local_1c = DAT_004c545c;
      local_14 = DAT_004c545c + DAT_004c5464;
      FUN_0049a8ed();
      FUN_0049a9e7(&local_20);
      iVar1 = *piVar4;
      FUN_0049aa95(iVar1,0x27c - *(short *)(iVar1 + 4),0x13c - *(short *)(iVar1 + 2),
                   (int)*(short *)(iVar1 + 0xe),0);
      FUN_0049a93f();
      FUN_0049a760(uVar6);
      FUN_0048d32c();
    }
    FUN_00498aab(iVar2,0);
  }
switchD_0048000f_caseD_0:
  return;
}

