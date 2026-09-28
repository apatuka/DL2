// FUN_00423fdc @ 00423fdc size=897 sig=undefined FUN_00423fdc() cc=unknown
// callers: FUN_004244d4
// callees: FUN_00482f34,FUN_00482f64,FUN_0049eb44

void FUN_00423fdc(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14;
  int local_10;
  
  DAT_00557500 = DAT_004d5ab4;
  DAT_00557504 = DAT_004d5ad4;
  DAT_00557508 = DAT_004d5ad0;
  DAT_0055750c = DAT_004d5ae0;
  DAT_00557510 = DAT_004d5ac8;
  if (DAT_004d5ab0 == 0) {
    DAT_00557514 = DAT_004b7c50;
  }
  else {
    iVar1 = FUN_00482f64();
    if (iVar1 < -3000) {
      iVar1 = -3000;
    }
    DAT_00557514 = (iVar1 * 100 + 300000) / 3000;
  }
  if (DAT_004d5aac == 0) {
    DAT_00557518 = DAT_004b7c54;
  }
  else {
    iVar1 = FUN_00482f34();
    if (iVar1 < -3000) {
      iVar1 = -3000;
    }
    DAT_00557518 = (iVar1 * 100 + 300000) / 3000;
  }
  DAT_0055751c = DAT_004d5ab0;
  DAT_00557520 = DAT_004d5aac;
  DAT_00557524 = DAT_004d5aa8;
  DAT_00557528 = DAT_004d5ac4;
  if (DAT_00557500 == 1) {
    uVar2 = 4;
  }
  else if (DAT_00557500 == 2) {
    uVar2 = 5;
  }
  else {
    uVar2 = 6;
  }
  FUN_0049eb44(DAT_004b7c3c,uVar2,1,0xb,1,0);
  if (DAT_00557504 == 0) {
    uVar2 = 7;
  }
  else if (DAT_00557504 == 1) {
    uVar2 = 8;
  }
  else {
    uVar2 = 9;
  }
  FUN_0049eb44(DAT_004b7c3c,uVar2,1,0xb,1,0);
  if (DAT_004d5ad0 == 0) {
    FUN_0049eb44(DAT_004b7c3c,0xb,1,0xb,1,0);
  }
  else {
    FUN_0049eb44(DAT_004b7c3c,0xc,1,0xb,1,0);
  }
  if (DAT_0055750c == 0) {
    uVar2 = 0x1d;
  }
  else if (DAT_0055750c == 1) {
    uVar2 = 0x1c;
  }
  else {
    uVar2 = 0x1b;
  }
  FUN_0049eb44(DAT_004b7c3c,uVar2,1,0xb,1,0);
  if (DAT_004d5ac8 == 0) {
    FUN_0049eb44(DAT_004b7c3c,0x17,1,0xb,1,0);
  }
  else {
    FUN_0049eb44(DAT_004b7c3c,0x16,1,0xb,1,0);
  }
  local_10 = DAT_00557514;
  local_14 = 1;
  FUN_0049eb44(DAT_004b7c3c,0x13,1,0x29,0,&local_14);
  if (DAT_0055751c == 0) {
    FUN_0049eb44(DAT_004b7c3c,0x13,1,10,1,0);
  }
  local_10 = DAT_00557518;
  local_14 = 1;
  FUN_0049eb44(DAT_004b7c3c,0x14,1,0x29,0,&local_14);
  if (DAT_00557520 == 0) {
    FUN_0049eb44(DAT_004b7c3c,0x14,1,10,1,0);
  }
  if (DAT_0055751c == 0) {
    FUN_0049eb44(DAT_004b7c3c,0xe,1,0xb,0,0);
  }
  else {
    FUN_0049eb44(DAT_004b7c3c,0xe,1,0xb,1,0);
  }
  if (DAT_00557520 == 0) {
    FUN_0049eb44(DAT_004b7c3c,0xf,1,0xb,0,0);
  }
  else {
    FUN_0049eb44(DAT_004b7c3c,0xf,1,0xb,1,0);
  }
  if (DAT_00557524 == 0) {
    FUN_0049eb44(DAT_004b7c3c,0x10,1,0xb,0,0);
  }
  else {
    FUN_0049eb44(DAT_004b7c3c,0x10,1,0xb,1,0);
  }
  if (DAT_00557528 == 0) {
    FUN_0049eb44(DAT_004b7c3c,0x11,1,0xb,0,0);
  }
  else {
    FUN_0049eb44(DAT_004b7c3c,0x11,1,0xb,1,0);
  }
  return;
}

