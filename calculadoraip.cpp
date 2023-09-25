#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <math.h>
using namespace std;

int obtenerOctetosIP(string ip, vector<int> &octetosIP) {		
	stringstream sip(ip);								
	string temp;
	octetosIP.clear();									
	vector<bool> IpRango;
	while (getline(sip,temp,'.'))						
		octetosIP.push_back(atoi(temp.c_str()));			
	if (octetosIP.size() == 4) {
		for(int i = 0; i < octetosIP.size(); i++){
			if (octetosIP[i] >= 0 && octetosIP[i] <= 255)
				IpRango.push_back(true);
			else
				IpRango.push_back(false);
		}
		if (IpRango[0]==true&&IpRango[1]==true&&IpRango[2]==true&&IpRango[3]==true){
			return 0;
		}else{
			cout << endl << "Solo debe haber 255 bits por octeto. Porfavor introduzca denuevo la IP." << endl << endl;
			return 1;
		}
	}else{
		cout << endl << "Porfavor introduzca sus octetos con el punto." << endl << endl;
		return 1;
	}
}




int obtenerOctetosMascara(string mascara,  vector<int> &octetosMascara) {
	stringstream smascara(mascara);
	string temp;
	octetosMascara.clear();		
	vector<bool> mascaraRango;
	while (getline(smascara,temp,'.'))
		octetosMascara.push_back(atoi(temp.c_str()));
	if (octetosMascara.size() == 4){
		for(int i = 0; i < octetosMascara.size(); i++){
			if (octetosMascara[i] == 0 || octetosMascara[i] == 128 || octetosMascara[i] == 192 || octetosMascara[i] == 224 || octetosMascara[i] == 240 || octetosMascara[i] == 248 || octetosMascara[i] == 252 || octetosMascara[i] == 254 || octetosMascara[i] == 255)
				mascaraRango.push_back(true);
			else
				mascaraRango.push_back(false);
		}
		if(mascaraRango[0]==true&&mascaraRango[1]==true&&mascaraRango[2]==true&&mascaraRango[3]==true){
			return 0;
		}else{
			cout << endl << "La mascara de subred solo usa 2^[0-7]. Porfavor re introduzca la mascara." << endl << endl;
			return 1;
		}
	}else{
		cout << endl << "Porfavor introduzca sus octetos con el punto." << endl << endl;
		return 1;
	}
}




int calcClase(vector<int> &octetosIP) {
	if (octetosIP[0] == 10) {
		return 1;	// Direccion de clase A privada //
	}else if (octetosIP[0] == 172 && octetosIP[1] >= 16 && octetosIP[1] <= 31) {
		return 2;	// Direccion de clase B privada //
	}else if (octetosIP[0] == 192 && octetosIP[1] == 168) {
		return 3;	// Direccion de clase C privada //
	}else if (octetosIP[0] == 127) {
		return 4;	// Direccion reservada Loopback //
	}else if (octetosIP[0] >= 0 && octetosIP[0] < 127) {
		return 5;
	}else if (octetosIP[0] > 127 && octetosIP[0] < 192) {
		return 6;
	}else if (octetosIP[0] > 191 && octetosIP[0] < 224) {
		return 7;
	}else if (octetosIP[0] > 223 && octetosIP[0] < 240) {
		return 8;
	}else if (octetosIP[0] > 239 && octetosIP[0] <= 255) {
		return 9;
	}else{
		return 0;	// Fuera de rango //
	}
}




// Determinar forma binaria /--
int obtenerBits(vector<int> &octetosIP, vector<int> &octetosMascara, vector<int> &octetosIPBits, vector<int> &octetosMascaraBits){

	// Obtener representacion binaria de la IP // 
cout << "------------------------------------------" << endl;
cout << "///////// Representacion Binaria //////////" << endl;
cout << "------------------------------------------" << endl;
	for (int j=0; j < octetosIP.size(); j++)
    {
		if (j>0)
			cout << ".";

        int mascara = 128;
        while (mascara)
        {
            octetosIPBits.push_back((octetosIP[j] & mascara) != 0);
			cout << ((octetosIP[j] & mascara) != 0);
            mascara >>= 1;
        }
    }
	cout << "  : Direccion IP" << endl;

	// Obtener representacion binaria de la subred // 
	for (int j=0; j < octetosMascara.size(); j++)
    {
		if (j>0)
			cout << ".";
        int mascara = 128;
        while (mascara)
        {
            octetosMascaraBits.push_back((octetosMascara[j] & mascara) != 0);
			cout << ((octetosMascara[j] & mascara) != 0);
            mascara >>= 1;
        }
    }
	cout << "  : Mascara de subred" << endl;
	cout << "-----------------------------------------" << endl;

return 0;
}



// Se utiliza una AND logica de la IP y la mascara de subred para generar el network ID //
vector<int> obtenerNetID(vector<int> &octetosIPBits, vector<int> &octetosMascaraBits){
	vector<int> netID;
    for (int j=0; j < octetosIPBits.size(); j++)
    {
        if ((j > 0) && (j%8 == 0))
            cout << ".";

		netID.push_back(octetosIPBits[j] & octetosMascaraBits[j]);
    }
return netID;
}


// Regresar de binario a decimal
string aString(vector<int> octetos){
	ostringstream octStrm;

	for(int j = 0; j < octetos.size(); j++)
	{
		if (j>0)
			octStrm << '.';

		octStrm << octetos[j];
	}
	
	return octStrm.str();
}


// Regresar de binario a decimal
vector<int> aDecimal(vector<int> octetos, vector<int> &decimales){
	stringstream octStrm;
	decimales.clear();
	for(int j = 0; j < octetos.size(); j++)
	{
		if (j>0)
			octStrm << '.';

		octStrm << octetos[j];
	}

	string temp;
	while (getline(octStrm, temp, '.'))
		decimales.push_back(atoi(temp.c_str()));
	
	return decimales;
}

// Obtener el incremento //
int obtenerIncremento(vector<int> decimalMascara, vector<int> decimalNetID){
	int incremento = 0;
	for (int i=0; i<decimalMascara.size(); i++){
		if (decimalMascara[i] == 255){
			incremento = 1;
		}else if(decimalMascara[i] == 254){
			incremento = 2;
			break;
		}else if(decimalMascara[i] == 252){
			incremento = 4;
			break;
		}else if(decimalMascara[i] == 248){
			incremento = 8;
			break;
		}else if(decimalMascara[i] == 240){
			incremento = 16;
			break;
		}else if(decimalMascara[i] == 224){
			incremento = 32;
			break;
		}else if(decimalMascara[i] == 192){
			incremento = 64;
			break;
		}else if(decimalMascara[i] == 128){
			incremento = 128;
			break;
		}
	}
return incremento;
}

// obtener el rango del network ID
vector<int> obtenerNetIDRango(vector<int> &decimalNetID, int &netInc, vector<int> &decimalMascara) {
	vector<int> netIDFin;
	for (int i=0; i<decimalNetID.size(); i++){
		if (decimalMascara[i] == 255){
			netIDFin.push_back(decimalNetID[i]);
		}else if (decimalMascara[i] < 255 && decimalMascara[i] > 0){
			netIDFin.push_back( (decimalNetID[i] + netInc) - 1 );
		}else{
			netIDFin.push_back(255);
		}
	}
	return netIDFin;
}



// Obtener las subredes
int obtenerSubredes(vector<int> &decimalMascara, int &ipClase, vector<int> &subClaseMascara){
	int netBits = 0;
	subClaseMascara.clear();
		if (ipClase==1){
			subClaseMascara.push_back(255);
			subClaseMascara.push_back(0);
			subClaseMascara.push_back(0);
			subClaseMascara.push_back(0);
		}else if(ipClase==2){
			subClaseMascara.push_back(255);
			subClaseMascara.push_back(255);
			subClaseMascara.push_back(0);
			subClaseMascara.push_back(0);
		}else if(ipClase==3){
			subClaseMascara.push_back(255);
			subClaseMascara.push_back(255);
			subClaseMascara.push_back(255);
			subClaseMascara.push_back(0);
		}else if(ipClase==4 || ipClase==5){
			subClaseMascara.push_back(decimalMascara[0]);
			subClaseMascara.push_back(decimalMascara[1]);
			subClaseMascara.push_back(decimalMascara[2]);
			subClaseMascara.push_back(decimalMascara[3]);
		}

	for (int i=0; i<decimalMascara.size(); i++){
		if (decimalMascara[i] != subClaseMascara[i]){
			if (decimalMascara[i] == 255){
				netBits += 8;
				continue;
			}else if (decimalMascara[i] == 254){
				netBits += 7;
				continue;
			}else if (decimalMascara[i] == 252){
				netBits += 6;
				continue;
			}else if (decimalMascara[i] == 248){
				netBits += 5;
				continue;
			}else if (decimalMascara[i] == 240){
				netBits += 4;
				continue;
			}else if (decimalMascara[i] == 224){
				netBits += 3;
				continue;
			}else if (decimalMascara[i] == 192){
				netBits += 2;
				continue;
			}else if (decimalMascara[i] == 128){
				netBits += 1;
				continue;
			}else if (decimalMascara[i] == 0){
				netBits += 0;
				continue;
			}else{
				netBits += 0;
			}
		}
	}
	int subredes = pow(2.0,netBits);
	return subredes;
}



// Obtener los hosts por subred
int obtenerHostsPorSubred(vector<int> &decimalMascara){
	int hostBits = 0;
	for (int i=0; i<decimalMascara.size(); i++){
		if (decimalMascara[i] == 255){
			hostBits += 0;
			continue;
		}else if (decimalMascara[i] == 254){
			hostBits += 1;
			continue;
		}else if (decimalMascara[i] == 252){
			hostBits += 2;
			continue;
		}else if (decimalMascara[i] == 248){
			hostBits += 3;
			continue;
		}else if (decimalMascara[i] == 240){
			hostBits += 4;
			continue;
		}else if (decimalMascara[i] == 224){
			hostBits += 5;
			continue;
		}else if (decimalMascara[i] == 192){
			hostBits += 6;
			continue;
		}else if (decimalMascara[i] == 128){
			hostBits += 7;
			continue;
		}else if (decimalMascara[i] == 0){
			hostBits += 8;
			continue;
		}else{
			hostBits = 0;
			break;
		}
	}
	int hostsPorSubred = pow(2.0,hostBits)-2;
	return hostsPorSubred;
}


int main() {

// Imprimir detalles dada la direccion IP y la mascara //
char resp = 'y';
while (resp == 'y') {
	cout << " //// -- Calculadora de subredes IPv4 -- \\\\\\\\" << endl;
	cout << "||||  ----- Amezquita Lopez Jose Antonio ----- ||||" << endl;
	cout << " \\\\\\\\ ----- Grupo 5CV2 ---- ////" << endl;
	cout << endl << endl;

		// Obtener octetos de la direccion IP //
		string ip;
		vector<int> octetosIP;
		while (obtenerOctetosIP(ip, octetosIP) == 1) {
		cout << "Ingresa una direccion IPv4 -> ";
		(getline(cin, ip));		
		}

		// Obtener octetos de la mascara de subred //
		string mascara;
		vector<int> octetosMascara;
		while (obtenerOctetosMascara(mascara, octetosMascara) == 1) {
		cout << endl << "Introduzca la mascara para " << ip << " -> ";
		(getline(cin, mascara));	
		}
		cout << endl << endl << endl << endl << endl;

		// Imprimir la direccion IP y mascara iniciales //
		vector<int> decimales;
		cout << "//////////////////////////////////////////" << endl;
		cout << "/// Direccion IP: " << aString(octetosIP) << endl;
		vector<int> decimalMascara = aDecimal(octetosMascara, decimales);
		cout << "/// Mascara de subred: " << aString(octetosMascara) << endl;
		cout << "//////////////////////////////////////////" << endl << endl;

		// Imprimir la representacion binaria //
		vector<int> octetosIPBits;
		vector<int> octetosMascaraBits;
		obtenerBits(octetosIP, octetosMascara, octetosIPBits, octetosMascaraBits);
		vector<int> netID = obtenerNetID(octetosIP, octetosMascara);
		vector<int> decimalNetID = aDecimal(netID, decimales);
		int netInc = obtenerIncremento(decimalMascara, decimalNetID);
		cout << endl;

		// Imprimir la clase de la IP
			cout << "------------------------------------------" << endl;
			cout << "//////////// Informacion sobre la clase ///////////" << endl;
			cout << "------------------------------------------" << endl;
			int claseResult = calcClase(octetosIP);
			int ipClase = 0;
			switch (claseResult){
				case 1:
					cout << "Clase de la IP: Clase Privada 'A' " << endl;
					ipClase = 1;
					break;
				case 2:
					cout << "Clase de la IP: Clase Privada 'B' " << endl;
					ipClase = 2;
					break;
				case 3:
					cout << "Clase de la IP: Clase Privada 'C' " << endl;
					ipClase = 3;
					break;
				case 4:
					cout << "Clase de la IP: Direccion reservada Loopback" << endl;
					ipClase = 1;
					break;
				case 5: 
					cout << "Clase de la IP: A" << endl;
					ipClase = 1;
					break;
				case 6:
					cout << "Clase de la IP: B" << endl;
					ipClase = 2;
					break;
				case 7:
					cout << "Clase de la IP: C" << endl;
					ipClase = 3;
					break;
				case 8:
					cout << "Clase de la IP: D" << endl;
					ipClase = 4;
					cout << "!! Esta es una direccion clase D reservada para multicast" << endl;
					break;
				case 9:
					cout << "Clase de la IP: E" << endl;
					ipClase = 5;
					cout << "!! Esta es una direccion clase E reservada para multicast" << endl;
					break;
				default :
					cout << "No esta dentro del rango" << endl;
					break;
			}
		vector<int> subClaseMascara;
		obtenerSubredes(decimalMascara, ipClase, subClaseMascara);
		cout << "Mascara de subred de clase predeterminada: " << aString(subClaseMascara) << endl;
		cout << "-----------------------------------------" << endl << endl;

		// Imprimir detalles de las subredes //
		cout << "------------------------------------------" << endl;
		cout << "///////////// Detalles de subred /////////////" << endl;
		cout << "------------------------------------------" << endl;
		vector<int> netIDRango = obtenerNetIDRango(decimalNetID, netInc, decimalMascara);
		cout << "Network ID:            -           Broadcast ID: " << endl;
			cout << "-------------------------------------------------" << endl;
			cout << aString(netID) << " - [ hosts usables ] - ";
		cout << aString(netIDRango) << endl << endl;
		cout << "Incremento de subred: " << obtenerIncremento(decimalMascara, decimalNetID) << endl;
		cout << "Numero de subredes: " << obtenerSubredes(decimalMascara, ipClase, subClaseMascara) << endl;
		cout << "Hosts usables por subred: " << obtenerHostsPorSubred(decimalMascara) << endl;
		cout << "-----------------------------------------" << endl << endl;

		cout << "Quisieras introducir otra direccion para obtener subredes? (s o n): ";
		cin >> resp;
		cout << endl << endl << endl << endl;
}
	return 0;
}