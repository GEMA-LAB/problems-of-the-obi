{ OBI2002            }
{ Tarefa Lua         }
{ r. anido           }

program lua;

const
   MAXN =  10000;
var
   temps       : array[1..MAXN] of integer;
   m, n, i, j  : integer;
   max, min    : integer;
   media, soma : integer;
   teste       : integer;
begin
   teste := 1;
   readln(n, m);
   while n <> 0 do begin
      { le as temperaturas }
      for i:= 1 to n do
	 readln(temps[i]);
      { calcula a soma do primeiro intervalo }
      soma := 0;
      for i := 1 to m do
	 soma := soma + temps[i];
      { a primeira media neste momento e' o maximo e o minimo }
      max := soma div m; min := soma div m;

      { calcula soma de todos os outros intervalos, usando sempre
        o valor do intervalo anterior }
      for i := m+1 to n do begin
	 soma := soma - temps[i-m] + temps[i];
	 media := soma div m;
	 if media < min then min := media
	 else if media > max then max := media;
      end;
      writeln('Teste ', teste);
      writeln(min, ' ', max);
      writeln;
      inc(teste);
      readln(n, m);
   end;
end.
