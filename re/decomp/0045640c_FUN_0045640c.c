// FUN_0045640c @ 0045640c size=252 sig=undefined FUN_0045640c() cc=unknown
// callers: FUN_00456508
// callees: FUN_00456214,FUN_00450fa8,FUN_004526b0,FUN_00456150,FUN_00451b68

undefined4 FUN_0045640c(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined2 *puVar1;
  int iVar2;
  bool bVar3;
  
  FUN_00456150(param_1,param_3,param_2,0);
  bVar3 = *(char *)(param_1 + 0x21) != '\0';
  for (puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),0xffffffff);
      puVar1 != (undefined2 *)0x0;
      puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),*puVar1)) {
    if ((((int)*(char *)(puVar1 + 4) == (int)*(short *)(DAT_0057cdf8 + 8)) &&
        (iVar2 = FUN_00450fa8(puVar1), iVar2 == 0)) &&
       ((bVar3 || ((&DAT_004faf8d)[*(char *)(puVar1 + 3) * 0x24] != '\x01')))) {
      FUN_00451b68(puVar1);
    }
  }
  for (puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),0xffffffff);
      puVar1 != (undefined2 *)0x0;
      puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),*puVar1)) {
    if ((((int)*(char *)(puVar1 + 4) == (int)*(short *)(DAT_0057cdf8 + 10)) &&
        (iVar2 = FUN_00450fa8(puVar1), iVar2 == 0)) &&
       ((bVar3 || ((&DAT_004faf8d)[*(char *)(puVar1 + 3) * 0x24] != '\x01')))) {
      FUN_00451b68(puVar1);
    }
  }
  FUN_004526b0();
  if (DAT_005649e0 != 0) {
    param_3 = param_2;
  }
  return param_3;
}

