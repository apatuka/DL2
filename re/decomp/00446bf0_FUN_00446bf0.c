// FUN_00446bf0 @ 00446bf0 size=68 sig=undefined FUN_00446bf0() cc=unknown
// callers: FUN_00456508,FUN_004568c8,ConsumeFood,FUN_00451b68,FUN_00485264,FUN_00485364,FUN_00446c34,FUN_0040e348,FUN_004471c0,FUN_00457624,FUN_004474b0,FUN_0040f060,FUN_004526b0,FUN_004566c4,FUN_00446e30,FUN_0045723c,SetRetreat,FUN_0046e6b8
// callees: 

undefined4 FUN_00446bf0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = *(char *)(param_1 + 0x25);
  if ((((((cVar1 == '\x01') || (cVar1 == '\x02')) || (cVar1 == '\x03')) ||
       ((cVar1 == '\x05' || (cVar1 == '\x06')))) ||
      ((cVar1 == '\x0f' || ((cVar1 == '\x10' || (cVar1 == '\x13')))))) || (cVar1 == '\x04')) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

