// placa.js

function check_old(plate) {
  if (plate.length != 8) return false;
  for (var i = 0; i < 8; i++) {
    if (i < 3 && (plate[i] > 'Z' || plate[i] < 'A')) return false;
    if (i == 3 && plate[i] != '-') return false;
    if (i > 3 && (plate[i] > '9' || plate[i] < '0')) return false;
  }
  return true;
}

function check_new(plate) {
  if (plate.length != 7) return false;
  for (var i = 0; i < 7; i++) {
    if ((i < 3 || i == 4) && (plate[i] > 'Z' || plate[i] < 'A')) return false;
    if ((i > 3 && i != 4) && (plate[i] > '9' || plate[i] < '0')) return false;
  }
  return true;
}

var plate;
scanf("%s", "plate");
if (check_old(plate)) printf("1\n");
else if (check_new(plate)) printf("2\n");
else printf("0\n");
