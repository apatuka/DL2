// FUN_0049c244 @ 0049c244 size=207 sig=undefined FUN_0049c244() cc=unknown
// callers: FUN_004a2962,FUN_0049c3c9,FUN_0049b7f0
// callees: FUN_0049f7c9,FUN_0049bb73,FUN_0049ba80

void FUN_0049c244(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  FUN_0049bb73(param_1,param_2,4,&local_24);
  FUN_0049ba80(param_1,param_2,&local_14);
  iVar1 = *(int *)(param_2 + 0x4c);
  *(undefined4 *)(param_2 + 0x4c) = 0;
  if ((*(byte *)(param_2 + 0x24) & 0x40) == 0) {
    iVar4 = (local_18 - local_20) - (local_8 - local_10);
    if ((0 < iVar4) &&
       (uVar2 = *(int *)(param_2 + 0xec) - *(int *)(param_2 + 0xe8), uVar5 = (int)uVar2 >> 0x1f,
       iVar3 = (uVar2 ^ uVar5) - uVar5, iVar3 != 0)) {
      uVar2 = *(int *)(param_2 + 0x48) - *(int *)(param_2 + 0xe8);
      uVar5 = (int)uVar2 >> 0x1f;
      *(int *)(param_2 + 0x4c) = (int)(((uVar2 ^ uVar5) - uVar5) * iVar4) / iVar3;
    }
  }
  else {
    iVar4 = (local_1c - local_24) - (local_c - local_14);
    if ((0 < iVar4) &&
       (uVar2 = *(int *)(param_2 + 0xec) - *(int *)(param_2 + 0xe8), uVar5 = (int)uVar2 >> 0x1f,
       iVar3 = (uVar2 ^ uVar5) - uVar5, iVar3 != 0)) {
      uVar2 = *(int *)(param_2 + 0x48) - *(int *)(param_2 + 0xe8);
      uVar5 = (int)uVar2 >> 0x1f;
      *(int *)(param_2 + 0x4c) = (int)(((uVar2 ^ uVar5) - uVar5) * iVar4) / iVar3;
    }
  }
  if ((param_3 != 0) && (iVar1 != *(int *)(param_2 + 0x4c))) {
    FUN_0049f7c9(param_2);
  }
  return;
}

