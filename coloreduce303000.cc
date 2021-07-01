/** \author MATTHIAS_KOCKISCH
 *  \date	10 dec 2018
 */
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
using namespace std;

//TYPEDEF
typedef vector<vector<array<int,3> > > Image;
typedef vector<vector<int> > ImageS;

//INPUT
int cin_nbR();
vector<array<int,3> > cin_cf(int nbR);
vector<double> cin_seuil(int nbR);
int cin_nbF();
Image cin_image(int nbL,int nbC,int MAX);

//SEUILLAGE
ImageS seuil_images(int nbL,int nbC,int MAX,int nbR,Image image0,vector<double> seuil);

//FILTRAGE
ImageS prefiltre(int nbF,int nbL,int nbC,ImageS images0, ImageS images1);
int filtre(array<int,8> tf);
ImageS bords_noirs(ImageS images0, int nbL, int nbC);

//SORTIES
void cout_RVB(int nbL, int nbC, ImageS images0, vector<array<int,3> > cf);

//ERROR
void error_nbR(int nbR);
void error_color(int id);
void error_threshold(double invalid_val);
void error_nb_filter(int nb_filter);

//MAIN
int main() {
	
	//INPUT
	int nbR(cin_nbR());
	vector<array<int,3> > cf(nbR+1);
	cf=cin_cf(nbR);
	vector<double> seuil(nbR+1);
	seuil=cin_seuil(nbR);
	int nbF(cin_nbF());
	char P3[2];
	int nbC, nbL, MAX;
	cin >> P3 >> nbC >> nbL >> MAX;
	Image image0(nbL, vector<array<int,3> >(nbC));
	image0=cin_image(nbL, nbC, MAX);
	
	//SEUILLAGE
	ImageS images0(nbL, vector<int>(nbC));
	images0=seuil_images(nbL, nbC, MAX, nbR, image0, seuil);
	
	//FILTRAGE
	ImageS images1(nbL, vector<int>(nbC));
	images0=prefiltre(nbF, nbL, nbC, images0, images1);
	if (nbF>0) images0=bords_noirs(images0, nbL, nbC);
	
	//SORTIES
	cout << P3 << endl << nbC << " " << nbL << endl << MAX << endl;
	cout_RVB(nbL, nbC, images0, cf);
	return 0;
}

//INPUT
int cin_nbR() {
	int nbR;
	cin >> nbR;
	if (nbR<2 || nbR>255) {
		error_nbR(nbR);
		exit(0);
	}
	return nbR;
}

vector<array<int,3> > cin_cf(int nbR) {
	vector<array<int,3> > cf(nbR+1);
	for (int i(0); i < nbR; i++) {
		for (int j(0); j < 3; j++) {
			cf[0][j]=0;
			cin >> cf[i+1][j];
			if (cf[i+1][j]<0 || cf[i+1][j]>255) {
				error_color(i+1);
				exit(0);
			}
		}
	}
	return cf;
}

vector<double> cin_seuil(int nbR) {
	vector<double> seuil(nbR+1);
	seuil[0]=0;
	seuil[nbR]=1;
	for (int i(1); i<nbR; i++) {
		cin >> seuil[i];
		if (seuil[i]-seuil[i-1]<0.001 || seuil[i]>1 || seuil[i]<0) {
			error_threshold(seuil[i]);
			exit(0);
		}
	}
	return seuil;
}

int cin_nbF() {
	int nbF;
	cin >> nbF;
	if (nbF<0) {
		error_nb_filter(nbF);
		exit(0);
	}
	return nbF;
}

Image cin_image(int nbL,int nbC,int MAX) {
	Image image0(nbL, vector<array<int,3> >(nbC));
	for (int i(0); i<nbL; i++) {
		for (int j(0); j<nbC; j++) {
			for (int k(0); k<3; k++) {
				cin >> image0[i][j][k];
				if (image0[i][j][k]<0 || image0[i][j][k]>MAX) {
					error_color(image0[i][j][k]);
					exit(0);
				}
			}
		}
	}
	return image0;
}

//SEUILLAGE
ImageS seuil_images(int nbL,int nbC,int MAX,int nbR,Image image0,vector<double> seuil){
	ImageS images0(nbL, vector<int>(nbC));
	for (int i(0); i<nbL; i++) {
		for (int j(0); j<nbC; j++) {
			int c(0), s(0);
			double in(0);
			for (int k(0); k<3; k++) {
				c += pow(image0[i][j][k],2);
			}
			in =sqrt(c/(3*pow(MAX,2)));
			while (in >= seuil[s] && s<nbR) {
				s++;
			}
			images0[i][j] = s;
		}
	}
	return images0;
}

//FILTRAGE
ImageS prefiltre (int nbF,int nbL,int nbC,ImageS images0, ImageS images1){
	images1=images0;
	for (int f(0); f<nbF; f++) {
		for (int i(1); i<nbL-1; i++) {
			for (int j(1); j<nbC-1; j++) {
				array<int,8> tf {images0[i-1][j-1],images0[i-1][j],
					images0[i-1][j+1],images0[i][j-1],images0[i][j+1],
					images0[i+1][j-1],images0[i+1][j],images0[i+1][j+1]};
				images1[i][j]=filtre(tf);
			}
		}

		images0=images1;
	}
	return images0;
}

int filtre(array<int,8> tf) {
	int c(0), d(0);
	do {
		d=0;
		do {
			c++;
			} while (tf[c]==tf[c+1]);
		for (int e(0); e<8; e++) {
			if (tf[c]==tf[e]) {
				d++;
			}
		}
	} while (c<3 && d<6);
	if (d>5) return tf[c];
	else return 0;
}

ImageS bords_noirs(ImageS images0, int nbL, int nbC) {
	for (int i(0); i<nbL; i++) {
		images0[i][0]=0;
		images0[i][nbC-1]=0;
	}
	for (int j(0); j<nbC; j++) {
		images0[0][j]=0;
		images0[nbL-1][j]=0;
	}
	return images0;
}

//SORTIES
void cout_RVB(int nbL, int nbC, ImageS images0, vector<array<int,3> > cf) {
	for (int i(0); i<nbL; i++) {
		for (int j(0); j<nbC; j++) {
			for (int k(0); k<3; k++) {
				cout << cf[images0[i][j]][k] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

//ERROR
void error_nbR(int nbR)
{
	cout << "Invalid number of colors: " << nbR << endl;
}
void error_color(int id)
{
	cout << "Invalid color value " << id << endl;
}
void error_threshold(double invalid_val)
{
	cout << "Invalid threshold value: " << invalid_val << endl;
}
void error_nb_filter(int nb_filter)
{
	cout << "Invalid number of filter: " << nb_filter << endl;
}