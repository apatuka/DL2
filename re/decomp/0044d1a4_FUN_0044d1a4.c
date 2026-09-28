// FUN_0044d1a4 @ 0044d1a4 size=62 sig=undefined FUN_0044d1a4() cc=unknown
// callers: FUN_00485668,FUN_00445f08,FindConstructionSite,FUN_00480be0,FUN_0040d228,_MovePopulation,FUN_0040d080,FUN_004526b0,FUN_0040e440,FUN_0045b094,FUN_0045a0bc,FUN_00410720,DrawSTileBuilding,FUN_0041acf8,FUN_0046b074,FUN_0046dc5c,FUN_004096a8,CheckDiscovery,FUN_0045c704,FUN_00486964,FUN_004436cc,FUN_00402df4,FUN_0044081c,FUN_0045b448,FUN_0040dd80,FUN_00407e78,_DeleteBuilding,FUN_00480d78,FUN_0045eadc,FUN_00409e2c,FUN_00403e30,FUN_00409474,FUN_00483d58,FUN_00409c5c,FUN_00409d9c,FUN_0044d600,FUN_00472578,FUN_0047dfdc,FUN_00409400,FUN_004013ec
// callees: 

int FUN_0044d1a4(int param_1,int param_2,int param_3)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 0x154 + param_3 * 0x34);
  while( true ) {
    if (0x23 < param_3) {
      return -1;
    }
    if ((*piVar1 != 0) && (param_2 == *(char *)(*piVar1 + 5))) break;
    param_3 = param_3 + 1;
    piVar1 = piVar1 + 0xd;
  }
  return param_3;
}

