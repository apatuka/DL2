// FUN_00401fbc @ 00401fbc size=84 sig=undefined FUN_00401fbc() cc=unknown
// callers: 
// callees: FUN_0044ddf4

void FUN_00401fbc(int param_1,int param_2,undefined4 param_3)

{
  short *psVar1;
  int iVar2;
  short *psVar3;
  undefined1 local_38 [4];
  short local_34 [24];
  
  FUN_0044ddf4(&DAT_0059f160 + param_1 * 0x2d8,param_3,local_38);
  iVar2 = 0;
  psVar3 = (short *)(param_2 + 0x2a);
  psVar1 = local_34;
  do {
    *psVar3 = *psVar3 + *psVar1;
    iVar2 = iVar2 + 1;
    psVar3 = psVar3 + 1;
    psVar1 = psVar1 + 2;
  } while (iVar2 < 0xb);
  return;
}

