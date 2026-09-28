// FUN_0046c9d8 @ 0046c9d8 size=30 sig=undefined FUN_0046c9d8() cc=unknown
// callers: SelRace,FindArtifact,FUN_0047d49c,SelectInit,RaceInit_dc94,FUN_0047d288,FUN_00485364,FUN_00485668,FUN_0044f3f0,FUN_0047cdd8,FUN_0047d1e0,FUN_0046686c,FUN_004851ec,SpyCaught,FindTresure,FUN_0047cb74,FUN_0046c49c,FUN_0046681c,FindConstructionSite,FUN_004667ac,ChCht,FUN_0048514c,SeaManipulationEffects,FUN_0047d35c,SearchForSubs,FUN_0047d068,FUN_00466508,FUN_0047ce94,AnyKnown,CheckDiscovery,SeaManipulationFlagTerritories,FUN_0047cf9c,DoRiot,CreateRandomEvents,NoBonus
// callees: FUN_004ae5d8

int FUN_0046c9d8(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_004ae5d8();
    iVar1 = iVar1 % param_1;
  }
  return iVar1;
}

