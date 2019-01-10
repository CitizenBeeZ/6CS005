#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/******************************************************************************
 * This program takes an initial estimate of m and c and finds the associated 
 * rms error. It is then as a base to generate and evaluate 8 new estimates, 
 * which are steps in different directions in m-c space. The best estimate is 
 * then used as the base for another iteration of "generate and evaluate". This 
 * continues until none of the new estimates are better than the base. This is
 * a gradient search for a minimum in mc-space.
 * 
 * To compile:
 *   cc -o lr_coursework lr_coursework.c -lm
 * 
 * To run:
 *  https://canvas.wlv.ac.uk/calendar ./lr_coursework
 * 
 * Dr Kevan Buckley, University of Wolverhampton, 2018
 *****************************************************************************/

typedef struct point_t {
  double x;
  double y;
} point_t;

int n_data = 1000;
point_t data[];

/*int time_difference(struct timespec *start, struct timespec *finish, long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec;
  long long int dn =  finish->tv_nsec - start->tv_nsec;
  if(dn < 0 ) {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

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
}*/

double line(double m, double x, double c) {
	double y = (m * x) +c;
	return y;
}

int main(int args, char *argv[]) {
	if (args != 3) {
		fprintf(stderr, "You need to specify a slope and intercept\n");
		return 1;
	}

  int i;
	double slope = (double) atof(argv[1]);
	double intercept = (double) atof(argv[2]);
	double x, y;

	printf("x,y\n");
		for(i=0; i<1000; i++){
			x=(i /10.0);
			y = line(slope, x, intercept);
			printf("%lf, %lf\n", x,y);
	}

  /*double bm = 1.3;
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

  struct timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

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

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was, %lld,ns or %0.9lf,s\n", time_elapsed,
         (time_elapsed/1.0e9));*/
  return 0;
}

point_t data[] = {
  {67.98,72.86},{72.02,121.49},{82.57,126.11},{73.94,130.07},
  {83.66,115.76},{84.13,109.93},{79.89,115.22},{80.17,118.88},
  {72.60,98.79},{69.11,93.40},{82.51,108.77},{66.85,92.86},
  {69.28,93.71},{69.62,120.06},{83.03,96.81},{76.56,107.48},
  {69.85,114.10},{89.46,123.00},{54.70,78.18},{58.08,91.85},
  {57.56,90.21},{72.68,112.10},{33.61,63.88},{40.83,71.19},
  {15.18,29.73},{81.49,114.72},{51.74,83.70},{70.91,92.98},
  {30.08,73.13},{77.69,111.95},{21.50,52.81},{75.95,93.88},
  {85.06,105.59},{20.51,43.20},{39.04,60.39},{37.18,50.60},
  {19.21,54.82},{68.45,105.10},{ 0.11,52.19},{ 8.39,41.88},
  {33.74,74.63},{76.85,99.26},{42.68,63.27},{69.41,104.25},
  {74.85,117.93},{85.45,112.78},{79.19,125.00},{48.46,79.10},
  {25.90,56.04},{92.02,112.20},{74.13,108.95},{96.93,125.88},
  {15.03,31.67},{40.21,74.85},{38.55,70.50},{20.08,43.84},
  {49.03,88.26},{66.04,94.67},{82.49,122.35},{ 8.75,49.95},
  {94.69,134.32},{78.20,115.08},{53.80,70.65},{56.31,99.57},
  {65.08,75.93},{88.99,143.82},{77.72,124.76},{19.19,51.43},
  {17.87,42.23},{31.07,51.48},{12.70,51.82},{84.63,127.68},
  { 9.09,38.36},{71.34,117.87},{ 8.72,33.16},{65.33,91.08},
  {71.24,125.14},{ 6.11,29.05},{37.55,65.63},{88.29,127.64},
  {45.14,81.26},{51.19,79.63},{86.16,118.06},{92.61,133.30},
  {14.97,58.65},{34.30,44.22},{70.26,87.77},{43.75,71.15},
  {47.97,67.58},{93.06,137.73},{ 2.93,32.64},{80.56,124.36},
  {43.15,74.38},{93.15,122.12},{85.61,107.78},{81.12,116.04},
  {70.10,100.47},{38.00,67.49},{65.09,89.42},{89.95,128.91},
  {64.18,86.63},{12.44,39.02},{99.41,128.49},{33.93,76.66},
  {32.45,53.71},{21.12,52.13},{91.86,132.82},{17.41,37.59},
  {25.94,58.45},{86.53,108.19},{49.07,91.20},{ 6.57,26.70},
  {72.03,110.77},{32.88,77.61},{56.60,89.05},{53.04,68.41},
  {36.18,68.32},{74.34,110.02},{35.96,65.69},{91.34,121.61},
  {95.86,117.85},{96.15,147.12},{87.52,126.28},{96.74,134.54},
  {17.35,26.70},{12.58,18.78},{28.53,70.44},{18.60,44.67},
  {61.69,84.49},{28.85,40.73},{22.52,53.34},{54.82,97.34},
  {20.34,49.79},{15.70,33.76},{63.45,91.61},{47.25,69.81},
  {19.11,45.60},{31.02,68.30},{36.26,64.80},{60.44,95.08},
  { 8.99,28.88},{84.84,129.88},{ 5.09,30.21},{66.13,100.26},
  {63.62,82.43},{10.40,33.62},{95.10,146.64},{ 7.57,50.98},
  {92.10,138.76},{67.18,104.50},{10.02,37.03},{15.37,36.20},
  {43.27,71.96},{83.69,91.26},{73.16,95.39},{ 8.57,40.71},
  {85.73,110.46},{62.25,77.14},{98.10,158.89},{83.64,118.39},
  {98.21,132.31},{70.32,95.66},{71.27,96.05},{53.62,80.59},
  {79.48,108.01},{20.83,46.06},{33.81,59.00},{52.05,83.03},
  {39.84,46.24},{79.97,114.69},{19.50,33.45},{86.84,112.48},
  {27.50,66.83},{68.06,97.16},{94.50,140.40},{70.06,97.66},
  { 9.51,55.46},{62.06,83.11},{29.50,61.84},{35.75,47.26},
  {69.00,92.12},{46.96,66.46},{74.23,115.20},{64.61,105.51},
  { 6.18,29.26},{22.66,22.54},{98.97,145.01},{69.66,102.09},
  {26.16,49.32},{22.25,37.34},{ 2.50,17.40},{22.13,40.23},
  { 6.73,37.72},{99.41,137.47},{46.27,86.47},{93.52,129.57},
  {28.65,56.58},{24.26,46.85},{25.75,56.05},{18.62,59.32},
  {71.49,114.00},{88.43,112.19},{12.99,32.69},{52.75,78.17},
  {16.92,38.47},{42.19,83.91},{79.37,120.75},{82.45,117.44},
  {87.49,115.25},{94.21,118.79},{85.80,127.54},{22.24,42.54},
  {15.85,38.33},{18.57,48.92},{63.38,93.61},{42.73,73.51},
  {32.93,57.20},{26.18,44.49},{76.10,110.75},{31.24,56.19},
  {29.02,54.23},{98.35,127.20},{ 3.15,19.47},{76.05,95.41},
  {23.49,46.25},{90.18,122.46},{48.79,68.21},{65.09,85.25},
  { 1.31,23.86},{ 9.44,44.97},{81.25,107.59},{72.02,102.95},
  { 4.74,20.90},{97.75,129.72},{ 9.57,42.75},{45.74,95.22},
  {28.02,69.54},{69.27,87.04},{69.28,114.49},{18.20,37.12},
  {54.60,65.86},{63.45,101.49},{88.94,126.19},{30.14,70.99},
  {93.73,115.72},{80.98,103.65},{37.37,71.24},{22.64,52.21},
  {13.08,37.40},{87.23,116.35},{ 7.16,46.47},{ 0.09,28.01},
  {64.94,105.79},{35.73,86.41},{67.14,111.06},{32.01,66.54},
  {90.01,133.67},{98.42,127.59},{48.98,85.46},{ 2.12,28.16},
  { 4.36,54.51},{64.39,101.65},{48.04,82.59},{75.03,102.60},
  {47.97,66.81},{20.24,33.85},{11.87,40.27},{94.56,123.17},
  {85.45,118.35},{24.05,45.80},{76.07,100.69},{ 3.13,28.05},
  {62.56,93.74},{78.29,104.46},{59.34,89.12},{48.39,73.15},
  {20.47,51.63},{80.97,114.58},{93.33,135.74},{ 1.79,33.00},
  {20.12,37.59},{37.14,79.35},{71.07,108.55},{45.29,72.51},
  {12.42,28.89},{49.30,78.97},{45.50,64.44},{20.31,63.73},
  {74.58,107.24},{13.26,34.52},{61.57,86.12},{77.35,96.35},
  {71.91,102.66},{64.69,98.29},{91.35,129.32},{97.95,126.95},
  {30.75,48.84},{41.43,84.83},{63.43,85.08},{98.99,134.50},
  {44.73,75.10},{22.76,51.85},{42.36,67.84},{84.28,126.36},
  {17.60,37.14},{27.02,47.41},{15.40,39.72},{27.34,45.49},
  {62.96,90.28},{87.22,116.25},{45.96,82.18},{15.57,45.43},
  {92.06,124.36},{41.66,69.65},{47.81,65.15},{27.22,51.25},
  {44.21,80.96},{25.17,64.65},{ 7.02,30.35},{98.39,135.29},
  { 9.74,41.30},{ 6.31,43.90},{87.75,116.75},{72.25,112.85},
  {25.73,57.79},{63.31,83.32},{64.95,92.98},{97.01,134.91},
  {57.89,86.61},{77.52,116.27},{11.23,17.18},{17.20,53.05},
  {16.24,46.25},{25.37,77.19},{51.05,83.74},{75.23,119.64},
  {61.35,100.17},{65.98,96.23},{25.99,50.50},{ 8.83,36.84},
  {73.77,89.95},{56.54,84.52},{43.48,77.55},{81.59,122.18},
  {30.30,66.46},{49.72,96.63},{79.97,109.35},{47.88,72.85},
  { 8.16,38.93},{ 9.79,36.77},{49.91,78.85},{14.71,28.84},
  { 8.62,49.10},{26.93,49.27},{71.99,94.09},{43.38,61.76},
  {18.60,40.29},{37.03,58.92},{71.31,106.99},{ 3.20, 7.88},
  {65.80,78.56},{79.85,115.69},{53.22,86.56},{33.71,62.14},
  {26.06,65.68},{78.91,101.78},{74.51,110.85},{63.23,68.61},
  {13.20,40.12},{34.81,52.07},{56.12,94.44},{48.15,90.88},
  {19.26,43.74},{ 6.85,23.65},{22.89,51.29},{40.36,71.12},
  { 5.32,10.10},{98.57,135.26},{ 5.72,37.58},{35.80,61.85},
  {74.35,130.77},{44.65,77.77},{40.33,53.98},{99.66,130.49},
  { 7.47,16.05},{99.99,135.78},{49.96,59.18},{86.11,137.83},
  {28.11,61.95},{38.82,58.89},{95.08,120.72},{32.56,60.55},
  {13.90,50.06},{17.12,46.71},{94.32,135.38},{47.34,90.08},
  {69.43,114.25},{75.57,105.21},{56.99,86.50},{40.44,70.09},
  {52.23,75.09},{53.86,74.32},{ 2.21,21.73},{55.72,63.56},
  {94.03,125.36},{60.36,80.49},{ 8.90,45.26},{97.06,120.41},
  { 8.31,20.39},{58.60,77.34},{43.23,94.93},{84.25,136.71},
  {63.12,88.25},{72.67,110.82},{66.75,110.84},{28.11,65.68},
  {25.89,36.51},{85.87,108.23},{65.82,100.72},{67.39,94.30},
  {27.43,63.15},{89.69,120.78},{31.63,58.25},{99.43,145.69},
  { 3.12,36.92},{98.74,132.67},{69.48,125.02},{49.71,80.07},
  {35.89,70.91},{12.56,41.65},{39.53,81.07},{39.48,67.33},
  {13.89,39.06},{77.92,96.14},{73.51,92.46},{66.21,100.32},
  {86.15,133.90},{ 7.05,30.80},{16.14,49.83},{52.77,59.63},
  {43.98,75.04},{24.03,63.80},{40.26,76.89},{34.98,77.88},
  {91.74,132.64},{60.76,93.42},{23.23,53.85},{20.49,54.88},
  {12.34,25.36},{28.20,54.04},{53.59,66.83},{38.72,63.98},
  {58.56,84.35},{65.38,105.30},{41.18,69.71},{55.98,92.20},
  {79.74,128.00},{25.83,60.35},{ 2.12,34.42},{29.76,58.33},
  {60.65,86.20},{23.70,49.85},{78.15,122.98},{88.18,114.34},
  {16.35,38.11},{60.38,80.90},{73.08,96.10},{98.28,142.95},
  {44.63,74.85},{92.38,132.87},{25.57,37.73},{ 0.04,24.13},
  {39.33,58.12},{83.95,115.08},{35.50,64.42},{ 0.17, 9.05},
  {64.58,94.58},{35.24,70.09},{97.30,135.67},{26.06,45.26},
  { 0.90,30.12},{80.66,106.03},{82.07,122.43},{72.73,120.24},
  { 7.55,30.75},{91.21,120.65},{14.11,42.15},{29.63,45.31},
  {20.51,45.83},{38.98,61.72},{29.67,46.13},{37.15,60.72},
  {57.10,82.78},{84.33,122.82},{76.45,112.19},{26.85,50.43},
  {83.25,125.70},{35.11,67.01},{48.39,67.41},{92.69,117.42},
  {99.04,133.07},{16.72,45.04},{65.69,96.08},{44.01,81.74},
  {92.73,122.89},{11.55,34.29},{82.97,122.08},{23.38,41.46},
  {52.09,100.25},{92.06,130.54},{35.62,59.91},{88.09,120.12},
  {16.59,35.88},{47.29,72.47},{31.12,42.42},{31.69,56.24},
  {69.76,97.67},{29.68,56.28},{53.28,84.20},{72.66,95.53},
  {84.83,124.09},{65.01,114.18},{27.16,51.41},{54.48,90.32},
  { 3.69,30.82},{55.16,68.85},{30.97,64.40},{41.66,55.99},
  {17.41,28.20},{31.03,57.96},{99.95,132.54},{54.90,94.98},
  {39.56,66.54},{58.22,89.72},{10.70,51.97},{36.87,60.05},
  {49.68,77.57},{58.51,88.82},{57.19,95.75},{57.56,84.55},
  {27.79,63.65},{56.84,75.63},{55.95,80.88},{ 1.91,25.62},
  {43.77,69.59},{ 8.28,30.30},{30.97,44.56},{35.70,48.43},
  {35.10,43.36},{45.53,75.09},{33.33,53.23},{95.39,136.26},
  {39.03,80.93},{32.37,55.13},{41.52,60.06},{ 8.65,21.60},
  {87.60,120.68},{63.20,85.51},{42.86,66.78},{42.44,65.48},
  {78.99,121.64},{91.07,124.54},{26.39,65.90},{52.95,82.21},
  {52.19,76.07},{94.45,132.48},{ 3.81,22.73},{93.38,120.12},
  {67.31,102.54},{ 5.64,31.88},{95.31,121.28},{71.00,101.76},
  {56.96,86.59},{51.00,91.45},{85.08,114.82},{76.70,108.14},
  {79.64,122.91},{82.79,106.84},{10.66,48.01},{93.14,150.77},
  {96.47,138.41},{46.77,69.40},{79.79,109.79},{25.98,67.04},
  {88.91,130.04},{16.55,48.93},{65.08,102.75},{73.49,106.25},
  {14.06,53.92},{26.60,52.30},{80.98,112.10},{49.58,67.20},
  {92.46,118.24},{66.48,105.97},{79.58,125.30},{43.75,78.40},
  { 4.75,29.98},{83.29,126.75},{79.16,135.90},{17.82,53.93},
  {77.44,105.97},{84.35,116.54},{62.58,117.87},{14.84,59.66},
  {17.08,35.95},{62.65,96.65},{70.39,105.03},{72.52,99.37},
  {94.01,120.53},{40.31,70.67},{44.35,74.97},{71.51,111.60},
  {54.10,83.47},{41.54,58.50},{37.91,60.92},{72.63,102.90},
  { 8.15,49.42},{91.70,120.00},{41.63,70.14},{47.14,76.74},
  {70.47,96.46},{16.61,38.40},{97.68,129.24},{36.24,65.72},
  {89.49,136.43},{85.12,127.41},{83.10,119.58},{84.25,122.70},
  {56.10,79.87},{19.75,57.34},{88.76,114.02},{97.26,143.19},
  {60.96,93.88},{85.88,127.06},{74.62,91.32},{64.27,97.94},
  { 7.57,27.88},{57.09,106.11},{52.10,85.28},{54.30,84.57},
  {49.60,83.27},{94.11,120.31},{16.18,35.67},{92.45,138.61},
  {67.76,99.96},{10.37,38.68},{16.96,51.66},{99.55,114.71},
  {86.72,125.13},{83.26,102.62},{88.81,118.53},{57.69,84.14},
  {88.09,119.33},{98.69,123.72},{16.11,43.72},{14.22,58.95},
  {71.11,95.86},{ 5.69,41.04},{23.13,59.63},{66.96,67.53},
  {49.71,113.24},{53.97,96.50},{43.03,67.66},{73.86,97.76},
  { 3.68,39.48},{73.91,115.59},{95.95,132.37},{80.51,96.37},
  {19.52,30.27},{71.32,117.24},{17.74,48.53},{87.40,119.37},
  {80.25,120.08},{91.16,126.78},{45.03,82.59},{73.87,104.05},
  {28.71,56.65},{ 3.65,35.67},{81.76,117.14},{87.51,119.17},
  {79.21,118.84},{66.05,102.02},{22.33,48.93},{70.91,107.70},
  {24.36,42.83},{92.73,119.57},{54.84,74.71},{38.90,76.86},
  {33.44,56.65},{95.72,146.37},{65.28,96.06},{81.08,117.94},
  {51.73,73.85},{67.59,110.14},{59.97,83.39},{ 6.08,38.97},
  {72.52,88.07},{72.21,103.74},{29.67,47.92},{56.58,84.41},
  {15.84,64.75},{49.00,77.58},{88.50,126.22},{74.48,113.57},
  {83.12,110.96},{66.87,102.02},{13.02,43.58},{25.22,50.03},
  {85.12,110.70},{29.29,56.18},{86.98,124.53},{42.95,79.25},
  {43.60,80.60},{31.58,63.84},{45.41,54.26},{78.18,117.76},
  {27.26,42.43},{67.41,87.85},{68.46,109.39},{65.19,105.16},
  {26.65,62.28},{60.94,89.46},{20.30,34.62},{96.29,128.44},
  {63.40,95.34},{13.00,50.65},{42.83,57.99},{22.71,48.58},
  {74.00,104.81},{ 7.19,37.10},{74.73,110.34},{41.60,74.15},
  {11.11,29.87},{25.27,39.60},{ 0.26,39.84},{ 1.02,40.25},
  {69.39,92.52},{15.11,44.29},{65.59,95.36},{24.05,58.03},
  { 1.08, 7.67},{26.20,48.97},{26.06,57.00},{50.62,74.29},
  {17.20,33.93},{24.63,52.43},{74.06,112.59},{13.44,39.45},
  {71.89,113.40},{35.81,73.11},{33.43,46.36},{88.86,124.45},
  { 4.79,14.84},{23.85,44.88},{84.21,121.08},{ 1.50,28.35},
  {32.56,63.59},{21.93,51.74},{96.05,118.26},{46.41,87.50},
  { 0.87,33.71},{43.96,86.13},{46.06,67.38},{30.50,43.54},
  {56.15,87.40},{31.97,74.53},{60.20,88.20},{51.45,75.63},
  {74.82,116.52},{88.61,101.98},{84.19,124.24},{70.82,81.55},
  {39.91,61.07},{56.55,103.37},{74.79,106.80},{72.80,107.32},
  {13.41,27.56},{ 8.20,29.60},{60.66,93.00},{77.08,96.38},
  {87.56,123.69},{78.62,84.74},{58.00,90.51},{61.06,116.46},
  {46.42,94.08},{91.50,148.64},{32.99,58.75},{39.99,66.52},
  {20.11,52.18},{30.99,39.95},{95.25,116.31},{ 6.86,45.91},
  {74.66,97.39},{20.88,71.05},{60.10,79.86},{43.04,50.94},
  {98.32,134.95},{21.95,38.97},{37.15,77.61},{91.95,118.85},
  {96.73,136.03},{31.92,44.71},{33.38,52.72},{61.45,86.33},
  {74.14,107.63},{85.30,115.57},{73.79,104.74},{14.07,42.96},
  {83.74,117.16},{29.09,71.12},{25.53,56.20},{76.08,90.23},
  {72.10,107.27},{76.74,117.82},{27.71,53.82},{39.20,67.29},
  {89.57,110.39},{94.19,117.64},{76.30,101.56},{42.31,65.56},
  {94.12,128.54},{ 8.87,41.00},{37.69,66.53},{57.07,92.92},
  {60.82,97.63},{81.04,114.51},{89.77,115.35},{83.89,114.70},
  {79.91,121.23},{ 7.46,21.41},{20.18,57.73},{46.66,94.82},
  {66.18,99.52},{83.17,99.83},{27.67,62.05},{ 8.16,46.39},
  {73.11,106.17},{31.24,59.63},{ 3.85,37.41},{47.02,83.44},
  {37.61,60.89},{80.65,116.35},{33.11,70.04},{14.95,22.74},
  {44.61,76.62},{36.80,63.46},{14.91,37.50},{97.75,142.84},
  {61.31,85.64},{57.02,87.30},{23.31,24.90},{79.08,115.97},
  {67.57,102.44},{43.10,77.76},{60.39,77.98},{37.89,58.26},
  {51.20,88.08},{79.04,119.41},{78.89,109.14},{19.70,53.61},
  {67.12,96.20},{69.44,91.16},{68.28,89.69},{ 6.07,32.31},
  {52.16,88.81},{56.72,89.38},{51.14,88.74},{34.81,83.94},
  {26.27,56.50},{93.20,126.51},{92.96,109.11},{58.11,82.08},
  {27.00,59.35},{57.21,95.21},{ 0.01,17.53},{25.91,50.11},
  {47.62,68.36},{91.63,120.31},{70.58,90.55},{ 6.97,47.61},
  {10.60,54.82},{54.12,68.12},{18.61,51.08},{35.15,60.78},
  {16.03,49.80},{83.12,142.61},{89.25,126.99},{10.91,45.62},
  {62.47,90.43},{25.53,46.29},{58.95,95.45},{44.22,60.56},
  {54.83,88.36},{82.10,106.74},{37.63,55.71},{65.69,89.28},
  { 3.98,26.10},{66.15,96.27},{10.60,30.94},{82.86,108.63},
  {13.26,63.92},{51.19,91.40},{ 6.41,33.75},{27.01,57.14},
  {94.19,125.78},{48.93,69.11},{38.63,55.41},{91.55,119.60},
  {38.33,64.35},{72.76,110.46},{88.77,136.89},{48.32,74.45},
  {94.28,151.66},{30.46,54.94},{30.33,60.46},{67.87,89.48},
  {49.30,68.29},{92.46,132.98},{74.06,113.69},{58.17,78.48},
  {15.66,29.92},{27.00,53.51},{40.07,63.86},{34.26,58.71},
  {63.83,85.28},{16.95,38.52},{29.48,60.96},{95.89,136.89},
  { 8.33,37.34},{90.00,121.90},{65.20,103.73},{71.02,109.68},
  {35.67,72.89},{ 9.50,24.26},{63.87,95.85},{16.50,54.83},
  {87.18,118.97},{27.21,30.63},{ 1.27,38.08},{55.29,86.34},
  { 5.65,49.85},{44.45,75.38},{29.88,50.44},{73.42,108.53},
  {67.92,100.28},{ 6.45,43.32},{30.87,57.40},{99.59,131.07},
  {23.56,24.64},{55.44,82.72},{ 1.20,15.24},{50.30,86.10},
  {82.44,119.27},{89.69,130.15},{ 8.88,52.82},{49.95,90.79},
  {92.50,136.95},{ 5.99,30.29},{37.76,70.28},{49.27,76.11},
  {51.31,71.10},{59.32,98.44},{30.95,68.85},{82.33,116.56},
  {76.60,124.68},{58.13,82.84},{24.47,29.99},{90.98,116.41},
  {30.86,59.16},{12.70,29.70},{54.46,82.99},{94.70,137.87},
  {62.63,100.08},{64.04,83.29},{49.34,49.35},{17.93,48.21},
  {65.94,91.39},{80.92,97.54},{92.13,119.57},{61.67,89.38},
  {19.57,53.39},{40.01,51.29},{59.93,108.45},{16.73,59.66},
  {12.35,24.37},{12.91,31.31},{32.47,76.68},{90.43,133.70},
  {16.66,17.51},{18.48,49.77},{28.85,49.66},{91.14,119.52},
  {99.84,153.53},{88.39,117.82},{62.14,89.68},{10.62,40.97},
  {38.64,73.37},{60.79,110.08},{11.99,48.18},{47.76,68.53}
};
