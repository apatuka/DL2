// FUN_0040401c @ 0040401c size=43 sig=undefined FUN_0040401c() cc=unknown
// callers: FUN_00407e78
// callees: FUN_00403fd8

int FUN_0040401c(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00521bb4;
  do {
    iVar1 = FUN_00403fd8(*puVar2,param_1);
    if (iVar1 != 0) {
      return iVar1;
    }
    puVar2 = (undefined4 *)puVar2[1];
  } while (puVar2 != &DAT_00521bb4);
  return 0;
}

