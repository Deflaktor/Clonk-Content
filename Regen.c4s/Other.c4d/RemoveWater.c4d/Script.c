/* Wasser Entfernen Zauber */

#strict

public func Activate(pCaster)
  {
  // Effekt erstellen
  AddEffect("WaterRemoveUSpell", pCaster, 150, 5, 0, GetID(), GetDuration());
  // Grafikeffekt
  CastParticles("MSpark", 5, 50, 0,0, 100, 200, RGBa(100,100,255,128), RGBa(0,0,255,0));
  CreateParticle("MSpark", 0,0, 1000, RGBa(50,50,255,150));
  // Zauber entfernen
  RemoveObject();
  return(1); 
  }

public func GetSpellClass(object pMage) { return(WATR); }
public func GetSpellCombo(pMage) { return ("25"); } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
public func GetResearchBase () { return (MFFS); }
public func GetDuration () { return (33*30); }

protected func FxWaterRemoveUSpellStart (object pTarget, int iNumber, int iTemp, int iDuration)
{
  if(iTemp) return();
  EffectVar(0,pTarget,iNumber)=iDuration;
  Sound("Energize");
}


  
protected func FxWaterRemoveUSpellTimer(object pTarget, int iEffectNumber, int iEffectTime)
{
  var iTime = EffectVar(0, pTarget, iEffectNumber) -= 5;
  
  // Das Kraftfeld langsam ausfaden
  var iAlpha = 70 * Min(GetDuration(), GetDuration()-iTime) / GetDuration();
  if(iAlpha>50)
    iAlpha=50;

  var color = RGBa(215 + Cos(iTime, 40),
						215 + Cos(iTime, 40),
						215 + Sin(iTime, 40),
						Sqrt(Sqrt(iAlpha**5)) );
  
  var iX, iY;
  // for(var i=90+45+180; i<=270-45+180; i+=12)
  for(var i=0; i<360; i+=12)
    {
      var iAng=i + RandomX(-5,5);
      iX=Sin(iAng, 15);
      iY=Cos(iAng, 15);
      CreateParticle("PSpark", GetX(pTarget)+iX, GetY(pTarget)+iY, -iX/7+RandomX(-3,3), -iY/7+RandomX(-3,3), 25+Random(15), color, pTarget);
	 // CreateParticle("PSpark", GetX(pTarget)+iX, GetY(pTarget)+iY, -iX/5+RandomX(-1,1), -iY/5+RandomX(-1,1), 25+Random(15), color, pTarget);
    }
	
  for(var i=0;i<300;++i) {
    if(ExtractLiquid(GetX(pTarget),GetDefBottom(pTarget)-2)==-1) {
      break;
    }
  }
  
  // Nach Ablauf der Zeit wird der Effekt gelöscht
  if (iTime <= 0) return(-1);
 
}

protected func FxWaterRemoveUSpellStop(object pTarget, int iEffectNumber, int iReason, bool fTemp)
{
  // Keine temporären Aufrufe
  if (fTemp) return();
  
  Sound("DeEnergize");
  RemoveObject();
}

protected func FxWaterRemoveUSpellEffect(string szNewEffectName)
{
  // gleichen Effekt zusammenfassen
  if(szNewEffectName eq "WaterRemoveUSpell") return(-2);
}

protected func FxWaterRemoveUSpellAdd(object pTarget, int iNumber, string szNewEffectName, int iNewEffectTimer, int iDuration) {
  // Effekt übernehmen
  Sound("Energize");
  EffectVar(0,pTarget,iNumber) += iDuration;
}    
