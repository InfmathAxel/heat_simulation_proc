
class tridiag{
public:
	double *diag,*diagup,*diaglow;
	int n; // taille de diag, diagup et diaglow ont une taille n-1 / correspond aussi au nombre de point discrétisé , n-1 au nombre d'intervalle


tridiag(double *d,double *dup, double *dlw,int taille){
		n = taille;
		diag = new double[n];
		diagup = new double[n-1];
		diaglow = new double[n-1];
	for(int i= 0 ; i < n-1 ; i++){
		
			diag[i] = d[i];
			diagup[i] = dup[i];
			diaglow[i] = dlw[i];
	}
	diag[n-1] = d[n-1];}
	


void print(){ // permet d'afficher les matrices tridiag
	for (int i =0;i <n; i++){
		for (int j = 0;j< n ; j++){
			if ( i-1<= j and j <= i+1){
				if (i == 0 ){
					std::cout << diag[i] << " " << diagup[i] << " " ;
					j++;}
			else if (i == n-1){
				std::cout << diaglow[i-1] << " " << diag[i];
				j++;}
			else {
				std::cout << diaglow[i-1] << " " << diag[i] << " " << diagup[i]  << " " ;
				j++;j++;
			}}
			
			else 
				std::cout << 0  << " " ;
			}
			std::cout << "\n";
			
		}}
	
	

double* resolution_LU( double *F){ // résolution au Modèle Stationnaire .
	double *L_diagup = new double[n-1];
	double *L_diaglow = new double[n-1];
	double *L_diag = new double[n];   // b étoile 
	
	double *U_diagup = new double[n-1]; // c étoile 
	double *U_diaglow = new double[n-1];
	double *U_diag = new double[n];
	
	
	
	
	for(int i = 0; i < n-1;i++){
		// les diagonals de L et U que l'on connait déjà
		L_diagup[i] = 0;
		L_diaglow[i] = diaglow[i];
		U_diaglow[i] = 0;
		U_diag[i] = 1;
		
		// les diagonals de L et U que l'ont doit calculer
		if (i == 0){
			L_diag[0] = diag[0];
			U_diagup[0] = diagup[0]/L_diag[0];}
		else {
			L_diag[i] = diag[i] -diaglow[i-1]*U_diagup[i-1];
			U_diagup[i] = diagup[i]/L_diag[i];
			 }}
		//les derniers element de la diag U et L qui ne sont pas calculés dans la boucle
		L_diag[n-1] = diag[n-1] - diaglow[n-2]*U_diagup[n-2];
		U_diag[n-1] = 1 ;

tridiag L(L_diag,L_diagup,L_diaglow,n);
tridiag U(U_diag,U_diagup,U_diaglow, n);

// resolution de LY = F
double * Y = new double[n];
// rappel b etoile = L_diag , c etoile = U_diagup , a = L_diaglow
Y[0] = F[0]/L_diag[0];

for (int i = 1 ; i < n ; i++){
		Y[i] = (F[i] - L_diaglow[i-1]*Y[i-1])/L_diag[i];}

// resolution de UX = Y		
		
double *X = new double[n];
X[n-1] = Y[n-1];

for(int i = n-2; i>= 0; i--){
		X[i] = Y[i]-U_diagup[i]*X[i+1]; 
}
	

return X;}	

~tridiag()
{delete [] diag ; delete [] diagup; delete [] diaglow;}		
};
