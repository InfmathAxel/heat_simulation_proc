#include <cmath>

#include <fstream>
#include <iostream>
#include <iomanip>
#include "tridiag.hpp"
// me permet de regarder si je dois sauvergader la temperature a ce temps i .
bool check_if_in_list(int i, int* tn , int n){
	for (int k=0 ; k < n ; k ++) {
		if (i == tn[k])
			return true;}
	return false;}

int main(int argc, char **argv)
{	// on initie toutes les variables du fichier simu.Txt
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
	int Mx,My,Mz;
	int n_t;
	int *temps_donne;
	
	if (argc >= 2) {
		std::ifstream ifile(argv[1]);
	
	
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
			ifile >> c >> N ;
			ifile >> c >>Mx >> c >> My>> c >> Mz; // ici pour pouvoir utiliser le meme txt dans tout les programmes;
			ifile >> c >> n_t;
			temps_donne = new int[n_t];
			
			ifile >> c ;
			
			for (int i =0; i < n_t; i++){
				ifile >> temps_donne[i];
				std::cout << temps_donne[i]<<   " " ;}
	// initiation des variable qui ne sont pas dans simu.Txt
	double p = 2*(Ly+Lz);		
	double h = Lx/M;
	double S = Ly*Lz;
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
	for(int i = 1 ; i < M-1 ; i++){
		ai[i-1] = -k/(h*h);
		ci[i] = - k /(h*h);
		bi[i] = 2*k/(h*h) + (Hc*p)/S + (rho*Cp)/delta_T ; 
		F[i] = T[i]*(rho*Cp/delta_T + Hc*p/S); }
	
	
	// on initie A et Ti_1
	tridiag resultat(bi,ci,ai,M);
	double * Ti_n;
	Ti_n = resultat.resolution_LU(F);
	
	if(check_if_in_list(0,temps_donne,n_t) == true){
	std::ostringstream res1;
	res1 << "resultat_avec_M_" << M<<"_t0et_N_600.csv";
	std::ofstream ofile3(res1.str());
	ofile3  << "x"  << ","<< "Ti"<<"\n" ; 
	
	for ( int i = 0 ; i < M ; i++){
		ofile3 << std::setprecision(10)<< i << "," << Ti_n[i]<<"\n"; 	}
	ofile3.close();	}
	
	// on boucle sur N pour actualliser N fois la temperature en chaque point, et on boucle M fois pour mettre a jour le vecteur 
	// second membre F dans AX= F 
	for (int i = 1 ; i < N ; i ++){
		for (int j = 0 ; j < M ; j++){
			Ti_n[j] = Ti_n[j]*rho*Cp/delta_T + Hc*p/S * T[j];}
		Ti_n[0] = Phi;
		Ti_n[M-1] = 0;
		Ti_n = resultat.resolution_LU(Ti_n);
		if (check_if_in_list(i,temps_donne,n_t) == true ){
			std::ostringstream res;
				res << "resultat_avec_M_"<< M<<"t_"<<i <<"_et_N_"<<N << ".csv";
				std::ofstream ofile(res.str());
				ofile  << "x"  << ","<< "Ti"<<"\n" ; 
				for ( int k = 0 ; k < M ; k++){
			ofile << std::setprecision(10)<< k << "," << Ti_n[k]<<"\n"; 	}
		ofile.close();	}
		
	}
	
	// ou sinon avec le phi qui passe de 0 a phi tout les 30s  : 
	Ti_n = new double[M];
	Ti_n = resultat.resolution_LU(F);
	
	if(check_if_in_list(0,temps_donne,n_t) == true){
	std::ostringstream res1;
	res1 << "resultat_avec_M_" << M<<"_t0et_N_600.csv";
	std::ofstream ofile3(res1.str());
	ofile3  << "x"  << ","<< "Ti"<<"\n" ; 
	
	for ( int i = 0 ; i < M ; i++){
		ofile3 << std::setprecision(10)<< i << "," << Ti_n[i]<<"\n"; 	}
	ofile3.close();	}
	
	
	double T_phi_variant_0[N];
	double T_phi_variant_3000[N];
	double T_phi_variant_1500[N];
	T_phi_variant_0[0] = Ti_n[0];
	T_phi_variant_3000[0] = Ti_n[3000];
	T_phi_variant_1500[0] = Ti_n[1500];
	
	for (int i = 1 ; i < N ; i ++){
		for (int j = 0 ; j < M ; j++){
			Ti_n[j] = Ti_n[j]*rho*Cp/delta_T + Hc*p/S * T[j];}
		int quotient = i/30;
	
		Ti_n[0] = Phi;
		if ( quotient % 2 == 1) {
			Ti_n[0] = 0;}
		Ti_n[M-1] = 0;
		Ti_n = resultat.resolution_LU(Ti_n);
		T_phi_variant_0[i] = Ti_n[0];
		T_phi_variant_3000[i] = Ti_n[3000];
		T_phi_variant_1500[i]  = Ti_n[1500];
		
		
	// on stocke les températures en certain point a chaque temps t 
	}
	std::ostringstream res2;
	res2 << "resultat_avec_M_" << M<<"_N_"<< N<<"et_phi_variant.csv";
	std::ofstream ofile3(res2.str());
	ofile3  << "t"  << ","<< "x0" << ","  << "x1500"<<","<< "x3000 " <<"\n" ; 
	for (int j = 0 ;  j< N ; j++){
		ofile3 << delta_T*j << "," << T_phi_variant_0[j]  << "," << T_phi_variant_1500[j]  << "," << T_phi_variant_3000[j] <<"\n";
	}
	
	return 0;}}
	
	
	
	else {std::cout << "donner un nom de fichier"; return 0 ;
		}
	
	
	std::cout << "donner un nom de fichier"; return 0 ;

}
