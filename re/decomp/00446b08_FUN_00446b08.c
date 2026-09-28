// FUN_00446b08 @ 00446b08 size=51 sig=undefined FUN_00446b08() cc=unknown
// callers: FUN_00446b94,FUN_004726cc,FUN_00472844,FUN_00446b3c
// callees: 

void FUN_00446b08(undefined2 param_1,int param_2)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = &DAT_005a43d0;
  for (iVar2 = 0; iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
    *(undefined2 *)(puVar1 + param_2 * 2 + 0xa70) = param_1;
    puVar1 = puVar1 + 0xadc;
  }
  return;
}

