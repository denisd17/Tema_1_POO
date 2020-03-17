#include <iostream>

using namespace std;

class Nod
{
	int info;
	Nod *next;
public:
	//CONSTRUCTOR
	Nod()
	{
		info = 0;
		next = NULL;
	}
	//CONSTRUCTOR PARAMETRIZAT
	Nod(int info, Nod *next)
	{
		this->info = info;
		this->next = next;
	}
	//DESTRUCTOR
	~Nod()
	{
		info = 0;
		next = NULL;
	}
	//SETTER PENTRU INFO
	void set_info(int info)
	{
		this->info = info;
	}
	//GETTER PENTRU INFO
	int get_info()
	{
		return info;
	}
	//SETTER PENTRU NEXT
	void set_next(Nod *next)
	{
		this->next = next;
	}
	//GETTER PENTRU NEXT
	Nod* get_next()
	{
		return next;
	}
};

class Multime_dinamic
{
	Nod *left;
	Nod *right;

public:
	//CONSTRUCTOR
	Multime_dinamic()
	{
		left = NULL;
		right = NULL;
	}
	//DESTRUCTOR
	~Multime_dinamic()
	{
		Nod *temp;

		while (left != NULL)
		{
			temp = left->get_next();
			delete left;
			left = temp;
		}
		left = right = NULL;
	}
	//CONSTRUCTOR DE COPIERE
	Multime_dinamic(const Multime_dinamic &m)
	{
		left = NULL;
		right = NULL;
		Nod *temp = m.left;
		int data;
		while (temp != NULL)
		{
			data = temp->get_info();
			this->adauga_nod(data);
			temp = temp->get_next();
		}
	}
	//METODA PENTRU ADAUGAREA UNUI NOD IN LISTA
	void adauga_nod(int info)
	{
		Nod *nod_nou = new Nod(info, NULL);
		if (left == NULL)
		{
			left = nod_nou;
			right = nod_nou;
		}
		else
		{
			right->set_next(nod_nou);
			right = nod_nou;
		}
	}
	//METODA PENTRU ADAUGAREA A N NODURI IN LISTA SI AFISAREA LISTEI
	void adauga_n_noduri(int n)
	{
		int i, data;
		for (i = 0; i < n; i++)
		{
			cin >> data;
			this->adauga_nod(data);
		}
		this->display_list();

	}
	//METODA CE AFISEAZA TOATE ELEMENTELE LISTEI
	void display_list()const
	{
		//cout<<"display";
		Nod *temp = left;
		int to_display;

		while (temp != NULL)
		{
			to_display = temp->get_info();
			cout << to_display << " ";
			temp = temp->get_next();
		}
		cout << endl;
	}
	//METODA CE TRANSFORMA O LISTA INTR-O MULTIME
	//ELIMINA ELEMENTELE DUPLICATE DIN LISTA
	void transforma_multime()
	{
		int info, info_curent;
		Nod *curent = left, *anterior, *urmator;
		/*"urmator" = nodurile aflate dupa nodul "curent"
		"anterior" = pointer la nodul aflat imediat inaintea nodului "urmator"
		Parcurgem lista si verificam pentru fiecare numar daca se afla si in alte noduri ale listei.
		In cazul in care acesta se afla si in alte noduri, vom sterge nodul respectiv.*/
		while (curent != NULL)
		{
			info_curent = curent->get_info();
			anterior = curent;
			urmator = curent->get_next();


			while (urmator != NULL)
			{
				info = urmator->get_info();

				if (info == info_curent)
				{
					if (urmator == right)
					{
						anterior->set_next(NULL);
						urmator->set_next(NULL);
						right = anterior;
					}
					else
					{
						anterior->set_next(urmator->get_next());
						urmator->set_next(NULL);
					}
					urmator = anterior->get_next();
				}
				else
				{
					anterior = urmator;
					urmator = urmator->get_next();
				}
			}
			curent = curent->get_next();
		}
	}
	//FUNCTIE CE VERIFICA DACA UN ELEMENT DAT CA SI PARAMETRU SE AFLA SAU NU IN LISTA
	int in_set(int info)const
	{
		Nod *temp = left;
		int data;

		while (temp != NULL)
		{
			data = temp->get_info();
			if (data == info)
				return 1;
			temp = temp->get_next();
		}
		return 0;
	}
	//SUPRAINCARCARE OPERATOR EGAL
	Multime_dinamic& operator =(const Multime_dinamic &m)
	{
		if (this != &m)
		{
			this->~Multime_dinamic();
			Nod *temp = m.left;
			int data;
			while (temp != NULL)
			{
				data = temp->get_info();
				this->adauga_nod(data);
				temp = temp->get_next();
			}
		}
		return *this;
	}
	//SUPRAINCARCARE OPERATOR + PENTRU REUNIUNE
	Multime_dinamic operator +(const Multime_dinamic &m)
	{
		Multime_dinamic rezultat;
		int data;
		Nod *temp;
		temp = left;
		while (temp != NULL)
		{
			data = temp->get_info();
			rezultat.adauga_nod(data);
			temp = temp->get_next();
		}
		temp = m.left;
		while (temp != NULL)
		{
			data = temp->get_info();
			rezultat.adauga_nod(data);
			temp = temp->get_next();
		}
		rezultat.transforma_multime();
		return rezultat;
	}
	//SUPRAINCARCARE OPERATOR * PENTRU INTERSECTIE
	Multime_dinamic operator *(const Multime_dinamic &m)
	{
		Multime_dinamic rezultat;
		int info;
		Nod *temp = left;
		while (temp != NULL)
		{
			info = temp->get_info();

			if (m.in_set(info) == 1)
				rezultat.adauga_nod(info);

			temp = temp->get_next();
		}
		rezultat.transforma_multime();
		return rezultat;
	}
	//SUPRAINCARCARE OPERATOR - PENTRU DIFERENTA
	Multime_dinamic operator -(const Multime_dinamic &m)
	{
		Multime_dinamic rezultat;
		Nod *temp = left;
		int data;

		while (temp != NULL)
		{
			data = temp->get_info();
			if (m.in_set(data) == 0)
				rezultat.adauga_nod(data);
			temp = temp->get_next();
		}
		rezultat.transforma_multime();
		return rezultat;
	}
	//FUNCTIE FRIEND PENTRU SUPRAINCARCAREA OPERATORULUI <<
	friend ostream& operator<<(ostream &out, const Multime_dinamic &m);

	friend istream& operator>>(istream &in, Multime_dinamic &m);
};
//SUPRAINCARCAREA OPERATORULUI <<
ostream& operator<<(ostream &out, const Multime_dinamic &m)
{
	Nod *temp = m.left;
	int to_display;

	while (temp != NULL)
	{
		to_display = temp->get_info();
		out << to_display << " ";
		temp = temp->get_next();
	}
	return out;
}
//DE INTREBAT
//SUPRAINCARCAREA OPERATORULUI >>
istream& operator>>(istream &in, Multime_dinamic &m)
{
	int n,i,info;
	m.~Multime_dinamic();
	cout << "Introduceti numarul de elemente";
	in >> n;
	for (i = 0; i < n; i++)
	{
		in >> info;
		m.adauga_nod(info);
	}


	return in;
}
int main()
{
	int n;
	Multime_dinamic m, m1, m2;
	m1.adauga_nod(1);
	m1.adauga_nod(2);
	m1.adauga_nod(3);
	m2.adauga_nod(2);
	m2.adauga_nod(3);
	m2.adauga_nod(4);
	m1.display_list();
	m2.display_list();
	m = m1 + m2;
	cout << "reuniune" << endl;
	m1.display_list();
	m2.display_list();
	cout << m;

	cout << endl;

	m = m1 - m2;
	cout << "diferenta" << endl;
	m1.display_list();
	m2.display_list();
	cout << m;

	cout << endl;

	m = m1 * m2;
	cout << "intersectie" << endl;
	m1.display_list();
	m2.display_list();
	cout << m;
	cin >> m;
	cout << m;


	cin >> n;
	return 0;
}