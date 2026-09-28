// FUN_00402514 @ 00402514 size=51 sig=undefined FUN_00402514() cc=unknown
// callers: 
// callees: 

undefined4 FUN_00402514(int param_1)

{
  undefined2 *puVar1;
  
  puVar1 = &DAT_0055dc60;
  while( true ) {
    if ((undefined2 *)0x55eb9f < puVar1) {
      return 0;
    }
    if ((param_1 == (short)puVar1[2]) && (puVar1[10] != 0)) break;
    puVar1 = puVar1 + 0x3d;
  }
  return 1;
}

