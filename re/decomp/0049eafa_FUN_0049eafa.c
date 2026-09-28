// FUN_0049eafa @ 0049eafa size=38 sig=undefined FUN_0049eafa() cc=unknown
// callers: FUN_004a2c32,FUN_0041f024,FUN_004a03cf,FUN_0041ab54,FUN_00425bc4,FUN_004a016e,FUN_004a060f,FUN_0049d4ef,FUN_0049e47a,FUN_0049c710,FUN_0049d7f4,FUN_0049efae,FUN_0049fc69,FUN_004a26e8,FUN_00438dbc,FUN_004a08c5,FUN_0049da81,FUN_00438134,FUN_0049fe03
// callees: 

undefined4 FUN_0049eafa(int param_1)

{
  undefined4 uVar1;
  
  if ((*(byte *)(param_1 + 0x28) & 4) == 0) {
    if ((*(byte *)(param_1 + 0x28) & 0x10) == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 2;
  }
  return uVar1;
}

