// FUN_0048fe0b @ 0048fe0b size=107 sig=undefined FUN_0048fe0b() cc=unknown
// callers: 
// callees: FUN_0048fd54,FUN_00488a09,FUN_00488ba3,FUN_004888ec

uint FUN_0048fe0b(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_204 [512];
  
  *param_2 = 0;
  iVar1 = FUN_004888ec(param_1,0);
  if (iVar1 == -1) {
    *param_2 = 1;
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
    while( true ) {
      iVar3 = FUN_00488ba3(iVar1,local_204,0x200);
      if (iVar3 == 0) break;
      uVar2 = FUN_0048fd54(iVar3,uVar2,local_204);
    }
    FUN_00488a09(iVar1);
    uVar2 = uVar2 ^ 0xffffffff;
  }
  return uVar2;
}

