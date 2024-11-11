#include <cmath>

#include <fstream>
#include <iostream>
#include <iomanip>
#include "tridiag.hpp"



int main(int argc, char **argv)
{	// lecture du fichier pour avoir les valeurs;
	
	if (argc >= 2){
		std::ifstream ifile(argv[1]);
	//std::ifstream ifile("simu.txt");
	double Lx,Ly,Lz;
	int M;
	double Phi;
	double Hc;
	double Te;
	double k;
	double rho;
	double Cp;


	
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
			
	//std::cout << Lx << " "<< Ly << " " << Lz << " " << M << " " << Phi << " " <<  Hc << " " <<  Te << " " <<  stationnary << " " <<  TFinal << " " << N << " " <<  Mx << " " <<  My << " " << Mz << std::endl; 
	double p =2*(Ly+Lz);
	double S = Ly*Lz;
	// debut de la modelistaion demandé :
	double *x;
	// di8scretisation:
	double h = Lx/M;
	double xi[M];
	for(int i =0; i <M; i++)
		xi[i] = i*h;
	//std::cout << "h = " << h; 
	
	// on stocke les variable qui ne sont pas donnée dans simu
	
	// on prepare a,b,c et F
	double ai[M-1];
	double bi[M];
	double ci[M-1];
	double F[M];
	// on initie les valeurs particulieres de a,b,c,F
	bi[0] = k/h;
	bi[M-1] = k/h;
	ci[0] = -k/h;
	ai[M-2] =-k/h;
	F[0] = Phi;
	F[M-1] = 0;
	// on initie le reste de a,b,c,F
	for (int i= 1; i <M-1;i++){
		ai[i-1] = -k/(h*h);
		bi[i] = 2*k/(h*h) + Hc*p/S ;
		ci[i] = -k/(h*h);
		F[i] = Hc*p*Te/S;}
		
	tridiag resultat(bi,ci,ai,M);
	//resultat.print();
	//~ std::cout << "F = \n" ;
	//~ for (int i = 0 ; i < M ; i++) 
		//~ std::cout << F[i] <<  " " ;
	 x = resultat.resolution_LU(F);
		
		
	std::ostringstream list_file; 
	list_file << "a_b_c_avec_M_" << M << "_liste.txt";
	
	std::ofstream ofile(list_file.str());
	ofile << "i" << " " << "a" << "           " << "b" << "           "  << "c"<< "           "  << "F" << "           "   << "\n";
	for ( int i = 0 ; i < M-1 ; i++){
		ofile << std::setprecision(10) << i << " " << ai[i] << " "  << bi[i] << "  "<<  ci[i] <<  " " << F[i] << "\n"; 
	}
	ofile.close();
	
	double a = Hc*p/(k*S);
	double x_exact[M];
	for (int i = 0; i <M ; i++){
	double Texac = Te + Phi/k * (cosh(pow(a,0.5)*Lx))/(pow(a,0.5) * sinh(pow(a,0.5)*Lx)) * (cosh(pow(a,0.5)*(Lx-xi[i])))/cosh(pow(a,0.5)*Lx) ;
		x_exact[i] = Texac;}
	
	std::ostringstream iresultat;
	iresultat << "resultat_avec_M_" << M<<".csv";
	std::ofstream ofile2(iresultat.str());
	ofile2  << "x_num" << ","<< "x_exact"<<"\n" ; 
	for ( int i = 0 ; i < M ; i++){
		ofile2 << std::setprecision(10)<<x[i] << "," << x_exact[i]<<"\n"; 	}
	
	ofile2.close();
	


	

	return 0;}
	
	


else{
	std::cout << "donner un nom de fichier valide" ; return 0 ;}

}
 std::cout << "donner un nom de fichier " ;return  0;
}

