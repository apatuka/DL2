// FUN_0040e1fc @ 0040e1fc size=135 sig=undefined FUN_0040e1fc() cc=unknown
// callers: FUN_00403dbc,FUN_00401ac0,FUN_0040e284,FUN_0040bbf4,FUN_0040f2a4,FUN_00401a18
// callees: FUN_00447190,FUN_00446b94

bool FUN_0040e1fc(int param_1,int param_2)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = DAT_004c5140;
  iVar5 = (int)(char)(&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24];
  DAT_004c5140 = param_1;
  if (iVar5 == 1) {
    iVar5 = 5;
  }
  iVar3 = 0x2000 << (*(byte *)(param_1 + 8) & 0x1f);
  iVar4 = (int)*(char *)(param_1 + 8);
  cVar2 = FUN_00447190(param_1);
  FUN_00446b94(*(undefined4 *)(param_1 + 0x38),param_2,(int)cVar2,iVar5,iVar4,iVar3);
  DAT_004c5140 = uVar1;
  cVar2 = FUN_00447190(param_1);
  return (int)*(short *)(param_2 + 0xa70 + *(char *)(param_1 + 8) * 2) <= (int)cVar2;
}

