{ OBI2002            }
{ Tarefa Pedagio     }

program pedagio;

const
   MAXE	= 2500;
   MAXC	= 50;
var
   estrada    : array[1..MAXC, 1..MAXC] of boolean;
   visitada   : array[1..MAXC] of integer;
   fila	      : array[1..MAXC] of integer;
   f_ins, f_ret : integer;
   i, j, x, y : integer;
   c, e, l, p : integer;
   t	      : integer;
   teste      : integer;

procedure insere(v : integer);
begin
   inc(f_ins);
   fila[f_ins] := v;
end; { insere }

function retira: integer;
begin
   if f_ins = f_ret then {fila vazia}
      retira := 0
   else begin
      inc(f_ret);
      retira := fila[f_ret];
   end;
end; { retira }

   
begin
   teste := 1;
   readln(c, e, l, p);
   while c <> 0 do begin
      for i:= 1 to c do begin
	 visitada[i] := -1;
	 for j:= 1 to c do begin
	    estrada[i,j] := false;
	    estrada[j,i] := false;
	 end;
      end;

      for i:= 1 to e do begin
	 readln(x, y);
	 estrada[x, y] := true;
	 estrada[y, x] := true;
      end;

      f_ins := 0; f_ret := 0; {fila vazia}
      t := l;
      visitada[t] := 0;
      {t e' a cidade corrente}
      while (t > 0) do begin
	 if (visitada[t] < p) then begin
	    for i:= 1 to c do { verifica vizinhos de t }
	       if (visitada[i] = -1) and estrada[i,t] then begin
		  visitada[i] := visitada[t] + 1;
		  insere(i);
	       end;
	 end;
	 t := retira; {nova cidade corrente}
      end;

      { escreve resultado }
      writeln('Teste ', teste);
      inc(teste);
      visitada[l] := 0;
      for i := 1 to c do
	 if visitada[i] > 0 then write(i, ' ');
      writeln;
      readln(c, e, l, p);
   end;
end.
