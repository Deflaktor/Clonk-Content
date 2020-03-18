#strict
#appendto EGLN

private func SetMatAccessTable()
  {
  // Schnellzugriffstabelle auf Materialien, die glitzern
  Local(Material("Moonstone")) = 1;
  }


private func Twinkle() {
  // Sind wir noch nicht vorbereitet?
  if(!initialized) return(Initialize2());

  // sparkle_amount mal nach Glitzermaterial suchen
  // Gibt ggf. Zugriff auf Local(-1), was aber einfach 0 zurückgibt
  var x,y,c,m,obj;
  for(var i = 0; i < sparkle_amount; i++)
    if (Local(GetMaterial(x = Random(LandscapeWidth()), y = Random(LandscapeHeight()))))
      {
        Sparkle(x,y, c=128+Random(128),c,255, 1);
      }
  
  // mehrmals nach einem möglichen Glitzerobjekt suchen
  if (!Random(15)) while (obj = FindObject(0, 0,0,0,0, OCF_Collectible(), 0,0, NoContainer(), obj))
    if (!Random(10)) if (!Random(11-placement_factor))
      if(GetID(obj) == BCOR)
        if (Stuck(obj))
          if (!GetXDir(obj) && !GetYDir(obj))
            // So, alle Tests sind überstanden, jetzt wird geglänzt.
            Sparkle(GetX(obj)-3+Random(7),GetY(obj)-3+Random(7), 255,255,255);
}