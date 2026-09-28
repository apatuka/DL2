// FUN_00456258 @ 00456258 size=435 sig=undefined FUN_00456258() cc=unknown
// callers: 
// callees: FUN_00456214,FUN_00450fa8,FUN_004526b0,FUN_00456150,FUN_00451b68

void FUN_00456258(int param_1,int param_2)

{
  undefined2 *puVar1;
  int iVar2;
  bool bVar3;
  int local_10;
  int local_c;
  
  bVar3 = *(char *)(param_1 + 0x21) != '\0';
  local_c = -1;
  for (puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_2 + 0x7a),0xffffffff);
      puVar1 != (undefined2 *)0x0;
      puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_2 + 0x7a),*puVar1)) {
    if (((param_1 == *(int *)(puVar1 + 0x20)) && (iVar2 = FUN_00450fa8(puVar1), iVar2 == 0)) &&
       ((bVar3 || ((&DAT_004faf8d)[*(char *)(puVar1 + 3) * 0x24] != '\x01')))) {
      local_c = (int)*(char *)(puVar1 + 4);
      break;
    }
  }
  local_10 = -1;
  puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),0xffffffff);
  do {
    if (puVar1 == (undefined2 *)0x0) {
LAB_00456331:
      if ((local_10 != -1) && (local_c != -1)) {
        FUN_00456150(param_1,local_c,local_10,0);
        for (puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_2 + 0x7a),0xffffffff);
            puVar1 != (undefined2 *)0x0;
            puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_2 + 0x7a),*puVar1)) {
          if (((param_1 == *(int *)(puVar1 + 0x20)) && (iVar2 = FUN_00450fa8(puVar1), iVar2 == 0))
             && ((bVar3 || ((&DAT_004faf8d)[*(char *)(puVar1 + 3) * 0x24] != '\x01')))) {
            FUN_00451b68(puVar1);
          }
        }
        for (puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),0xffffffff);
            puVar1 != (undefined2 *)0x0;
            puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),*puVar1)) {
          if (((param_2 == *(int *)(puVar1 + 0x20)) && (iVar2 = FUN_00450fa8(puVar1), iVar2 == 0))
             && ((bVar3 || ((&DAT_004faf8d)[*(char *)(puVar1 + 3) * 0x24] != '\x01')))) {
            FUN_00451b68(puVar1);
          }
        }
        FUN_004526b0();
      }
      return;
    }
    if (((param_2 == *(int *)(puVar1 + 0x20)) && (iVar2 = FUN_00450fa8(puVar1), iVar2 == 0)) &&
       ((bVar3 || ((&DAT_004faf8d)[*(char *)(puVar1 + 3) * 0x24] != '\x01')))) {
      local_10 = (int)*(char *)(puVar1 + 4);
      goto LAB_00456331;
    }
    puVar1 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),*puVar1);
  } while( true );
}

