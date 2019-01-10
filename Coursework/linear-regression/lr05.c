#include <stdio.h>
#include <math.h>

/******************************************************************************
 * This program takes an initial estimate of m and c and finds the associated 
 * rms error. It is then used as a base to generate and evaluate 8 new 
 * estimates, which are steps in different directions in m-c space. The best 
 * estimate is then used as the base for another iteration of "generate and 
 * evaluate". This continues until none of the new estimates are better than 
 * the base. This is a gradient search for a minimum in mc-space.
 * 
 * To compile:
 *   cc -o lr05 lr05.c -lm
 * 
 * To run:
 *   ./lr05
 * 
 * Dr Kevan Buckley, University of Wolverhampton, 2018
 *****************************************************************************/

typedef struct point_t {
  double x;
  double y;
} point_t;

int n_data = 1000;
point_t data[];

double residual_error(double x, double y, double m, double c) {
  double e = (m * x) + c - y;
  return e * e;
}

double rms_error(double m, double c) {
  int i;
  double mean;
  double error_sum = 0;
  
  for(i=0; i<n_data; i++) {
    error_sum += residual_error(data[i].x, data[i].y, m, c);  
  }
  
  mean = error_sum / n_data;
  
  return sqrt(mean);
}

int main() {
  int i;
  double bm = 1.3;
  double bc = 10;
  double be;
  double dm[8];
  double dc[8];
  double e[8];
  double step = 0.01;
  double best_error = 999999999;
  int best_error_i;
  int minimum_found = 0;
  
  double om[] = {0,1,1, 1, 0,-1,-1,-1};
  double oc[] = {1,1,0,-1,-1,-1, 0, 1};

  be = rms_error(bm, bc);

  while(!minimum_found) {
    for(i=0;i<8;i++) {
      dm[i] = bm + (om[i] * step);
      dc[i] = bc + (oc[i] * step);    
    }
      
    for(i=0;i<8;i++) {
      e[i] = rms_error(dm[i], dc[i]);
      if(e[i] < best_error) {
        best_error = e[i];
        best_error_i = i;
      }
    }

    printf("best m,c is %lf,%lf with error %lf in direction %d\n", 
      dm[best_error_i], dc[best_error_i], best_error, best_error_i);
    if(best_error < be) {
      be = best_error;
      bm = dm[best_error_i];
      bc = dc[best_error_i];
    } else {
      minimum_found = 1;
    }
  }
  printf("minimum m,c is %lf,%lf with error %lf\n", bm, bc, be);

  return 0;
}

point_t data[] = {
  {75.63,110.64},{66.70,108.01},{75.67,131.10},{69.53,97.56},{86.65,128.96},
  {65.22,110.33},{78.91,136.82},{66.65,104.39},{85.11,129.67},{67.34,121.75},
  {75.64,114.67},{76.59,134.26},{69.32,118.67},{89.85,142.19},{74.57,129.08},
  {51.85,84.40},{88.88,131.83},{41.87,89.99},{42.08,81.12},{20.81,66.34},{73.00,
  124.87},{56.51,95.52},{36.77,74.92},{16.58,47.20},{58.23,86.52},{99.81,
  161.23},{28.22,74.01},{23.09,54.61},{55.65,100.72},{17.43,45.10},{97.54,
  138.89},{59.51,90.13},{1.35,30.15},{30.12,55.88},{17.03,48.10},{63.13,102.69},
  {88.34,144.80},{65.46,105.62},{13.87,35.29},{82.31,116.16},{86.29,126.13},
  {69.35,138.43},{39.74,76.66},{83.34,124.69},{68.54,95.68},{41.19,90.51},{3.87,
  35.32},{65.91,121.91},{24.28,55.58},{29.81,76.45},{57.17,100.63},{25.97,
  64.67},{63.89,106.48},{26.98,64.82},{46.19,80.43},{85.62,120.10},{10.81,
  36.48},{99.17,152.61},{5.73,33.28},{46.93,63.95},{79.03,141.27},{88.09,
  143.52},{82.23,113.08},{61.31,89.25},{20.29,54.38},{44.64,94.98},{3.48,49.71},
  {22.09,41.74},{76.57,126.43},{36.09,70.71},{63.45,107.03},{71.52,118.07},
  {15.83,53.42},{45.81,88.39},{98.25,135.41},{3.23,43.36},{53.18,88.21},{43.90,
  93.00},{42.84,79.97},{57.04,109.30},{6.42,46.32},{99.39,148.86},{23.88,55.05},
  {44.87,91.76},{43.43,93.24},{80.31,132.36},{29.49,62.74},{51.13,87.08},{62.58,
  102.23},{11.77,43.51},{0.42,39.80},{77.00,114.98},{31.69,85.44},{60.80,98.35},
  {17.56,48.16},{29.78,61.26},{20.32,40.40},{27.35,68.00},{21.87,44.46},{1.47,
  21.10},{95.81,139.30},{11.19,42.55},{17.22,49.10},{81.32,126.54},{62.14,
  101.72},{74.23,128.08},{40.53,101.86},{34.03,73.98},{5.28,30.25},{84.26,
  131.97},{87.99,105.49},{42.85,66.55},{27.88,68.73},{1.22,34.96},{73.23,
  117.47},{83.13,117.00},{89.91,145.13},{99.42,165.25},{94.33,129.28},{52.64,
  91.11},{47.70,82.61},{86.66,126.90},{35.19,75.90},{76.98,138.48},{54.51,
  87.84},{82.30,120.78},{54.64,95.09},{33.15,78.47},{22.21,61.29},{21.21,33.13},
  {74.73,125.39},{45.34,76.41},{68.12,111.40},{3.08,18.74},{95.83,147.77},
  {75.21,118.51},{38.32,91.61},{35.85,55.40},{89.48,112.01},{37.65,72.55},
  {34.15,81.16},{13.85,60.34},{33.55,86.46},{38.94,77.21},{29.14,69.57},{32.91,
  80.18},{82.18,122.76},{75.98,130.64},{57.18,113.74},{60.84,96.78},{52.42,
  82.51},{13.30,46.46},{7.43,24.34},{68.66,106.23},{99.48,159.58},{78.70,
  121.19},{54.78,101.43},{85.26,156.39},{20.27,46.89},{6.65,50.54},{12.12,
  39.30},{63.38,94.20},{0.91,30.18},{91.82,128.83},{47.94,82.32},{38.42,89.40},
  {45.07,86.25},{84.30,134.54},{26.03,73.15},{39.46,83.64},{82.95,120.63},
  {59.43,102.81},{30.10,43.52},{28.82,76.98},{85.81,129.05},{61.88,104.90},
  {65.40,119.09},{74.31,109.83},{44.13,79.23},{28.04,75.87},{28.84,50.73},
  {81.67,132.05},{18.92,42.15},{13.74,46.96},{49.00,102.47},{37.14,66.79},
  {10.60,42.78},{85.13,133.90},{80.80,116.15},{73.93,117.47},{53.88,94.77},
  {94.24,138.44},{91.95,145.02},{92.48,130.68},{13.30,42.21},{11.26,54.52},
  {89.95,134.62},{97.49,133.93},{86.45,132.36},{39.65,77.37},{7.09,47.59},
  {19.72,53.96},{54.87,95.32},{71.74,113.07},{94.80,129.43},{57.82,100.53},
  {97.14,143.03},{97.41,151.88},{99.48,137.76},{48.59,83.33},{84.30,139.41},
  {59.17,104.53},{89.27,126.28},{6.26,31.64},{35.26,78.03},{9.58,47.71},{5.46,
  25.49},{14.74,45.89},{41.23,75.63},{68.70,127.16},{50.93,101.54},{83.79,
  123.86},{18.97,50.51},{39.31,92.00},{8.78,47.38},{76.43,113.72},{27.93,83.67},
  {86.19,134.23},{7.65,23.73},{23.58,45.07},{36.64,77.32},{77.36,121.68},{79.25,
  118.15},{39.29,77.91},{61.81,95.43},{43.93,66.58},{7.66,35.21},{90.32,133.03},
  {47.02,86.60},{10.63,53.25},{58.47,101.38},{67.86,117.60},{52.37,82.08},
  {34.48,63.92},{75.42,121.13},{33.63,59.03},{69.63,121.63},{87.45,132.28},
  {53.02,91.88},{30.79,61.50},{45.25,74.94},{73.07,105.63},{29.26,76.84},{26.85,
  62.85},{60.94,87.03},{82.60,133.86},{16.58,35.19},{76.94,106.88},{28.25,
  30.25},{85.94,124.45},{76.90,111.28},{69.98,126.56},{80.70,124.12},{16.63,
  80.46},{10.07,42.17},{61.38,107.93},{89.27,150.00},{2.77,47.25},{99.20,
  146.54},{25.84,56.14},{68.26,107.96},{81.23,137.38},{29.28,68.72},{39.27,
  82.28},{99.78,172.86},{23.46,52.90},{52.53,86.27},{85.25,140.75},{35.25,
  61.97},{18.25,37.44},{92.79,146.39},{92.41,145.85},{33.93,57.27},{55.83,
  101.90},{57.45,85.87},{81.46,128.54},{80.14,131.62},{63.74,106.21},{54.68,
  113.75},{92.11,149.47},{93.65,127.41},{90.46,131.35},{5.57,27.30},{36.52,
  77.15},{5.02,33.43},{36.94,58.47},{5.72,46.83},{65.58,109.21},{41.73,76.80},
  {99.98,139.36},{69.65,109.14},{66.90,98.26},{20.09,67.41},{46.04,83.67},
  {21.47,62.29},{58.88,93.04},{99.77,148.30},{33.10,71.64},{18.70,61.35},{50.95,
  96.27},{67.02,98.65},{71.52,113.67},{76.21,128.03},{97.05,144.69},{41.30,
  56.35},{19.00,37.80},{8.53,52.07},{51.48,76.72},{30.81,58.84},{74.89,133.82},
  {11.21,45.27},{35.01,73.07},{0.14,22.71},{58.84,91.65},{27.14,65.94},{5.64,
  38.23},{30.36,62.51},{12.98,56.01},{87.42,145.65},{37.09,75.38},{26.16,74.99},
  {87.36,135.77},{37.69,77.54},{39.14,64.36},{59.02,94.01},{65.93,114.99},
  {40.96,81.09},{36.39,77.86},{90.89,135.24},{20.38,47.89},{88.31,148.39},
  {64.73,110.65},{0.78,38.17},{52.74,101.04},{18.96,41.49},{31.46,82.71},{16.87,
  54.62},{7.52,35.40},{1.34,42.87},{39.38,86.15},{78.16,133.07},{87.68,137.80},
  {74.88,113.52},{50.53,96.34},{11.75,41.66},{95.88,162.46},{58.05,114.23},
  {22.29,56.67},{96.68,135.28},{0.80,32.17},{87.28,125.40},{26.26,65.56},{64.70,
  91.01},{46.90,92.60},{77.40,107.37},{98.27,153.00},{31.49,68.28},{94.76,
  149.35},{72.16,110.02},{23.15,58.51},{17.42,51.20},{58.39,113.47},{88.10,
  134.35},{21.16,61.05},{63.87,124.23},{25.51,48.16},{82.99,140.22},{21.15,
  62.69},{92.74,137.12},{11.05,45.03},{72.26,130.11},{16.02,54.59},{23.16,
  62.52},{60.00,86.28},{18.49,63.97},{87.45,131.45},{37.48,71.12},{84.73,
  127.60},{56.78,75.61},{93.81,153.64},{45.27,81.67},{16.82,47.71},{42.92,
  87.31},{73.80,114.49},{86.01,134.52},{17.92,62.84},{98.22,145.16},{61.97,
  100.25},{7.52,56.74},{26.82,61.80},{35.58,58.76},{10.16,39.63},{49.24,97.69},
  {56.86,100.78},{9.62,43.75},{98.44,150.73},{12.78,53.12},{84.08,129.16},
  {96.69,135.91},{29.12,81.61},{75.09,113.68},{96.50,139.38},{46.88,74.27},
  {5.31,42.20},{77.98,118.35},{71.24,121.81},{91.87,141.74},{48.37,94.62},
  {69.70,113.25},{67.02,110.61},{89.57,130.27},{50.56,93.69},{78.18,134.57},
  {29.08,57.57},{95.63,150.69},{59.97,95.07},{40.07,66.53},{9.12,61.97},{6.72,
  36.59},{8.22,42.84},{84.25,115.34},{4.54,43.30},{81.37,125.28},{24.54,63.39},
  {7.96,39.69},{96.97,139.08},{38.09,82.14},{61.43,124.20},{18.84,43.75},{23.84,
  62.58},{51.17,108.47},{62.67,89.82},{69.59,104.62},{44.83,94.29},{57.03,
  96.77},{38.77,76.35},{91.18,144.69},{30.02,71.49},{8.22,45.83},{60.36,90.89},
  {33.34,87.56},{27.34,53.76},{0.02,9.95},{2.57,22.41},{24.77,53.14},{50.54,
  85.41},{87.20,134.04},{16.89,52.73},{41.63,85.72},{75.62,135.39},{3.67,43.22},
  {31.15,75.30},{28.18,68.22},{62.50,100.31},{84.24,119.66},{83.32,129.72},
  {48.69,83.50},{69.34,87.64},{49.54,71.56},{48.13,90.66},{71.77,112.08},{63.43,
  116.37},{8.30,42.37},{96.27,151.77},{38.34,65.26},{46.20,91.51},{95.27,
  138.74},{24.12,58.49},{62.57,101.73},{60.77,93.60},{20.00,49.45},{16.70,
  58.47},{93.97,155.46},{29.89,81.03},{47.17,79.52},{53.35,100.92},{71.44,
  108.95},{74.56,128.18},{22.96,46.90},{80.05,126.79},{47.05,96.48},{6.28,
  40.88},{18.83,53.84},{39.43,81.89},{96.57,139.42},{82.33,127.47},{70.71,
  112.04},{65.13,115.45},{17.25,29.30},{97.59,127.56},{59.99,88.71},{15.82,
  48.95},{27.53,59.62},{14.29,41.44},{82.30,144.48},{41.35,77.34},{61.24,95.23},
  {23.74,66.98},{12.73,46.69},{98.84,136.06},{28.84,59.18},{40.59,81.77},{9.73,
  54.72},{66.31,108.78},{87.06,130.24},{63.93,97.12},{35.18,94.61},{11.25,
  57.00},{9.50,45.01},{35.14,58.94},{48.75,100.72},{5.07,40.85},{79.15,122.65},
  {12.00,34.98},{49.08,83.04},{61.98,109.85},{92.77,159.49},{70.89,119.92},
  {82.00,132.85},{9.34,25.61},{12.42,35.19},{63.23,117.72},{55.92,87.85},{72.87,
  109.86},{72.62,108.87},{62.14,111.59},{20.15,64.70},{36.74,83.27},{85.63,
  122.75},{57.17,105.70},{76.87,132.67},{79.57,122.25},{94.29,145.32},{9.55,
  55.92},{82.58,119.48},{53.60,85.49},{74.46,120.05},{27.24,63.37},{47.58,
  92.75},{87.61,135.22},{77.45,114.49},{3.43,43.59},{40.90,83.56},{11.78,40.71},
  {6.46,44.37},{37.42,68.37},{7.91,36.72},{35.07,68.66},{2.59,46.73},{16.59,
  62.05},{55.37,87.85},{2.22,43.94},{0.49,38.92},{79.96,130.77},{47.11,107.53},
  {50.25,95.41},{10.44,20.99},{1.93,34.17},{65.89,110.80},{77.15,129.41},{37.46,
  79.90},{9.14,43.14},{55.34,83.71},{63.34,118.70},{89.32,130.12},{70.25,
  119.86},{81.65,140.38},{99.17,135.70},{2.70,46.71},{81.42,110.49},{97.50,
  142.37},{62.23,88.47},{95.79,148.88},{15.76,60.89},{94.18,155.63},{7.44,
  54.14},{23.62,62.57},{55.58,85.72},{47.75,78.71},{18.89,57.65},{78.46,131.60},
  {54.22,92.59},{72.59,106.91},{98.29,143.49},{82.06,125.39},{33.67,68.47},
  {58.38,93.19},{40.86,74.42},{90.71,122.93},{37.32,58.73},{32.95,84.96},{15.21,
  60.66},{20.61,37.68},{12.00,46.03},{32.01,42.03},{95.37,152.74},{40.29,76.77},
  {83.70,131.48},{51.58,104.96},{52.08,94.18},{26.36,54.44},{40.21,79.70},
  {22.13,59.01},{75.06,112.61},{57.97,94.59},{68.35,111.51},{51.20,92.39},{1.39,
  40.03},{37.72,65.91},{3.54,19.31},{70.19,114.89},{68.10,113.76},{4.64,29.71},
  {2.23,47.93},{77.22,113.13},{3.03,45.20},{40.66,96.00},{92.58,137.90},{35.87,
  59.91},{76.78,133.29},{80.14,144.38},{29.88,71.39},{15.25,47.84},{39.13,
  79.05},{28.53,68.66},{21.78,61.48},{40.56,63.12},{81.04,136.08},{69.44,
  115.22},{7.64,48.16},{77.22,117.54},{6.83,38.94},{35.13,70.66},{13.00,36.65},
  {45.97,87.41},{93.48,153.33},{46.98,97.53},{8.65,36.69},{30.98,56.26},{28.28,
  67.63},{17.55,31.43},{19.08,45.96},{51.29,85.55},{49.95,97.67},{9.07,48.32},
  {8.09,47.64},{63.14,104.02},{76.12,134.96},{36.28,87.80},{81.84,130.30},
  {91.85,137.01},{49.47,115.87},{43.97,98.90},{36.17,79.87},{53.16,94.91},
  {49.25,96.02},{21.08,47.05},{47.01,95.84},{90.57,153.22},{10.92,46.45},{9.08,
  41.78},{60.04,96.29},{11.28,56.40},{63.27,116.97},{91.15,150.37},{14.92,
  60.84},{66.57,102.24},{60.20,107.99},{62.38,104.44},{15.77,50.94},{99.60,
  169.05},{74.66,108.14},{42.74,73.90},{3.64,34.21},{23.79,61.30},{7.33,50.34},
  {28.87,67.60},{63.83,97.19},{72.50,131.74},{86.29,136.35},{79.36,126.60},
  {87.95,136.49},{18.20,61.21},{68.91,116.12},{11.28,78.15},{10.46,43.33},
  {75.39,107.70},{93.43,134.22},{15.36,33.82},{39.46,70.53},{19.45,49.37},
  {24.86,45.17},{34.80,68.77},{67.12,114.49},{0.80,29.31},{20.90,69.56},{77.88,
  124.96},{36.86,96.15},{46.36,101.73},{60.20,95.29},{52.58,101.04},{16.97,
  37.54},{35.82,72.18},{16.50,46.59},{74.15,117.87},{24.90,86.04},{30.67,70.06},
  {81.02,126.74},{0.57,35.32},{94.89,139.93},{11.79,50.07},{40.58,78.68},{53.32,
  97.48},{94.18,138.34},{95.75,158.94},{35.20,89.91},{52.10,86.13},{84.00,
  138.07},{44.22,85.84},{35.05,70.30},{67.64,107.52},{77.56,100.00},{26.72,
  72.63},{89.37,131.19},{15.36,39.75},{23.99,56.09},{99.44,128.50},{31.73,
  61.76},{63.72,113.69},{82.00,133.41},{89.95,120.95},{33.02,80.52},{55.60,
  100.66},{56.35,102.39},{55.15,107.69},{91.10,138.10},{96.05,140.07},{36.39,
  78.18},{40.19,85.39},{99.19,146.25},{85.49,118.13},{92.77,125.59},{44.65,
  89.63},{41.67,108.83},{63.29,100.21},{33.00,64.38},{44.26,87.64},{71.84,
  117.84},{85.87,139.89},{33.60,82.68},{27.72,64.78},{65.25,108.00},{32.61,
  60.13},{19.38,49.66},{92.50,122.18},{52.60,99.33},{78.60,128.92},{78.79,
  129.93},{58.01,98.97},{6.24,32.80},{45.14,79.00},{36.80,79.23},{83.41,135.33},
  {27.41,83.97},{3.08,48.95},{14.97,61.54},{2.29,33.63},{12.78,58.61},{29.06,
  56.83},{4.76,33.56},{44.48,99.36},{3.19,34.18},{2.77,38.03},{41.13,69.84},
  {58.75,87.51},{76.58,114.13},{10.80,42.09},{7.25,29.21},{64.33,119.71},{90.98,
  152.02},{59.56,101.19},{61.18,84.84},{39.79,78.18},{23.48,64.07},{72.83,
  126.00},{87.45,134.61},{5.67,26.72},{50.66,98.12},{7.20,33.36},{87.71,147.53},
  {95.11,132.59},{21.14,66.53},{79.89,129.09},{97.99,150.24},{16.62,55.54},
  {30.29,52.75},{50.85,101.16},{95.73,156.75},{90.93,130.57},{88.46,123.46},
  {43.91,97.11},{11.50,41.30},{24.87,60.88},{61.13,107.51},{36.42,83.76},{91.85,
  136.43},{65.20,102.56},{12.93,44.03},{95.29,164.86},{72.33,111.45},{97.58,
  136.71},{78.12,122.63},{19.66,69.59},{36.77,63.80},{89.73,161.34},{69.58,
  123.34},{34.76,70.74},{94.14,167.43},{24.41,69.60},{91.18,124.81},{70.00,
  119.02},{42.67,91.12},{29.20,70.69},{94.21,140.59},{26.10,51.23},{21.76,
  58.65},{40.08,81.36},{20.74,54.93},{73.80,132.11},{95.11,148.78},{24.37,
  59.39},{73.12,111.54},{35.27,56.01},{36.63,74.21},{77.30,119.72},{59.37,
  86.61},{28.83,77.81},{44.40,65.13},{67.12,122.37},{45.54,85.37},{66.51,
  109.42},{62.35,123.89},{9.41,37.89},{14.33,46.59},{83.91,147.34},{85.04,
  134.31},{63.13,111.50},{83.24,128.67},{0.98,19.84},{42.32,68.89},{58.82,
  119.45},{72.88,136.15},{47.55,78.33},{78.48,114.08},{97.57,157.86},{19.16,
  74.40},{33.51,48.58},{39.25,64.16},{72.42,114.13},{53.05,108.36},{14.12,
  49.96},{4.98,42.65},{90.62,139.03},{10.64,37.26},{90.61,137.54},{97.90,
  139.96},{91.96,160.55},{17.79,62.50},{24.32,47.36},{23.99,64.53},{0.55,40.75},
  {11.50,35.24},{97.91,131.01},{71.26,102.60},{39.53,58.33},{79.07,139.86},
  {56.12,88.90},{82.22,127.29},{98.50,150.28},{99.66,149.09},{43.34,77.44},
  {2.38,30.29},{28.74,54.26},{83.95,125.24},{19.49,45.54},{41.43,98.07},{47.52,
  82.07},{54.19,98.83},{1.30,51.85},{86.33,129.04},{71.68,113.94},{41.11,69.80},
  {81.32,122.13},{96.45,147.89},{14.79,38.32},{37.11,70.34},{94.59,140.97},
  {70.22,96.42},{27.23,69.49},{62.72,94.45},{40.94,72.04},{67.92,113.70},{89.77,
  132.41},{92.46,121.27},{52.27,99.31},{38.45,84.61},{20.06,52.99},{75.13,
  108.86},{86.90,114.10},{19.84,59.29},{11.73,34.94},{8.77,36.88},{36.75,77.20},
  {60.73,95.15},{35.47,74.82},{32.05,60.45},{44.96,92.42},{17.78,42.52},{26.02,
  62.08},{26.60,54.45},{99.36,131.56},{65.18,109.25},{50.32,97.97},{73.86,
  130.08},{74.52,121.50},{96.95,144.10},{11.24,48.44},{27.25,60.16},{99.19,
  130.15},{93.55,145.14},{14.47,49.54},{34.80,74.97},{49.21,91.04},{46.42,
  72.15},{5.54,24.04},{71.33,110.28},{29.47,50.85},{79.94,104.71},{92.96,
  138.63},{93.74,154.51},{65.66,93.17},{28.38,65.98},{81.52,134.89},{36.08,
  68.32},{3.31,17.57},{95.37,146.38},{94.42,133.61},{23.56,47.78},{14.97,37.83},
  {79.84,129.72},{76.77,105.21},{91.91,138.67},{4.63,33.25},{98.04,162.98},
  {82.33,133.13},{25.17,44.91},{6.45,30.53},{4.20,43.70},{67.41,108.69},{83.67,
  143.83},{51.44,86.34},{81.83,138.54},{89.40,137.75},{71.64,109.63},{86.84,
  124.36},{37.21,79.39},{26.38,56.02},{52.61,82.90},{77.81,108.00},{0.94,18.74},
  {40.30,69.80},{5.32,38.54},{44.82,77.36},{89.75,152.00},{82.54,131.12},{59.53,
  114.59},{27.22,74.53},{35.12,73.60},{2.43,46.64},{79.45,127.76},{69.45,
  109.17},{62.55,123.00},{46.90,88.74},{29.94,59.04},{21.30,47.26},{69.67,
  107.20},{99.86,168.57},{16.48,52.52},{81.80,122.69},{26.47,63.97}
};
