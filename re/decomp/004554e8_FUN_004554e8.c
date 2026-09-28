// FUN_004554e8 @ 004554e8 size=71 sig=undefined FUN_004554e8() cc=unknown
// callers: FUN_004556b0
// callees: 

void FUN_004554e8(int param_1,int param_2,int param_3)

{
  byte bVar1;
  
  bVar1 = 0;
  if (*(int *)(param_1 + 0x20) < param_2) {
    bVar1 = 2;
  }
  else if (param_2 < *(int *)(param_1 + 0x20)) {
    bVar1 = 8;
  }
  if (*(int *)(param_1 + 0x24) < param_3) {
    bVar1 = bVar1 | 4;
  }
  else if (param_3 < *(int *)(param_1 + 0x24)) {
    bVar1 = bVar1 | 1;
  }
  if (bVar1 != 0) {
    *(byte *)(param_1 + 0x30) = bVar1;
  }
  return;
}

