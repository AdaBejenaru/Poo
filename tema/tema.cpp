#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Avocat
{
protected:
    int cod;
    string nume;
    int nr_procese;
    int* vector_procese;
public:
    Avocat() : cod(0), nume(""), nr_procese(0), vector_procese(nullptr) {}
    Avocat(int c, string n, int nr, int* vp) : cod(c), nume(n), nr_procese(nr), vector_procese(vp) {
        vector_procese = new int[nr];
        for (int i = 0; i < nr; i++)
        {
            vector_procese[i] = vp[i];
        }
    }
    Avocat(const Avocat& a) : cod(a.cod), nume(a.nume), nr_procese(a.nr_procese), vector_procese(a.vector_procese) {
        vector_procese = new int[nr_procese];
        for (int i = 0; i < nr_procese; i++)
            vector_procese[i] = a.vector_procese[i];
    }
    virtual ~Avocat()
    {
        delete[] vector_procese;
    }
    Avocat& operator=(const Avocat& a)
    {
        if (this == &a)
        {
            return *this;
        }
        cod = a.cod;
        nume = a.nume;
        nr_procese = a.nr_procese;
        delete[] vector_procese;
        vector_procese = new int[nr_procese];
        for (int i = 0; i < nr_procese; i++)
        {
            vector_procese[i] = a.vector_procese[i];
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Avocat& a)
    {
        cout << "Introduceti codul avocatului: ";
        in >> a.cod;
        cout << "Introduceti numele avocatului: ";
        in >> a.nume;
        cout << "Introduceti numarul de procese: ";
        in >> a.nr_procese;
        if (a.nr_procese > 0)
        {
            a.vector_procese = new int[a.nr_procese];
            for (int i = 0; i < a.nr_procese; i++)
                in >> a.vector_procese[i];
        }
    }
    bool operator<(const Avocat& a) const
    {
        return nr_procese < a.nr_procese;
    }
    virtual int CalcDurMaxCuClient() const = 0;
};

class Avocat_Oficiu : public Avocat
{
private:
    string nume_client;
    int durata;
public:
    Avocat_Oficiu() : Avocat(), nume_client(""), durata(0) {}
    Avocat_Oficiu(string nc, int d, int c, string n, int nr, int* vp) : Avocat(c, n, nr, vp), nume_client(nc), durata(d) {}
    Avocat_Oficiu(const Avocat_Oficiu& a) : Avocat(a), nume_client(a.nume_client), durata(a.durata) {}
    ~Avocat_Oficiu() {}
    Avocat_Oficiu& operator=(const Avocat_Oficiu& a)
    {
        if (this == &a)
        {
            return *this;
        }
        Avocat::operator=(a);
        nume_client = a.nume_client;
        durata = a.durata;
        return *this;
    }
    friend istream& operator>>(istream& in, Avocat_Oficiu& a)
    {
        Avocat& avocat = a;
        in >> avocat;
        cout << "Introduceti numele clientului: ";
        in >> a.nume_client;
        cout << "Introduceti durata petrecuta cu clientul: ";
        in >> a.durata;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Avocat_Oficiu& a)
    {
        const Avocat& avocat = a;
        out << avocat;
        out << "Numele clientului: " << a.nume_client << endl;
        out << "Durata petrecuta cu clientul: " << a.durata << endl;
        return out;
    }

    int CalcDurMaxCuClient() const
    {
        return durata;
    }
};

int main()
{
    int n;
    cout << "Introduceti numarul de avocati: ";
    cin >> n;
    vector<Avocat_Oficiu> avocati;
    for (int i = 0; i < n; i++)
    {
        Avocat_Oficiu a;
        cin >> a;
        avocati.push_back(a);
    }
    sort(avocati.begin(), avocati.end());
    cout << "Avocatii sortati dupa numarul de procese:" << endl;
    for (auto& a : avocati)
    {
        cout << a << endl;
    }
    int durata_maxima = 0;
    Avocat_Oficiu avocat_max;
    for (auto& a : avocati)
    {
        if (a.CalcDurMaxCuClient() > durata_maxima)
        {
            durata_maxima = a.CalcDurMaxCuClient();
            avocat_max = a;
        }
    }
    cout << "Avocatul care a petrecut cel mai mult timp cu un client: " << avocat_max << endl;
    return 0;
}

