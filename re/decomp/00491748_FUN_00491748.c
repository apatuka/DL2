// FUN_00491748 @ 00491748 size=158 sig=undefined FUN_00491748() cc=unknown
// callers: FUN_004997df
// callees: FUN_0048fade,FUN_00498aab,FUN_004917e6

undefined4 FUN_00491748(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (param_1 == 0) {
    uVar2 = 0;
  }
  else {
    puVar1 = (undefined4 *)FUN_00498aab(*(undefined4 *)(param_1 + 0xb8),1);
    if (param_2 == 0) {
      FUN_0048fade(*puVar1,puVar1[0x16],0);
      puVar1[1] = 0xffffffff;
    }
    else if (param_2 < puVar1[1] + 1) {
      FUN_0048fade(*puVar1,puVar1[0x16],0);
      puVar1[1] = 0xffffffff;
      while ((int)puVar1[1] < param_2 + -1) {
        FUN_004917e6(param_1);
      }
    }
    else if ((int)puVar1[1] < param_2 + -1) {
      while ((int)puVar1[1] < param_2 + -1) {
        FUN_004917e6(param_1);
      }
    }
    FUN_00498aab(*(undefined4 *)(param_1 + 0xb8),0);
    uVar2 = 1;
  }
  return uVar2;
}

