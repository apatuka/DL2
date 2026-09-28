// FUN_004a6b00 @ 004a6b00 size=69 sig=undefined FUN_004a6b00() cc=unknown
// callers: FUN_004904bf,FUN_00497956,FUN_004397a0,FUN_004978bf,FUN_00497859,FUN_00493522,FUN_0046fae4,FUN_00495aa4,FUN_00490bca,FUN_004934e0,FUN_004976dc,FUN_00438b9c
// callees: FUN_004addb4

int FUN_004a6b00(char *param_1,char *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  while( true ) {
    bVar1 = FUN_004addb4((int)*param_1);
    bVar3 = bVar1;
    bVar2 = FUN_004addb4((int)*param_2);
    if ((bVar3 != bVar2) || (bVar1 == 0)) break;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  }
  return (uint)bVar1 - (uint)bVar2;
}

