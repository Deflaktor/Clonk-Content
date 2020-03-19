Initialize:
  SetAction("Fetzen");
  return(1);

Zeit:
  if (GreaterThan(GetActTime(),10)) RemoveObject();
  return(1);