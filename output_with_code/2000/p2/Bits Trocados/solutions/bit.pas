program bits;

var
   teste, Valor, Resto : Integer;
   I, J, K, L	       : Integer;
begin
   teste:=1;
   Readln(Valor);
   while(Valor<>0) do begin
      I:=Valor div 50;  Resto:=Valor mod 50;
      J:=Resto div 10;  Resto:=Resto mod 10;
      K:=Resto div 5;   L    :=Resto mod 5;

      Writeln('Teste ', teste);
      Writeln(I, ' ', J, ' ', K, ' ', L);
      Writeln;
      Inc(teste);
      Readln(Valor);
   end;
end.
