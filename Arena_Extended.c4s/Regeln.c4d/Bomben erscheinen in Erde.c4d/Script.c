#strict

protected Initialize:
  SetAction("Initialize");
  // Position
  SetPosition();
  return(1);

Initialized:
  // Plazierungsfaktor ermitteln
  Local(0)=ObjectCount(GetID())+1;
  // Andere Objekte des gleichen Typs entfernen
  while(Var(1)=FindObject(GetID()))
    RemoveObject(Var(1));
  // Steuerungsaktion
  SetAction("Active");
  return(1);

DoFlints:
  /* Flint Respawn ... thx to flgr */
  // nur wenn zu wenige da sind

  if(LessThan(ObjectCount(MARI,0,0,0,0,0,0,0,NoContainer()),3*Local(0)/4))
  EarthMaterials(MARI);

  if(LessThan(ObjectCount(WBOB,0,0,0,0,0,0,0,NoContainer()),2*Local(0)))
  EarthMaterials(WBOB);

  if(LessThan(ObjectCount(BALL,0,0,0,0,0,0,0,NoContainer()),1*Local(0)))
  EarthMaterials(BALL);

  if(LessThan(ObjectCount(MBOM,0,0,0,0,0,0,0,NoContainer()),2*Local(0)))
  EarthMaterials(MBOM);

  if(LessThan(ObjectCount(FLNT,0,0,0,0,0,0,0,NoContainer()),3*Local(0)))
  EarthMaterials(FLNT);

  if(LessThan(ObjectCount(FF4V,0,0,0,0,0,0,0,NoContainer()),2*Local(0)))
  EarthMaterials(FF4V);

  if(LessThan(ObjectCount(_AUS,0,0,0,0,0,0,0,NoContainer()),1*Local(0)))
  EarthMaterials(_AUS);

  if(LessThan(ObjectCount(JU58,0,0,0,0,0,0,0,NoContainer()),1*Local(0)))
  EarthMaterials(JU58);

  if(LessThan(ObjectCount(JU59,0,0,0,0,0,0,0,NoContainer()),1))
  EarthMaterials(JU59);

  if(LessThan(ObjectCount(SBOM,0,0,0,0,0,0,0,NoContainer()),1*Local(0)))
  EarthMaterials(SBOM);

  if(LessThan(ObjectCount(KAC5,0,0,0,0,0,0,0,NoContainer()),1*Local(0)/2))
  EarthMaterials(KAC5);

  if(LessThan(ObjectCount(HNTF,0,0,0,0,0,0,0,NoContainer()),1*Local(0)))
  EarthMaterials(HNTF);

  if(LessThan(ObjectCount(SHFT,0,0,0,0,0,0,0,NoContainer()),2*Local(0)))
  EarthMaterials(SHFT);

  if(LessThan(ObjectCount(SFLN,0,0,0,0,0,0,0,NoContainer()),2*Local(0)))
  EarthMaterials(SFLN);

  if(LessThan(ObjectCount(_SFN,0,0,0,0,0,0,0,NoContainer()),1*Local(0)))
  EarthMaterials(_SFN);

  if(LessThan(ObjectCount(FL58,0,0,0,0,0,0,0,NoContainer()),2*Local(0)/3))
  EarthMaterials(FL58);

  if(LessThan(ObjectCount(J102,0,0,0,0,0,0,0,NoContainer()),1*Local(0)/2))
  EarthMaterials(J102);

  if(LessThan(ObjectCount(TFLN,0,0,0,0,0,0,0,NoContainer()),2*Local(0)))
  EarthMaterials(TFLN);

  if(LessThan(ObjectCount(EFLN,0,0,0,0,0,0,0,NoContainer()),1*Local(0)))
  EarthMaterials(EFLN);

  if(LessThan(ObjectCount(_CGP,0,0,0,0,0,0,0,NoContainer()),1*Local(0)))
  EarthMaterials(_CGP);

  if(LessThan(ObjectCount(_RND,0,0,0,0,0,0,0,NoContainer()),2*Local(0)))
  EarthMaterials(_RND);
  
  if(LessThan(ObjectCount(MELO,0,0,0,0,0,0,0,NoContainer()),1*Local(0)))
  EarthMaterials(MELO);

  if(LessThan(ObjectCount(FBLU,0,0,0,0,0,0,0,NoContainer()),1*Local(0)/2))
  EarthMaterials(FBLU);
  
  return(1);

Zufallsflint:
  return(CreateContents(GameCall("Zufallsflint")));

EarthMaterials:
//for(var i=0;i<=10;i++) 
  if(Equal(GetMaterial(SetVar(0,Random(LandscapeWidth())),SetVar(1,Random(LandscapeHeight()))),Material("Earth"))) {
    SetVar(0,CreateObject(CTOT,Var(0),Var(1)+20,-1));
    ObjectCall(Var(0),"Init",Par(0));
    return(1);
  }
return(0);