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
  if(Local(0)>=2)
  if(LessThan(ObjectCount(ATOM),1))
  EarthMaterials(ATOM);

  if(LessThan(ObjectCount(CHS2),1*Local(0)))
  EarthMaterials(CHS2);

  if(LessThan(ObjectCount(KREI),1*Local(0)))
  EarthMaterials(KREI);

  if(LessThan(ObjectCount(_MFF),1*Local(0)))
  EarthMaterials(_MFF);

  if(LessThan(ObjectCount(MARI),1*Local(0)))
  EarthMaterials(MARI);

  if(LessThan(ObjectCount(MSHF),1*Local(0)))
  EarthMaterials(MSHF);

  if(Local(0)>=2)
  if(LessThan(ObjectCount(P57M),1))
  EarthMaterials(P57M);

  if(LessThan(ObjectCount(SHF2),1*Local(0)))
  EarthMaterials(SHF2);

  if(LessThan(ObjectCount(SHF3),1*Local(0)))
  EarthMaterials(SHF3);

  if(Local(0)>=3)
  if(LessThan(ObjectCount(SLGR),1))
  EarthMaterials(SLGR);

return(1);

EarthMaterials:
if(Equal(GetMaterial(SetVar(0,Random(LandscapeWidth())),SetVar(1,Random(LandscapeHeight()))),Material("Earth")))
{
SetVar(0,CreateObject(CTOT,Var(0),Var(1)+20,-1));
ObjectCall(Var(0),"Init",Par(0));
return(1);
}
return(0);
