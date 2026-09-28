// FUN_00479de4 @ 00479de4 size=203 sig=undefined FUN_00479de4() cc=unknown
// callers: FUN_004782ec
// callees: sprintf,fclose,FUN_00427f04,fopen,FUN_00427e80
// strings: \"net_map.xfer\"|\"maps\\\\\"|\"Receiving Game Data\\r%d%% complete\"|\"Load MultiPlayer Game\"

void FUN_00479de4(int param_1)

{
  undefined1 local_54 [80];
  
  DAT_004d59a4 = DAT_004d59a4 | 0x4000;
  if (DAT_004dc310 != 0) {
    fclose(DAT_004dc310);
    DAT_004dc310 = 0;
  }
  sprintf(&DAT_005597d5,&DAT_004dc3a1,s_maps__004dc3a6,s_net_map_xfer_004dc3ac);
  DAT_004dc310 = fopen(&DAT_005597d5,&DAT_004dc38a);
  DAT_006535fc = 0;
  DAT_006535f8 = CONCAT22(*(undefined2 *)(param_1 + 0x1a),*(undefined2 *)(param_1 + 0x1c));
  DAT_006535f4 = 0;
  DAT_00653638 = 0;
  sprintf(local_54,PTR_s_Receiving_Game_Data__d___complet_00509c38,0);
  FUN_00427e80(0,PTR_s_Load_MultiPlayer_Game_00509c30,local_54,0,2);
  FUN_00427f04();
  return;
}

