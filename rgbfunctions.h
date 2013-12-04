// float hue, saturation, brightness;

typedef struct {
  char r;
  char g;
  char b;
} RGB;

RGB hsb2rgb(float hue, float saturation, float brightness){
  int r,g,b;
  float h2, f, p, q, t;
  RGB rgb;
  
  if (saturation == 0) {
    r = g = b = (int) (brightness * 255.0f + 0.5f);
  } 
  else {
    h2 = (hue - (int)hue) * 6.0f;
    f = h2 - (int)(h2);
    p = brightness * (1.0f - saturation);
    q = brightness * (1.0f - saturation * f);
    t = brightness * (1.0f - (saturation * (1.0f - f)));
    switch ((int) h2) {
    case 0:
      r = (int) (brightness * 255.0f + 0.5f);
      g = (int) (t * 255.0f + 0.5f);
      b = (int) (p * 255.0f + 0.5f);
      break;
    case 1:
      r = (int) (q * 255.0f + 0.5f);
      g = (int) (brightness * 255.0f + 0.5f);
      b = (int) (p * 255.0f + 0.5f);
      break;
    case 2:
      r = (int) (p * 255.0f + 0.5f);
      g = (int) (brightness * 255.0f + 0.5f);
      b = (int) (t * 255.0f + 0.5f);
      break;
    case 3:
      r = (int) (p * 255.0f + 0.5f);
      g = (int) (q * 255.0f + 0.5f);
      b = (int) (brightness * 255.0f + 0.5f);
      break;
    case 4:
      r = (int) (t * 255.0f + 0.5f);
      g = (int) (p * 255.0f + 0.5f);
      b = (int) (brightness * 255.0f + 0.5f);
      break;
    case 5:
      r = (int) (brightness * 255.0f + 0.5f);
      g = (int) (p * 255.0f + 0.5f);
      b = (int) (q * 255.0f + 0.5f);
      break;
    }
  };
  
  rgb.r = r;
  rgb.g = g;
  rgb.b = b;
  
  return(rgb); 
}


typedef struct {
  float h;
  float s;
  float b;
} HSB;

HSB rgb2hsb(int r, int g, int b) {
    HSB hsb;
    float hue, saturation, brightness;
    int cmax = (r > g) ? r : g;
    if (b > cmax) cmax = b;
    int cmin = (r < g) ? r : g;
    if (b < cmin) cmin = b;

    brightness = ((float) cmax) / 255.0f;
    if (cmax != 0)
        saturation = ((float) (cmax - cmin)) / ((float) cmax);
    else
        saturation = 0;
    if (saturation == 0)
        hue = 0;
    else {
        float redc = ((float) (cmax - r)) / ((float) (cmax - cmin));
        float greenc = ((float) (cmax - g)) / ((float) (cmax - cmin));
        float bluec = ((float) (cmax - b)) / ((float) (cmax - cmin));
        if (r == cmax)
            hue = bluec - greenc;
        else if (g == cmax)
            hue = 2.0f + redc - bluec;
        else
            hue = 4.0f + greenc - redc;
        hue = hue / 6.0f;
        if (hue < 0)
            hue = hue + 1.0f;
    }
    hsb.h = hue;
    hsb.s = saturation;
    hsb.b = brightness;
    return(hsb);
}
