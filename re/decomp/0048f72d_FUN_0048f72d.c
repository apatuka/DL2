// FUN_0048f72d @ 0048f72d size=41 sig=undefined FUN_0048f72d() cc=unknown
// callers: FUN_0049b604
// callees: 

undefined4 FUN_0048f72d(undefined1 *param_1,int param_2)

{
  undefined1 uVar1;
  undefined4 in_EAX;
  undefined1 *puVar2;
  
  puVar2 = param_1 + param_2;
  for (param_2 = param_2 >> 1; param_2 != 0; param_2 = param_2 + -1) {
    puVar2 = puVar2 + -1;
    uVar1 = *puVar2;
    *puVar2 = *param_1;
    *param_1 = uVar1;
    param_1 = param_1 + 1;
  }
  return in_EAX;
}

