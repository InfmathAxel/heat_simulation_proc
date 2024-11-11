#include <cmath>

#include <fstream>
#include <iostream>
#include <iomanip>
#include "tridiag.hpp"
// classe permettant surtour de faire la discretisation selon Mx de Lx et de calculer Ti chapeau
class visualisation {
public : 	
visualisation(double lx, int mx ){
		Lx = lx ; Mx = mx ;
		xi_0_0 = new double[Mx+1];
		
		for (int i = 0 ; i < Mx+1 ; i++){
		 xi_0_0[i] = i* Lx/Mx;
		}
		
		
}

void print(){
	for(int i = 0 ; i < Mx+1 ; i++){
		std::cout << xi_0_0[i] << " " ;}}

double * calcul_Ti(double* xi,int M,double Te, double *T_1d){
		double *T_chap;
		T_chap = new double[Mx+1];
		for (int i = 0 ; i < Mx+1 ; i ++ ){
			
			
			for (int j = 0 ; j < M-1 ; j ++) {
				//std::cout << xi[j]  << " "  << xi_0_0[i] << " " << xi[j+1] << "\n";
					if ((xi[j] <= xi_0_0[i]) and (xi_0_0[i] <= xi[j+1]) ){
							//std::cout << j ; 
							double a = 0 ;
							double b = 0 ;
							a = (T_1d[j] - T_1d[j+1])/ ( xi[j] - xi[j+1]);
							
							b =  T_1d[j] - a*xi[j];
							//std::cout << " a "  << a << " b " << b << "\n";
							T_chap[i] = a*xi_0_0[i] +b ;
							
													break;
							}}
					if (i == Mx) {
						//std::cout << j ; 
							double a = 0 ;
							double b = 0 ;
							a = (T_1d[M-2] - T_1d[M-1])/ ( xi[M-2] - xi[M-1]);
							
							b =  T_1d[M-1] - a*xi[M-1];
							//std::cout << " a "  << a << " b " << b << "\n";
							T_chap[i] = a*xi_0_0[i] +b ;
							break;}
									
			
		}
		

return T_chap;}


private : 
		double Lx;
		int Mx;
		double *xi_0_0;
};





int main(int argc, char **argv)

{	// lecture de simu.Txt
	if (argc >= 2){
		std::ifstream ifile(argv[1]);
	double Lx,Ly,Lz ;
	
	double Phi ;
	double Hc ;
	double Te ;
	double TFinal ;
	int N ; 
	int M ;
	double Cp ;
	double k ;
	double rho ;
	double Mx,My,Mz;
	if(ifile){
	std::string c ;
			
			ifile >> c  >>Lx >> c >> Ly>> c >> Lz;
			   
			ifile >> c >> M;
			ifile >> c >> Phi;
			ifile >> c >> Hc;
			ifile >> c >> rho;
			ifile >> c >> k;
			ifile >> c >> Cp;
			ifile >> c >> Te;
			ifile >> c >> TFinal;
			ifile >> c >> N;
			ifile >> c >>Mx >> c >> My>> c >> Mz;
	// initiation des variable n'étant pas dans simu.txt
	double p = 2*(Ly+Lz);
	double h =Lx/M;
	double S = Lz*Ly;
	double delta_T = TFinal/N;
	double ai[M-1];
	double bi[M];
	double ci[M-1];
	double F[M];
	
	// on initie Ti(0)
	double T[M] ;
	for (int i = 0 ; i <M ; i++){
		T[i] = Te;}
	// on initie les valeurs particulieres de a,b,c,F
	bi[0] = k/h;
	bi[M-1] = k/h;
	ci[0] = -k/h;
	ai[M-2] =-k/h;
	F[0] = Phi;
	F[M-1] = 0;
	//
	for (int i= 1; i <M-1;i++){
		ai[i-1] = -k/(h*h);
		bi[i] = 2*k/(h*h) + Hc*p/S ;
		ci[i] = -k/(h*h);
		F[i] = Hc*p*Te/S;}
		
	tridiag resultat(bi,ci,ai,M);
	//resultat.print();
	double *x ;
	 x = resultat.resolution_LU(F);
	 
	 
	
	visualisation tab(Lx,Mx);
	//tab.print();
	double *t;
	double xi[M];
	for(int i =0; i <M; i++)
		xi[i] = i*h;
	
	
	t = tab.calcul_Ti(xi,M,Te,x);
	
	// je pars du principe que Mx plus grand que My; Mz 
	// ecriture du fichier vtk.
	std::ostringstream donnee;
	donnee <<"données_stationnaire.vtk" ;
	std::ofstream ofile(donnee.str());
	// les commentaires de offiles sont la car le fichier vtk ne fonctionnait pas avec les commandes en commentaire et je veux garder la trace
	//~ ofile << "# vtk DataFile Version 2.0\n"
	//~ ofile << "vtk output\n"
	//~ ofile <<"ASCII\n"
	//~ ofile <<"DATASET STUCTURED_GRID\n"
	//~ ofile << "DIMENSIONS " << Mx << " "  << My << " "  << Mz << "\n" 
	//~ ofile << "POINTS " << Mx*My*Mz << " float" << "\n";	
	ofile << "# vtk DataFile Version 2.0\n";
    ofile << "vtk output\n";
    ofile << "ASCII\n";
    ofile << "DATASET STRUCTURED_GRID\n";
    ofile << "DIMENSIONS " << Mx << " " << My << " " << Mz << "\n";
    ofile << "POINTS " << (Mx)*(My)*(Mz) << " float\n";	 
	for (int i = 0 ; i < Mz ; i++){
		for(int j = 0 ; j < My ; j++){
			for (int k = 0; k< Mx ; k++){
		
		ofile << k << " " << j << " " << i << "\n";} }}
	
	int nb = Mx*My*Mz;
	ofile << "POINT_DATA " << nb << "\n" ;
	ofile << "FIELD FieldData 1\n"; 
	ofile << "sol1 1 " << nb << "float\n" ;
	for (int i = 0 ; i < Mz ; i++){
		for(int j = 0 ; j < My ; j++){
			for (int k = 0; k< Mx ; k++){
				
		
		ofile << t[k] << "\n";}}}
		
	ofile.close();
		
	
	
	
	return 0;
}
std::cout << "donnez un nom de fichier valide" ; return 0 ;}

std::cout <<"donnez un nom de fichier" ; return 0;
}

