//Script aus Blitz

#strict

/* Locals */

static lgt_enlightment; // Erhellung
static lgt_last_lgt_frame; // Letztes Frame, in dem die Helligkeit angepasst wurde

local fDoGamma;


/* Aktivierung */

public Activate: 
SetAction("Advance");
LightningEffect(60);
return(1);

adv:
LightningEffect(20);
ExecLgt();
return(1);


/* Effekte */

private func LightningEffect(strength)
  {
  lgt_enlightment+=Random(strength)+strength/2;
  return(1);
  }

private func ExecLgt()
  {
  //if (!fDoGamma) return(1);
  // Lichteffekt ausführen (Rampe 7)
  if (lgt_enlightment>0 && lgt_last_lgt_frame != FrameCounter())
    {
    var lgt=Min(lgt_enlightment*3, 255);
    SetGamma(RGB(lgt, lgt, lgt), RGB(128+lgt/2, 128+lgt/2, 128+lgt/2), 16777215, 5);
    lgt_enlightment=Max(lgt_enlightment*4/8-1); lgt_last_lgt_frame=FrameCounter();
    }
if(GetActTime()>10)
	Remove();
  }






/* Ende */

private Remove:
  if (ObjectCount(_FLS)<=1) ResetGamma(5);
  RemoveObject();
  return(1);