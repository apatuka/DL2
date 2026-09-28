// FUN_0042b870 @ 0042b870 size=272 sig=undefined FUN_0042b870() cc=unknown
// callers: FUN_0042baf8
// callees: FUN_0042b3d0,FUN_0042b7a8,FUN_0049eb44

/* WARNING: Type propagation algorithm not settling */

void FUN_0042b870(void)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int *piVar8;
  int local_28;
  int local_24 [6];
  
  local_24[0] = (DAT_004d5b1a + -0x14) / 5;
  piVar4 = &local_28;
  iVar2 = (int)DAT_004d5b1c;
  local_28 = 3;
  if (local_24[0] < 3) {
    piVar4 = local_24;
  }
  FUN_0042b7a8(*piVar4,iVar2);
  switch(iVar2) {
  case 0:
    uVar1 = 0x1f;
    break;
  case 1:
    uVar1 = 0x20;
    break;
  case 2:
    uVar1 = 0x21;
    break;
  case 3:
    uVar1 = 0x22;
    break;
  case 4:
    uVar1 = 0x23;
    break;
  case 5:
    uVar1 = 0x24;
    break;
  default:
    uVar1 = 0x25;
  }
  FUN_0049eb44(DAT_004bda5c,uVar1,1,0xb,1,0);
  local_24[2] = (int)DAT_004d5b1a;
  local_24[1] = 1;
  FUN_0049eb44(DAT_004bda5c,0x27,1,0x29,0,local_24 + 1);
  iVar2 = 0;
  piVar4 = &DAT_00557bf8;
  pcVar3 = &DAT_004d5b1d;
  do {
    *piVar4 = (int)*pcVar3;
    piVar8 = local_24 + 1;
    local_24[2] = (int)*pcVar3;
    local_24[1] = 1;
    uVar7 = 0;
    uVar6 = 0x29;
    uVar5 = 1;
    uVar1 = FUN_0042b3d0(iVar2);
    FUN_0049eb44(DAT_004bda5c,uVar1,uVar5,uVar6,uVar7,piVar8);
    iVar2 = iVar2 + 1;
    piVar4 = piVar4 + 1;
    pcVar3 = pcVar3 + 1;
  } while (iVar2 < 6);
  return;
}

