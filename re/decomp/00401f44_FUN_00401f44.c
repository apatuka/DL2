// FUN_00401f44 @ 00401f44 size=119 sig=undefined FUN_00401f44() cc=unknown
// callers: 
// callees: FUN_0044de9c

void FUN_00401f44(int param_1,int param_2,int param_3)

{
  short *psVar1;
  int iVar2;
  short *psVar3;
  undefined1 local_38 [4];
  short local_34 [24];
  
  FUN_0044de9c(&DAT_0059f160 + param_1 * 0x2d8,param_3,1,local_38);
  iVar2 = 0;
  psVar3 = (short *)(param_2 + 0x2a);
  psVar1 = local_34;
  do {
    *psVar3 = *psVar3 + *psVar1;
    iVar2 = iVar2 + 1;
    psVar3 = psVar3 + 1;
    psVar1 = psVar1 + 2;
  } while (iVar2 < 0xb);
  if (*(short *)(param_2 + 0x44) == *(short *)(param_2 + 0x40)) {
    *(short *)(param_2 + 0x40) =
         *(short *)(param_2 + 0x40) + (short)(char)(&DAT_004f9dc8)[param_3 * 0x32];
  }
  return;
}

