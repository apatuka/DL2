// memset @ 004a6838 size=138 sig=undefined memset() cc=unknown
// callers: FUN_004512a8,FUN_0040d338,FUN_00471b20,FUN_00411534,FUN_00479164,FUN_0044ca34,FUN_004765e8,FUN_0044d890,FUN_004422bc,FUN_00465ac8,FUN_004ac974,FUN_0048cf7f,FUN_004483d0,FUN_004669d8,WriteUnitData,RegisterWindowClasses,FUN_0046c7d4,RaceInit_dc94,FUN_0046a844,FUN_00468da0,FUN_00444ae4,FUN_0046ab18,FUN_004526b0,FUN_0040ba64,FUN_00486964,FUN_0046bdfc,FUN_004842e4,FUN_004ae974,FUN_004018d8,FUN_00402fe8,FUN_004af624,FUN_00461078,FUN_004418ec,FUN_0045ca3c,FUN_0040315c,FUN_0040d1a4,FUN_0040f700,FUN_00408f58,FUN_00484368,FUN_004606f4,FUN_004238c8,FUN_004522c6,FUN_00462d70,FUN_004ae670,FUN_00451034,FUN_004658a8,FUN_00466128,FUN_00401830,FUN_0047b8b4,FUN_00456e44,FUN_004107ec,FUN_0045727c,FUN_004571d4,FUN_004100e0,FUN_0047d460,FUN_0040cdfc,FUN_004233e0,FUN_0047b660,FUN_00479b6c,FUN_00408b58,ResetVariables,FUN_00452250,FUN_004b1fb4,FUN_00441128,CalculateGameCRC,FUN_00461328,FUN_00456150,FUN_004aa9c4,RaceInit,FUN_00474718,FUN_004b0248,FUN_004b343c,FUN_00479324,FUN_004b3698,FUN_004ab648,FUN_00442184,FUN_0044df94,FUN_00408288,FUN_00486910,FUN_00447a68,FUN_00471bec,FUN_0041161c,FUN_0046e730,FUN_00407d60,LoadCombatSprites,FUN_0044569c,SendTerritoryData,FUN_0046ac44,CYGame_InitDirectDraw,FUN_0040cffc,FUN_00405798,FUN_00463aec,FUN_00410558,FUN_00462100,FUN_0047549c,FUN_004419c8,DeleteArmy,FUN_00450b20,FUN_0047b7bc,FUN_0046578c,FUN_00466218,FUN_00472448,FUN_00464cbc,FUN_00401eb8,FUN_00471c1c,FUN_00431734,FUN_00479700,FUN_004a7df4,FUN_004012dc,FUN_0047b98c,FUN_004050ac,FUN_00489c98,FUN_004a6b48,FUN_004618e8,FUN_00486e34,FUN_00461f74,FUN_0044f3f0,FUN_004568c8,FUN_0040beb4,FUN_00441fa4,FUN_0047c730,ProduceUnits,FUN_0044cc40,FUN_0047cb04,FUN_0045f664,FUN_0040233c,FUN_004423b4,FUN_00451de4,FUN_0044f110,FUN_00460a74,FUN_004101d4,FUN_0048bf93,FUN_004835bc,FUN_004426f8,FUN_00405378,FUN_00460330,FUN_00451410,FUN_00459068,FUN_0040be04,FUN_00444e88,FUN_00485668,FUN_0047e394
// callees: 

/* RTL */

undefined4 * memset(undefined4 *param_1,undefined1 param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined2 uVar3;
  byte bVar4;
  undefined4 *puVar5;
  
  uVar3 = CONCAT11(param_2,param_2);
  if ((param_3 & 0xfffffffc) == 0) {
    if ((param_3 & 3) != 0) {
      *(undefined1 *)param_1 = param_2;
      bVar4 = (char)(param_3 & 3) - 1;
      if (bVar4 != 0) {
        *(undefined2 *)((int)param_1 + (bVar4 - 1)) = uVar3;
      }
    }
    return param_1;
  }
  *(undefined2 *)param_1 = uVar3;
  puVar1 = (undefined4 *)((int)param_1 + (param_3 - 4));
  *(undefined2 *)((int)param_1 + 2) = uVar3;
  uVar2 = *param_1;
  param_3 = param_3 >> 3;
  puVar5 = param_1;
  if (param_3 == 0) {
    *puVar1 = uVar2;
    return param_1;
  }
  do {
    *puVar5 = uVar2;
    puVar5[1] = uVar2;
    if (param_3 == 1) break;
    puVar5[2] = uVar2;
    puVar5[3] = uVar2;
    if (param_3 == 2) break;
    puVar5[4] = uVar2;
    puVar5[5] = uVar2;
    if (param_3 == 3) break;
    puVar5[6] = uVar2;
    puVar5[7] = uVar2;
    if (param_3 == 4) break;
    puVar5[8] = uVar2;
    puVar5[9] = uVar2;
    if (param_3 == 5) break;
    puVar5[10] = uVar2;
    puVar5[0xb] = uVar2;
    puVar5 = puVar5 + 0xc;
    param_3 = param_3 - 6;
  } while (param_3 != 0);
  *puVar1 = uVar2;
  puVar1[-1] = uVar2;
  return param_1;
}

