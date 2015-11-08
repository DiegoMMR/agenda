// Agenda.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "stdio.h"
#include "string"

using namespace std;
 
char aux1[20];
char aux2[20];

int Op1;
char Op2[1] = { 's' };
char name1[20];
char name2[20];
char name3[20];
char name4[20];
char Tel[20];
char Email[40];
char Op3[1] = { 's' };
string mayus = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string min = "abcdefghijklmnopqrstuvwxyz";

char letras1[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z' };
char letras2[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z' };

struct orden
{
	char nombre1[20];
	char nombre2[20];
	char apellido1[20];
	char apellido2[20];
	char telefono[20];
	char correo[40];
}var;

orden DP[];
int conteo;


//para mandar datos al archivo
ofstream entrada;
ofstream temp;
ifstream salida;


void inicio()
{
	system("cls");
	cout << "BIENVENIDO A SU AGENDA TELEFONICA \n\n" << endl;;

	cout << "1. Ingresar Datos" << endl;
	cout << "2. Consultar Datos" << endl;
	cout << "3. Ordenar Datos" << endl;
	cout << "4. Eliminar contacto" << endl;
	cout << "5. Buscar\n\n" << endl;
	cout << "Ingrese numero de Opcion" << endl;
	cin >> Op1;

	while (Op1 > 5)
	{

		Op1 = 0;
		cout << "\nIngrese un numero valido\n" << endl;
		cin >> Op1;

	}
}

void ingresar_datos()
{
	while (Op3[0] == 's')
	{
		system("cls");
		cout << "\n Ingrese datos Solicitados\n" << endl;
		cout << "Primer Nombre: ";
		cin >> name1;
		cout << "Segundo Nombre: ";
		cin >> name2;
		cout << "Primer Apellido: ";
		cin >> name3;
		cout << "Segundo Apellido: ";
		cin >> name4;
		cout << "Telefono: ";
		cin >> Tel;
		cout << "Email: ";
		cin >> Email;

		cout << endl;


		//abre el archivo para poder meter los datos
		entrada.open("Datos.txt", ios::out | ios::app);

		entrada << name1 << " " << name2 << " " << name3 << " " << name4 << "\n" << Tel << "\n" << Email << "\n\n";

		//lo cierra para que se puedan gardar los cambios
		entrada.close();

		cout << "\n Quiere ingresar mas elementos (s/n): ";
		cin >> Op3[0];

	}
}
void consultar()
{
	system("cls");
	cout << "Todos los numeros en la agenda\n" << endl;

	//esto funciona para abrir el archivo en forma de lectura
	salida.open("Datos.txt", ios::in);

	if (salida.fail())
	{
		cout << "Error al abrir Datos.txt" << endl;
		system("pause");
	}
	else{

		salida >> name1;

		while (!salida.eof())
		{
			salida >> name2 >> name3 >> name4 >> Tel >> Email;
			cout << "Nombre: " << name1 << " " << name2 << " " << name3 << " " << name4 << "\nTelefono: " << Tel << "\nEmail: " << Email << "\n\n";
			cout << "-------------------------------------------------" << endl;
			salida >> name1;

		}
		//se cierra para que no se puedan leer datos que no se desean leer
		salida.close();
	}
}
void ordenar()
{
	system("cls");

	temp.open("temp.txt", ios::out);
	salida.open("Datos.txt", ios::in);

	if (salida.fail())
	{
		cout << "Error al abrir Datos.txt" << endl;
		system("pause");
	}
	else{
		string letra;

		for (int i = 0; i < 25; i++)
		{
			
			salida >> name1;

			while (!salida.eof())
			{

				salida >> name2 >> name3 >> name4 >> Tel >> Email;

				letra = name1;
				

				if (letra.substr(0, 1) == mayus.substr(i, i + 1) || letra.substr(0, 1) == min.substr(i, i + 1))
				{
					temp << name1 << " " << name2 << " " << name3 << " " << name4 << "\n" << Tel << "\n" << Email << "\n\n";
				}

				salida >> name1;

				//cout << letra.substr(0, 1)  << mayus.substr(i, i + 1) << min.substr(i, i + 1) << ", ";
			}

			cout << letra.substr(0, 1);// << mayus.substr(i, i + 1) << min.substr(i, i + 1) << ", ";
		}

		cout << "los archivos se han ordenado" << endl;

		

	}

	temp.close();
	salida.close();


}
void eliminar_contacto()
{
	system("cls");

	temp.open("temp.txt", ios::out);
	salida.open("Datos.txt", ios::in);

	if (salida.fail())
	{
		cout << "Error al abrir Datos.txt" << endl;
		system("pause");
	}
	else{

		cout << "ELIMINAR\n\n";
		cout << "Introduzca el primer nombre de la persona que desea eliminar" << endl;
		cin >> aux1;
		cout << "Introduzca el primer apellido de la persona que desa eliminar" << endl;
		cin >> aux2;

		salida >> name1;

		while (!salida.eof())
		{
			salida >> name2 >> name3 >> name4 >> Tel >> Email;

			if (strcmp(aux1, name1) == 0 && strcmp(aux2, name3) == 0)
			{
				cout << "El registro ha sido elimidado" << endl;
			}
			else
			{
				temp << name1 << " " << name2 << " " << name3 << " " << name4 << "\n" << Tel << "\n" << Email << "\n\n";
			}

			salida >> name1;

		}

		temp.close();
		salida.close();

		remove("Datos.txt");
		rename("temp.txt", "Datos.txt");
	}
}
void buscar()
{

	system("cls");

	salida.open("Datos.txt", ios::in);

	if (salida.fail())
	{
		cout << "Error al abrir Datos.txt" << endl;
		system("pause");
	}
	else{
		int decision = 0;
		system("cls");

		cout << "BUSCAR\n\n" << endl;
		cout << "1. Por nombre" << endl;
		cout << "2. por apellido" << endl;
		cout << "3. Por nombre y apellido\n\n" << endl;

		cout << "ingrese numero de opcion: ";
		cin >> decision;

		while (decision > 3){
			cout << "ingrese un valor valido" << endl;
			cin >> decision;
		}

		system("cls");

		switch (decision)
		{
		case 1:
			cout << "BUSCAR\n\n" << endl;
			cout << "Introduzca el nombre que desea buscar" << endl;
			cin >> aux1;
			break;
		case 2:
			cout << "BUSCAR\n\n" << endl;
			cout << "Introduzca el apellido que desa buscar" << endl;
			cin >> aux2;
			break;
		case 3:
			cout << "BUSCAR\n\n" << endl;
			cout << "Introduzca el nombre que desea buscar" << endl;
			cin >> aux1;
			cout << "Introduzca el apellido que desa buscar" << endl;
			cin >> aux2;
			break;
		}


		salida >> name1;

		system("cls");

		while (!salida.eof())
		{
			salida >> name2 >> name3 >> name4 >> Tel >> Email;

			if (strcmp(aux1, name1) == 0 || strcmp(aux1, name2) == 0 || strcmp(aux2, name3) == 0 || strcmp(aux2, name4) == 0)
			{
				cout << "Nombre: " << name1 << " " << name2 << " " << name3 << " " << name4 << "\nTelefono: " << Tel << "\nEmail: " << Email << "\n\n";
				cout << "----------------------------------------" << endl;
			}


			salida >> name1;

		}
		system("pause");

	}
	salida.close();
}


void main()
{
		
	while (Op2[0] == 's')

	{
		inicio();
		
		switch (Op1)
		{
		case 1:
			ingresar_datos();
			break;
		case 2:
			consultar();
			break;
		case 3:
			ordenar();
			break;
		case 4:
			eliminar_contacto();
			break;
		case 5:
			buscar();
			break;
		}


		cout << "\n\nQuiere regresar al menu (s/n): ";
		cin >> Op2[0];
	}

	system("PAUSE");
}