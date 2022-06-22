#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <string>
#include <random>
#include <boost/graph/adjacency_list.hpp>

using namespace std;
using boost::asio::ip::tcp;
using namespace boost;

int main()
{

    typedef adjacency_list<vecS, vecS, undirectedS> Graph;
    int zeton;

    string ipserwera;
    string port;
    cout << "Podaj IP serwera: ";
    cin >> ipserwera;
    cout << "Podaj Port serwera: ";
    cin >> port;
    try
    {
        tcp::iostream serwer(ipserwera, port);  // proba nawiazania polaczenia z serwerem
        if (!serwer)
        {
            cout << "Polaczenie z serwerem nieudane." << endl;
            return 1;
        }
        string komunikat;
        getline(serwer, komunikat);
        cout << "Odebralem: " << komunikat << endl;
        vector<int> liczby;
        stringstream ss(komunikat);
        int liczba;
        while (ss >> liczba)
        {
            liczby.push_back(liczba);
        }
        int kod = liczby[0];
        if (kod != 200)
        {
            return 1;
        }
        Graph g(liczby[1]);
        zeton = liczby[2];
        int liczba_krawedzi = liczby[3];


        int odp;
        cin >> odp;
        serwer << string("210 ") + to_string(odp) + string("\n");
        serwer.flush();
        remove_edge(zeton, odp, g);
        zeton = odp;
        cout << "Wyslalem: 210 " << odp << endl;
        ss.clear();
        getline(serwer, komunikat);
        cout << "Odebralem: " << komunikat << endl;
        ss.str(komunikat);
        ss >> kod;
        if (kod == 220)
        {
            int ruch;
            ss >> ruch;
            remove_edge(zeton, ruch, g);
            zeton = ruch;
        }

        serwer.close();
    }
    catch (std::exception& e) {
        cout << "Wyjatek: " << e.what() << endl;
    }
    return 0;
}