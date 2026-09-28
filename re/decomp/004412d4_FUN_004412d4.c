// FUN_004412d4 @ 004412d4 size=118 sig=undefined FUN_004412d4() cc=unknown
// callers: FUN_00446c34,FUN_0040d64c,FUN_0040e384,FUN_004015ac,FUN_0040a37c,SetRetreat,FUN_004234d4,FUN_00404b68,FUN_0044339c,FUN_0040d808,FUN_00429a04,FUN_004474b0,FUN_004073e4,FUN_00486964,FUN_00407030,FUN_00428b74,FUN_0040f154,FUN_00406b1c,FUN_004418ac,FUN_004467e8,FUN_004089d4,FUN_0040d768,FindArtifact,FUN_0040f974,FUN_0040ec50,FUN_00442f68,FUN_00452594,FUN_0040df44,FUN_00403f5c,FUN_004013ec,FUN_00442c44,FUN_0040e9f4,FUN_0040e050,FUN_0040350c,FUN_004432fc,FUN_004568c8,FUN_00409544,FUN_004435b0,FUN_00451034,FUN_00453d9c,FUN_0046e064,FUN_00406dd8,FUN_00441adc,CheckDiscovery,FUN_0040e470,FUN_00457624,FUN_00484114,FUN_00486e34,FUN_00472578,FUN_00446440,FUN_0044f3f0,FUN_0045727c,FUN_00454928,FUN_004046e8
// callees: 

bool FUN_004412d4(int param_1,int param_2,uint param_3)

{
  bool bVar1;
  
  if (DAT_004d5af4 == 0) {
    bVar1 = false;
  }
  else if ((param_1 < 0) || (DAT_004d5aec <= param_1)) {
    bVar1 = false;
  }
  else if ((param_2 < 0) || (DAT_004d5aec <= param_2)) {
    bVar1 = false;
  }
  else if (((&DAT_0059f3da)[param_1 * 0xb6 + param_2] & 0x10) == 0) {
    bVar1 = param_3 == ((&DAT_0059f3da)[param_1 * 0xb6 + param_2] & param_3);
  }
  else {
    bVar1 = param_3 == (param_3 & 0x1e);
  }
  return bVar1;
}

