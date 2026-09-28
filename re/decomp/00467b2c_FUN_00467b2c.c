// FUN_00467b2c @ 00467b2c size=349 sig=undefined FUN_00467b2c() cc=unknown
// callers: 
// callees: FUN_00457ac0

void FUN_00467b2c(void)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  int *piVar4;
  undefined1 *puVar5;
  int aiStack_1c [6];
  
  if ((code *)PTR_FUN_004d02b8 != FUN_00457ac0) {
    aiStack_1c[0] = 2;
    piVar4 = aiStack_1c;
    aiStack_1c[0] = (*(code *)PTR_FUN_004d02b8)();
    if (DAT_004d512c < aiStack_1c[0]) {
      piVar4 = &DAT_004d512c;
    }
    DAT_004d512c = *piVar4;
    DAT_004d5b1a = (&DAT_004d5144)[DAT_004d512c * 2];
    iVar3 = 0;
    puVar5 = &DAT_004d5b1d;
    puVar2 = &DAT_004d514c + DAT_004d512c * 0xc;
    DAT_004d5b1b = DAT_004d5b1a;
    do {
      *puVar5 = *puVar2;
      iVar3 = iVar3 + 1;
      puVar5 = puVar5 + 1;
      puVar2 = puVar2 + 2;
    } while (iVar3 < 6);
    DAT_004d5b20._3_1_ = (char)DAT_004d512c * '\x02' + '\f';
    iVar3 = (*(code *)PTR_FUN_004d02b8)(1);
    aiStack_1c[0] = iVar3 + 1;
    if (DAT_004d5aec < iVar3 + 1) {
      piVar4 = &DAT_004d5aec;
    }
    else {
      piVar4 = aiStack_1c;
    }
    DAT_004d5aec = *piVar4;
    iVar3 = (*(code *)PTR_FUN_004d02b8)(4);
    aiStack_1c[0] = iVar3 + -1;
    if (DAT_004c4258 < iVar3 + -1) {
      piVar4 = &DAT_004c4258;
    }
    else {
      piVar4 = aiStack_1c;
    }
    DAT_004c4258 = *piVar4;
    DAT_004d5af0 = (&DAT_004c425c)[DAT_004c4258];
    iVar3 = (*(code *)PTR_FUN_004d02b8)(5);
    aiStack_1c[0] = iVar3 + -1;
    if (DAT_004d5b0c < iVar3 + -1) {
      piVar4 = &DAT_004d5b0c;
    }
    else {
      piVar4 = aiStack_1c;
    }
    DAT_004d5b0c = *piVar4;
    cVar1 = (*(code *)PTR_FUN_004d02b8)(7);
    aiStack_1c[0] = CONCAT31(aiStack_1c[0]._1_3_,cVar1 + -1);
    if (DAT_004d5b00 < (char)(cVar1 + -1)) {
      piVar4 = (int *)&DAT_004d5b00;
    }
    else {
      piVar4 = aiStack_1c;
    }
    DAT_004d5b00 = (char)*piVar4;
    DAT_004d5b08 = 0;
  }
  return;
}

