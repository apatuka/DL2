// FUN_0044134c @ 0044134c size=59 sig=undefined FUN_0044134c() cc=unknown
// callers: SeaManipulationFlagTerritories,FUN_0046f26c
// callees: 

bool FUN_0044134c(int param_1,int param_2)

{
  bool bVar1;
  
  if (DAT_004d5af4 == 0) {
    bVar1 = false;
  }
  else {
    bVar1 = (&DAT_0059f3da)[param_1 * 0xb6 + param_2] != 0;
  }
  return bVar1;
}

