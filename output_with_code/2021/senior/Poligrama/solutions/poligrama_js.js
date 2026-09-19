// OBI2021 - Fase 2                                                                                                          
// poligrama                                                                                                                 

function ordenaString(str){
  var arr = str.split('');
  var ordenada = arr.sort();
  return ordenada.join('');
}

var n;
var s, a, b;
var ok;

scanf("%d", "n");
scanf("%s", "s");

for (var k = 1; k < n; ++k) {
   if (n % k === 0) {
      a = ordenaString(s.substring(0, k));
      ok = true;
      for (var i = k; i < n; i += k) {
         b = ordenaString(s.substring(i, i+k));
         if (a != b) {
            ok = false;
            break;
         }
      }
      if (ok) {
         printf("%s\n", s.substring(0, k));
         break;
      }
   }
}


if (!ok)
    printf("*\n");
