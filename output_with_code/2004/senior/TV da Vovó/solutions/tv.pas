{ OBI2004            }
{ Tarefa TV da Vovo  }
{ r. anido           }


program tv;

const
   MAX = 1000;
var
   n, m, i, j	    : integer;
   teste	    : integer;
   x, y		    : integer;
   x_total, y_total : integer;
   imagem	    : array[0..MAX, 0..MAX] of integer;
begin
   teste := 1;
   { le dimensao da imagem }
   readln(n, m);
   while n > 0 do begin
      writeln('Teste ', teste);
      inc(teste);
      { le a imagem }
      for i := 0 to n-1 do
	 for j := 0 to m-1 do
	    read(imagem[i, j]);
      x_total := 0; y_total := 0;
      { le numero de deslocamentos }
      readln(y, x);
      { le e acumula os deslocamentos }
      while (x<>0) or (y<>0) do begin
	 x_total := x_total + x;
	 y_total := y_total - y;
	 readln(y, x);
      end;
      { normaliza deslocamentos }
      if x_total < 0 then x_total := n + x_total;
      if y_total < 0 then y_total := m + y_total;
      { aplica os comandos e imprime imagem resultante }
      for i := 0 to n-1 do begin
	 for j := 0 to m-1 do
	    write(imagem[(i + x_total) mod n, (j + y_total) mod m]:1, ' ');
	 writeln;
      end;
      writeln;
      { le dimensoes de nova imagem }
      readln(n, m);
   end;
end.
