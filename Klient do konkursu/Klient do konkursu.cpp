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
    while (!serwer=true)
    { 
    string ipserwera;
    string port;
    cout << "IP: ";
    cin >> ipserwera;
    cout << "Port Serwera: ";
    cin >> port;
    try {
        tcp::iostream serwer(ipserwera, port);  // proba nawiazania polaczenia z serwerem
        if (!serwer) {
            cout << "Polaczenie z serwerem nieudane." << endl;
            return 1;
        }
    
        string komunikat;
        getline(serwer, komunikat);
        cout << "Odebralem: " << komunikat << endl;
        vector<int> liczby;
        stringstream ss(komunikat);
        int liczba;
        while (ss >> liczba) {
            liczby.push_back(liczba);
        }
        int kod = liczby[0];
        if (kod != 200) {
            return 1;
        }
        Graph g(liczby[1]);
        zeton = liczby[2];
        int liczba_krawedzi = liczby[3];
        for (int i = 0; i < liczba_krawedzi; i++) {
            add_edge(liczby[4 + 2 * i], liczby[5 + 2 * i], g);
        }
        liczby.clear();
        while (kod < 230) {
           
            
            int odp;
            cout << "Moj kolejny ruch: ";
            cin >> odp;// losowy ruch klienta
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
            if (kod == 220) {
                int ruch;
                cout << "Podaj kolejny ruch: ";
                cin >> ruch;vvvv
                remove_edge(zeton, ruch, g);
                zeton = ruch;
            }
        }
        serwer.close();
    }
    catch (std::exception& e) {
        cout << "Wyjatek: " << e.what() << endl;
    }
    return 0;
}