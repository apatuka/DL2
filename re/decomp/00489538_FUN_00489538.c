// FUN_00489538 @ 00489538 size=58 sig=undefined FUN_00489538() cc=unknown
// callers: 
// callees: _SmackClose@4,FUN_00488a09,FUN_00495811

void FUN_00489538(int param_1)

{
  undefined4 *puVar1;
  
  if ((param_1 != 0) && (puVar1 = *(undefined4 **)(param_1 + 0x1c), puVar1 != (undefined4 *)0x0)) {
    FUN_00495811(param_1);
    _SmackClose_4(*puVar1);
    if (puVar1[3] != 0) {
      FUN_00488a09(puVar1[3]);
    }
  }
  (**(code **)(param_1 + 0x58))(param_1,0);
  return;
}

