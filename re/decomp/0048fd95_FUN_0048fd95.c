// FUN_0048fd95 @ 0048fd95 size=118 sig=undefined FUN_0048fd95() cc=unknown
// callers: 
// callees: FUN_0048fd54,fclose,fopen,fread

uint FUN_0048fd95(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_204 [512];
  
  *param_2 = 0;
  iVar1 = fopen(param_1,&DAT_0051daf4);
  if (iVar1 == 0) {
    *param_2 = 1;
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
    while( true ) {
      iVar3 = fread(local_204,1,0x200,iVar1);
      if (iVar3 == 0) break;
      uVar2 = FUN_0048fd54(iVar3,uVar2,local_204);
    }
    fclose(iVar1);
    uVar2 = uVar2 ^ 0xffffffff;
  }
  return uVar2;
}

