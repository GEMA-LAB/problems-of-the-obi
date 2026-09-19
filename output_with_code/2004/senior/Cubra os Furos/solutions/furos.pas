{ OBI2004               }
{ Tarefa Cubra os Furos }
{ r. anido              }


program furos;

const
   MAX_FUROS = 10000;
type
   ponto = record
	      x, y : integer;
	   end;

function diametro(x1, y1, x2, y2 : integer): integer;
var
   d : real;
begin
   if x1 = x2 then d := abs(y1 - y2)
   else if y1 = y2 then d := abs(x1 - x2)
   else d := sqrt(abs((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
   diametro := round(0.5+2*(d+2.5)); { arredonda para cima, conforme enunciado }
   { nota: havia uma inconsistencia no enunciado, com os exemplos nao correspondendo
     ao texto da tarefa. Por essa razao, todas as formas de arredondamento foram
     consideradas corretas durante a correcao das solucoes dos competidores. }
end; { diametro }  

var
   n, i, j	 : integer;
   teste	 : integer;
   furos	 : array[1..MAX_FUROS] of ponto;
   diam_min, max : integer;
   x, y, diam	 : integer;
begin
   teste := 1;
   readln(n);
   while n > 0 do begin
      writeln('Teste ', teste);
      inc(teste);
      for i:=1 to n do with furos[i] do readln(x, y);
      diam_min := MAX_FUROS * MAX_FUROS;
      for i:=1 to n do begin
	 max := 0;
	 x := furos[i].x; y := furos[i].y;
	 for j:=1 to n do begin
	    if i <> j then begin
	       diam := diametro(x, y, furos[j].x, furos[j].y);
	       if diam > max then max := diam;
	    end;
	 end;
	 if max < diam_min then diam_min := max;
      end;
      writeln(diam_min);
      writeln;
      readln(n);
   end;
end.