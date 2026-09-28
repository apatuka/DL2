// FUN_0049eaae @ 0049eaae size=76 sig=undefined FUN_0049eaae() cc=unknown
// callers: FUN_004a2307,FUN_004a228a
// callees: 

undefined4 FUN_0049eaae(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) & 0xffffffeb;
    uVar1 = 1;
  }
  else if (param_2 == 1) {
    *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) & 0xffffffeb | 0x10;
    uVar1 = 1;
  }
  else if (param_2 == 2) {
    *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) & 0xffffffeb | 4;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

