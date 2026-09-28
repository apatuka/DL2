// FUN_00436978 @ 00436978 size=97 sig=undefined FUN_00436978() cc=unknown
// callers: FUN_00436db8,FUN_00437134
// callees: FUN_0049eb44

void FUN_00436978(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = (&DAT_005a43f6)[param_1 * 0xadc];
  if (cVar1 == -1) {
    uVar2 = 0xd;
  }
  else if (cVar1 == '\0') {
    uVar2 = 0xe;
  }
  else if (cVar1 == '\x01') {
    uVar2 = 0xf;
  }
  else {
    uVar2 = 0xe;
  }
  FUN_0049eb44(DAT_004c4664,uVar2,1,0xb,1,0);
  return;
}

