/*-- Neues Script --*/

#strict
#appendto CNKT

protected func CreateConstructionSite(idType)
{
  // Nur wenn der Clonk steht und sich im Freien befindet
  if (GetAction(Contained()) ne "Walk") return(0);
  if (Contained(Contained())) return(0);
  // Pruefen, ob das Gebaeude hier gebaut werden kann
  if (idType->~RejectConstruction(0, 10, Contained()) ) return(0);
  // Besitzer setzen für CreateConstruction
  SetOwner(GetOwner(Contained()));
  // Baustelle erschaffen
  var check = 1;
  if(idType->~NoConstructionCheck())
    check = 0;
  var pSite;
  if (!(pSite = CreateConstruction(idType, 0, 10, GetOwner(Contained()), 1, 1,check))) return(0);
  pSite->~InitializeConstruction();
  // Meldung
  Message("Konstruktion: %s", Contained(), GetName(pSite));
  // Bausatz verbrauchen
  RemoveObject();
  return(1);
}