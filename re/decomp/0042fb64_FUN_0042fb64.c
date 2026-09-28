// FUN_0042fb64 @ 0042fb64 size=1874 sig=undefined FUN_0042fb64() cc=unknown
// callers: FUN_00430348
// callees: FUN_0049eb44,FUN_0042f950,FUN_0042f82c,FUN_0042f784,FUN_0042f890,FUN_0042f8c0,sprintf,FUN_0042f920,FUN_0042f7d8,FUN_0042f8f0,FUN_00457ac0

void FUN_0042fb64(void)

{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  int *piVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  char acStack_a4 [4];
  int iStack_a0;
  int iStack_9c;
  int aiStack_98 [37];
  
  DAT_00558ca8 = DAT_004d5b2c;
  DAT_00558cac = DAT_004d5b34;
  DAT_00558cb4 = DAT_004d5b38;
  DAT_00558cb8 = DAT_004d5b30;
  if (DAT_004d5a50 != 0) {
    if ((code *)PTR_FUN_004d02b8 == FUN_00457ac0) {
      DAT_004d5b08 = 1;
    }
    DAT_004d5b34 = 0;
    DAT_004d5b2c = 1;
    DAT_004d5b30 = 300;
  }
  iVar3 = 0;
  piVar6 = &DAT_004c425c;
  do {
    iVar1 = iVar3;
    if (*piVar6 == DAT_004d5af0) break;
    iVar3 = iVar3 + 1;
    piVar6 = piVar6 + 1;
    iVar1 = DAT_004c4258;
  } while (iVar3 < 5);
  DAT_004c4258 = iVar1;
  DAT_004d5af0 = (&DAT_004c425c)[DAT_004c4258];
  iVar3 = 0;
  DAT_00558c8c = DAT_004d5af8;
  piVar6 = &DAT_004c4274;
  DAT_00558c90 = DAT_004d5afc;
  do {
    if (*piVar6 == DAT_004d5af8) {
      DAT_004c428c = iVar3;
    }
    iVar3 = iVar3 + 1;
    piVar6 = piVar6 + 1;
  } while (iVar3 < 3);
  iVar3 = 0;
  piVar6 = &DAT_004c4280;
  do {
    if (*piVar6 == DAT_004d5afc) {
      DAT_004c4290 = iVar3;
    }
    iVar3 = iVar3 + 1;
    piVar6 = piVar6 + 1;
  } while (iVar3 < 3);
  DAT_00558c94 = DAT_004d5af0;
  if (DAT_004d5a50 == 0) {
    aiStack_98[0] = 0;
    iStack_9c = 1;
    iStack_a0 = 10;
    DAT_004d5b34 = 0;
    acStack_a4[0] = '\x01';
    acStack_a4[1] = '\0';
    acStack_a4[2] = '\0';
    acStack_a4[3] = '\0';
    FUN_0049eb44(DAT_004c4294,0x20);
    aiStack_98[0] = 0;
    iStack_9c = 1;
    iStack_a0 = 10;
    acStack_a4[0] = '\x01';
    acStack_a4[1] = '\0';
    acStack_a4[2] = '\0';
    acStack_a4[3] = '\0';
    FUN_0049eb44(DAT_004c4294,0x21);
  }
  DAT_00558c88 = DAT_004d5aec;
  aiStack_98[0] = 1;
  iStack_9c = 0x42fcb8;
  piVar6 = aiStack_98;
  aiStack_98[0] = (*(code *)PTR_FUN_004d02b8)();
  if (DAT_004d5aec < aiStack_98[0]) {
    piVar6 = &DAT_004d5aec;
  }
  DAT_004d5aec = *piVar6;
  iStack_9c = 1;
  iStack_a0 = 0x42fce0;
  uVar4 = (*(code *)PTR_FUN_004d02b8)();
  switch(uVar4) {
  case 1:
    iStack_a0 = 0;
    acStack_a4[0] = '\x01';
    acStack_a4[1] = '\0';
    acStack_a4[2] = '\0';
    acStack_a4[3] = '\0';
    FUN_0049eb44(DAT_004c4294,3,1,10);
  case 2:
    iStack_a0 = 0;
    acStack_a4[0] = '\x01';
    acStack_a4[1] = '\0';
    acStack_a4[2] = '\0';
    acStack_a4[3] = '\0';
    FUN_0049eb44(DAT_004c4294,4,1,10);
  case 3:
    iStack_a0 = 0;
    acStack_a4[0] = '\x01';
    acStack_a4[1] = '\0';
    acStack_a4[2] = '\0';
    acStack_a4[3] = '\0';
    FUN_0049eb44(DAT_004c4294,5,1,10);
  case 4:
    iStack_a0 = 0;
    acStack_a4[0] = '\x01';
    acStack_a4[1] = '\0';
    acStack_a4[2] = '\0';
    acStack_a4[3] = '\0';
    FUN_0049eb44(DAT_004c4294,6,1,10);
  case 5:
    iStack_a0 = 0;
    acStack_a4[0] = '\x01';
    acStack_a4[1] = '\0';
    acStack_a4[2] = '\0';
    acStack_a4[3] = '\0';
    FUN_0049eb44(DAT_004c4294,7,1,10);
  case 6:
    iStack_a0 = 0;
    acStack_a4[0] = '\x01';
    acStack_a4[1] = '\0';
    acStack_a4[2] = '\0';
    acStack_a4[3] = '\0';
    FUN_0049eb44(DAT_004c4294,8,1,10);
  }
  iStack_a0 = 4;
  acStack_a4[0] = -0x6a;
  acStack_a4[1] = -3;
  acStack_a4[2] = 'B';
  acStack_a4[3] = '\0';
  iVar3 = (*(code *)PTR_FUN_004d02b8)();
  iStack_9c = iVar3 + -1;
  if (DAT_004c4258 < iVar3 + -1) {
    piVar6 = &DAT_004c4258;
  }
  else {
    piVar6 = &iStack_9c;
  }
  DAT_004c4258 = *piVar6;
  acStack_a4[0] = '\x04';
  acStack_a4[1] = '\0';
  acStack_a4[2] = '\0';
  acStack_a4[3] = '\0';
  iVar3 = (*(code *)PTR_FUN_004d02b8)();
  if (iVar3 == 1) {
    FUN_0049eb44(DAT_004c4294,0x13,1,10,1,0);
LAB_0042fde9:
    FUN_0049eb44(DAT_004c4294,0x14,1,10,1,0);
LAB_0042fdfe:
    FUN_0049eb44(DAT_004c4294,0x15,1,10,1,0);
  }
  else {
    if (iVar3 == 2) goto LAB_0042fde9;
    if (iVar3 == 3) goto LAB_0042fdfe;
    if (iVar3 != 4) goto LAB_0042fe2a;
  }
  FUN_0049eb44(DAT_004c4294,0x16,1,10,1,0);
LAB_0042fe2a:
  iVar3 = (*(code *)PTR_FUN_004d02b8)(5);
  iStack_a0 = iVar3 + -1;
  if (DAT_004d5b0c < iVar3 + -1) {
    piVar6 = &DAT_004d5b0c;
  }
  else {
    piVar6 = &iStack_a0;
  }
  DAT_004d5b0c = *piVar6;
  DAT_00558c98 = DAT_004d5b0c;
  uVar4 = (*(code *)PTR_FUN_004d02b8)(5);
  switch(uVar4) {
  case 0:
    FUN_0049eb44(DAT_004c4294,0x17,1,10,1,0);
  case 1:
    FUN_0049eb44(DAT_004c4294,0x18,1,10,1,0);
  case 2:
    FUN_0049eb44(DAT_004c4294,0x19,1,10,1,0);
  case 3:
    FUN_0049eb44(DAT_004c4294,0x1a,1,10,1,0);
  case 4:
    FUN_0049eb44(DAT_004c4294,0x1b,1,10,1,0);
  default:
    uVar10 = 0;
    uVar9 = 1;
    uVar8 = 0xb;
    uVar7 = 1;
    uVar4 = FUN_0042f784(DAT_004c4258);
    FUN_0049eb44(DAT_004c4294,uVar4,uVar7,uVar8,uVar9,uVar10);
    uVar10 = 0;
    uVar9 = 1;
    uVar8 = 0xb;
    uVar7 = 1;
    uVar4 = FUN_0042f7d8(DAT_004d5b0c);
    FUN_0049eb44(DAT_004c4294,uVar4,uVar7,uVar8,uVar9,uVar10);
    uVar10 = 0;
    uVar9 = 1;
    uVar8 = 0xb;
    uVar7 = 1;
    uVar4 = FUN_0042f82c(DAT_004d5aec + -1);
    FUN_0049eb44(DAT_004c4294,uVar4,uVar7,uVar8,uVar9,uVar10);
    uVar10 = 0;
    uVar9 = 1;
    uVar8 = 0xb;
    uVar7 = 1;
    uVar4 = FUN_0042f890(DAT_004c428c);
    FUN_0049eb44(DAT_004c4294,uVar4,uVar7,uVar8,uVar9,uVar10);
    uVar10 = 0;
    uVar9 = 1;
    uVar8 = 0xb;
    uVar7 = 1;
    uVar4 = FUN_0042f8c0(DAT_004c4290);
    FUN_0049eb44(DAT_004c4294,uVar4,uVar7,uVar8,uVar9,uVar10);
    DAT_00558c84 = DAT_004d5b00;
    FUN_0042f950();
    FUN_0049eb44(DAT_004c4294,0x1d,1,0xb,DAT_004d5af4 != 0,0);
    DAT_00558c9c = DAT_004d5b04;
    FUN_0049eb44(DAT_004c4294,0x1c,1,0xb,DAT_004d5b04 != 0,0);
    FUN_0049eb44(DAT_004c4294,0x22,1,0xb,DAT_004d5b2c != 0,0);
    FUN_0049eb44(DAT_004c4294,0x20,1,0xb,DAT_004d5b34 != 0,0);
    DAT_00558c7c = DAT_004d5b00;
    cVar2 = (*(code *)PTR_FUN_004d02b8)(7);
    acStack_a4[0] = cVar2 + -1;
    if (DAT_004d5b00 < (char)(cVar2 + -1)) {
      pcVar5 = &DAT_004d5b00;
    }
    else {
      pcVar5 = acStack_a4;
    }
    DAT_004d5b00 = *pcVar5;
    uVar10 = 0;
    uVar9 = 1;
    uVar8 = 0xb;
    uVar7 = 1;
    uVar4 = FUN_0042f8f0((int)DAT_004d5b00);
    FUN_0049eb44(DAT_004c4294,uVar4,uVar7,uVar8,uVar9,uVar10);
    sprintf(&iStack_a0,&DAT_004c42a8,DAT_004d5b30);
    FUN_0049eb44(DAT_004c4294,0x27,1,0xf,0,&iStack_a0);
    FUN_0049eb44(DAT_004c4294,0x27,1,0x1c,4,0);
    sprintf(&iStack_a0,&DAT_004c42a8,DAT_004d5b38);
    FUN_0049eb44(DAT_004c4294,0x25,1,0xf,0,&iStack_a0);
    FUN_0049eb44(DAT_004c4294,0x25,1,0x1c,4,0);
    uVar10 = 0;
    uVar9 = 1;
    uVar8 = 0xb;
    uVar7 = 1;
    DAT_00558cb0 = DAT_004d5b3c;
    uVar4 = FUN_0042f920(DAT_004d5b3c);
    FUN_0049eb44(DAT_004c4294,uVar4,uVar7,uVar8,uVar9,uVar10);
    DAT_00558ca4 = DAT_004d5b08;
    if ((code *)PTR_FUN_004d02b8 == FUN_00457ac0) {
      FUN_0049eb44(DAT_004c4294,0x1e,1,0xb,DAT_004d5b08 != 0,0);
    }
    else {
      DAT_004d5b08 = 0;
      FUN_0049eb44(DAT_004c4294,0x1e,1,0xb,0,0);
      FUN_0049eb44(DAT_004c4294,0x1e,1,10,1,0);
    }
    DAT_00558c80 = DAT_004d5a90;
    if ((code *)PTR_FUN_004d02b8 == FUN_00457ac0) {
      FUN_0049eb44(DAT_004c4294,0x1f,1,0xb,DAT_004d5a90 != 0,0);
    }
    else {
      DAT_004d5a90 = 0;
      FUN_0049eb44(DAT_004c4294,0x1f,1,0xb,0,0);
      FUN_0049eb44(DAT_004c4294,0x1f,1,10,1,0);
    }
    if (DAT_004d5aa0 == '\0') {
      FUN_0049eb44(DAT_004c4294,0x34,1,0x3c,0,1);
    }
    else {
      FUN_0049eb44(DAT_004c4294,3,1,0x3c,0,1);
      FUN_0049eb44(DAT_004c4294,4,1,0x3c,0,1);
      FUN_0049eb44(DAT_004c4294,5,1,0x3c,0,1);
      FUN_0049eb44(DAT_004c4294,6,1,0x3c,0,1);
      FUN_0049eb44(DAT_004c4294,7,1,0x3c,0,1);
      FUN_0049eb44(DAT_004c4294,8,1,0x3c,0,1);
      FUN_0049eb44(DAT_004c4294,0x34,1,0x3c,1,1);
    }
    return;
  }
}

