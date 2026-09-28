// FUN_004a68c4 @ 004a68c4 size=24 sig=undefined FUN_004a68c4() cc=unknown
// callers: FUN_004af8f4
// callees: 

undefined2 * FUN_004a68c4(undefined2 *param_1,undefined2 param_2,int param_3)

{
  undefined2 *puVar1;
  
  puVar1 = param_1;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    *puVar1 = param_2;
    puVar1 = puVar1 + 1;
  }
  return param_1;
}

