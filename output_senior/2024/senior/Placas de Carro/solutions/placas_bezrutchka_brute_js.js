var plate;
scanf("%s", "plate");

function check_old(plate) {
  if (plate.length != 8) return false;
  for (var i = 0; i < 8; i++) {
    if (i < 3 && (plate.charAt(i) > 'Z' || plate.charAt(i) < 'A')) return false;
    if (i == 3 && plate.charAt(i) != '-') return false;
    if (i > 3 && (plate.charAt(i) > '9' || plate.charAt(i) < '0')) return false;
  }
  return true;
}

function check_new(plate) {
  if (plate.length != 7) return false;
  for (var i = 0; i < 7; i++) {
    if ((i < 3 || i == 4) && (plate.charAt(i) > 'Z' || plate.charAt(i) < 'A')) return false;
    if ((i > 3 && i != 4) && (plate.charAt(i) > '9' || plate.charAt(i) < '0')) return false;
  }
  return true;
}

if (check_old(plate)) {
  printf("1");
} else if (check_new(plate)) {
  printf("2");
} else {
  printf("0");
}
