// FUN_00484bf0 @ 00484bf0 size=58 sig=undefined FUN_00484bf0() cc=unknown
// callers: FUN_00484da8,UnitList__Insert
// callees: 

undefined4 * FUN_00484bf0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = 0;
  *(undefined1 *)param_1 = (undefined1)param_2;
  puVar1 = (undefined4 *)&stack0x0000000c;
  *(undefined2 *)((int)param_1 + 2) = param_2._2_2_;
  puVar3 = param_1;
  do {
    puVar3 = puVar3 + 1;
    *puVar3 = *puVar1;
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar2 < 0xb);
  param_1[0xc] = 0;
  return param_1;
}

