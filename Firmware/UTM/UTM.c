#include "UTM.h"
#include <math.h>
double sa, sb, e2, c, la, lo, lat, lon, S, deltaS, a, epsilon, nu, v, ta,
		 a1, a2, j2, j4, j6, alfa, beta, gama, Bm, xx, yy, e2cuadrada, e2cuadrada1;
uint8_t Huso, Letra;
/**
  * @brief  This is the code of Rafeal Palacios, which can convert the coordinate from Degree to UTM 
  * @param  dCoordinate[i][2] is the matrix of coordinates, which you want to convert. It has the following structure:
						dCoordinate[i][0]: is the Latitude
						dCoordinate[i][1]: is the Longitude
  * @retval The dUTM_Coordinate[i][2] matrix has the following structure:
						dUTM[i][0]: is the x
						dUTM[i][1]: is the y
						The ui8_Utmzone[i][2] matrix has the following structure:
						ui8_Utmzone[i][0]: is the huso
						ui8_Utmzone[i][1]: is the letra
  */
void UTM_Deg2utm(double dCoordinate[][2], double dUTM_Coordinate[][2], uint8_t ui8_Utmzone[][2], uint32_t ui32_Coor_Size)
{
//	double sa, sb, e2, c, la, lo, lat, lon, S, deltaS, a, epsilon, nu, v, ta,
//		   a1, a2, j2, j4, j6, alfa, beta, gama, Bm, xx, yy, e2cuadrada, e2cuadrada1;
//	uint8_t Huso, Letra;
	uint32_t ui32_Index = 0; 
	
	//Memory pre-allocation
	for(ui32_Index = 0; ui32_Index < ui32_Coor_Size; ui32_Index++)
	{
		dUTM_Coordinate[ui32_Index][0] = dUTM_Coordinate[ui32_Index][1] = 0;
		ui8_Utmzone[ui32_Index][0] = 60;
		ui8_Utmzone[ui32_Index][1] = 'X';
	}
	
	//Main loop
	for(ui32_Index = 0; ui32_Index < ui32_Coor_Size; ui32_Index++)
	{
		la=dCoordinate[ui32_Index][0];
		lo=dCoordinate[ui32_Index][1];
		sa = 6378137.000000 ; sb = 6356752.314245;
			 
		//e = ( sqrt( ( sa*sa ) - ( sb*sb ) ) ) / sa;
		//e2 =  ( sqrt( ( sa*sa ) - ( sb*sb ) ) ) / sb;
		//e2 = 0.082094437950043;
		//e2cuadrada = e2*e2;
		e2cuadrada = 0.006739496742333;
		e2cuadrada1 = 0.006739496742333;
		//c = ( sa*sa ) / sb;
		c = 6399593.625758674;
		//alpha = ( sa - sb ) / sa; //f
		//ablandamiento = 1 / alpha;   //1/f

		lat = la * ( PI_RAD / 180 );
		lon = lo * ( PI_RAD / 180 );

		Huso = floor( ( lo / 6 ) + 31); 
		S = ( ( Huso * 6 ) - 183 );
		deltaS = lon - ( S * ( PI_RAD / 180 ) );

		if (la<-72) Letra='C';
		else if (la<-64) Letra='D';
		else if (la<-56) Letra='E';
		else if (la<-48) Letra='F';
		else if (la<-40) Letra='G';
		else if (la<-32) Letra='H';
		else if (la<-24) Letra='J';
		else if (la<-16) Letra='K';
		else if (la<-8) Letra='L';
		else if (la<0) Letra='M';
		else if (la<8) Letra='N';
		else if (la<16) Letra='P';
		else if (la<24) Letra='Q';
		else if (la<32) Letra='R';
		else if (la<40) Letra='S';
		else if (la<48) Letra='T';
		else if (la<56) Letra='U';
		else if (la<64) Letra='V';
		else if (la<72) Letra='W';
		else Letra='X';

		a = cos(lat) * sin(deltaS);
//		a = cos(PI_RAD/4) * sin(PI_RAD/5);
		epsilon = 0.5 * log( ( 1 +  a) / ( 1 - a ) );
		nu = atan( tan(lat) / cos(deltaS) ) - lat;
		v = ( c / sqrt( ( 1 + ( e2cuadrada1 * ( cos(lat)*cos(lat) ) ) ) ) ) * 0.9996;
		ta = ( e2cuadrada / 2 ) * (epsilon*epsilon) * ( cos(lat)*cos(lat) );
		a1 = sin( 2 * lat );
		a2 = a1 * ( cos(lat)*cos(lat) );
		j2 = lat + ( a1 / 2 );
		j4 = ( ( 3 * j2 ) + a2 ) / 4;
		j6 = ( ( 5 * j4 ) + ( a2 * ( cos(lat)*cos(lat) )) ) / 3;
		//alfa = ( 3 / 4 ) * e2cuadrada;
		alfa = 0.005054622556750;
		//beta = ( 5 / 3 ) * (alfa * alfa);
		beta = 0.000042582015318;
		//gama = ( 35 / 27 ) * (alfa * alfa * alfa);
		gama = 0.000000167405789;
		Bm = 0.9996 * c * ( lat - alfa * j2 + beta * j4 - gama * j6 );
		xx = epsilon * v * ( 1 + ( ta / 3 ) ) + 500000;
		yy = nu * v * ( 1 + ta ) + Bm;

		if (yy<0)
		   yy=9999999+yy;

		dUTM_Coordinate[ui32_Index][0]=xx;
		dUTM_Coordinate[ui32_Index][1]=yy;
		ui8_Utmzone[ui32_Index][0] = Huso;
		ui8_Utmzone[ui32_Index][1] = Letra;
 }

}
