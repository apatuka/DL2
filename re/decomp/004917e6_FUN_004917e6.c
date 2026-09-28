// FUN_004917e6 @ 004917e6 size=120 sig=undefined FUN_004917e6() cc=unknown
// callers: FUN_004997df,FUN_00491748,FUN_0049185e
// callees: FUN_0048fade,FUN_0048f992,FUN_00491200,FUN_00498aab,FUN_0048fa92

undefined4 FUN_004917e6(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int local_14 [4];
  
  if (param_1 == 0) {
    uVar3 = 0;
  }
  else {
    puVar1 = (undefined4 *)FUN_00498aab(*(undefined4 *)(param_1 + 0xb8),1);
    if (puVar1[1] + 1 < (int)*(short *)((int)puVar1 + 0xe)) {
      iVar2 = FUN_0048fa92(*puVar1);
      FUN_0048f992(*puVar1,local_14,0x10);
      FUN_00491200(puVar1,param_1,local_14);
      FUN_0048fade(*puVar1,iVar2 + local_14[0],0);
    }
    FUN_00498aab(*(undefined4 *)(param_1 + 0xb8),0);
    uVar3 = 1;
  }
  return uVar3;
}

