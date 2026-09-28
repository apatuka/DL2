// FUN_004851ec @ 004851ec size=120 sig=undefined FUN_004851ec() cc=unknown
// callers: FUN_00485668,FUN_004526b0
// callees: FUN_0046c9d8,FUN_00423690,FUN_00447a40
// strings: \"Give Experience\"

void FUN_004851ec(int param_1)

{
  short sVar1;
  int iVar2;
  
  if (*(short *)(param_1 + 0x28) < 500) {
    sVar1 = FUN_0046c9d8(0x14,s_Give_Experience_005123dc);
    *(short *)(param_1 + 0x28) = *(short *)(param_1 + 0x28) + sVar1 + 10;
    iVar2 = FUN_00447a40((int)*(short *)(param_1 + 0x28));
    if (iVar2 != *(short *)(param_1 + 0x2a)) {
      *(short *)(param_1 + 0x2a) = (short)iVar2;
      if (iVar2 != 0) {
        if (iVar2 == 1) {
          FUN_00423690((int)*(char *)(param_1 + 8),4,param_1 + 0xb,0,0,0);
        }
        else if (iVar2 == 2) {
          FUN_00423690((int)*(char *)(param_1 + 8),5,param_1 + 0xb,0,0,0);
        }
      }
    }
  }
  return;
}

