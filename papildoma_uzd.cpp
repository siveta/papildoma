#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

using std::string;
using std::cout;
using std::cout;
using std::vector;
using std::endl;

struct Zodis {
	int kiekis=1;
	vector<int> eilutes;
};

string tvarkymas(string str) {
    str.erase(std::remove_if(str.begin(), str.end(), ispunct), str.end());
    return str;
}
vector<string> skaidymas(string eilute) {
    vector<string> zodziai;
    transform(eilute.begin(), eilute.end(), eilute.begin(), ::tolower);
    std::stringstream s(eilute);
    std::string zodis;
    while (getline(s, zodis, ' ')) {
        zodziai.push_back(zodis);
    }
    return zodziai;
}

void nuskaitymas(string failas, std::map<std::string, Zodis>& zodziaiMap) {
    std::ifstream myFile;
    std::string eil;
    int line = 1;
    std::map<string, Zodis>::iterator it;

    myFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        myFile.open(failas);
    }
    catch (std::ifstream::failure e) {
        cout << "Negalima atidaryti failo arba failas neegzistuoja!\n";
    }

    while (!myFile.eof()) {
        getline(myFile, eil);
        vector<string> zodziai = skaidymas(eil);
        for (int i = 0; i < zodziai.size(); i++) {
            if (zodziai[i].substr(0, 8) == "https://" || zodziai[i].substr(0, 4) == "www.") {
                string a = zodziai[i].substr(0, zodziai[i].size());
                cout <<"URL:: "<< zodziai[i] << endl;
            }
            else {
                string zodis1 = tvarkymas(zodziai[i]);
                it = zodziaiMap.find(zodis1);
                if (it != zodziaiMap.end()) {
                    it->second.kiekis++;
                    it->second.eilutes.push_back(line);
                }
                else {
                    Zodis a;
                    a.eilutes.push_back(line);
                    zodziaiMap.insert(std::make_pair(zodis1, a));
                }
            }
        }
        eil.clear();
        zodziai.clear();
        line++;
    }
}


void output(std::map<std::string, Zodis>& zodziaiMap) {
    cout << "-----------------------------------------------------------------------" << endl;
    cout << std::left << std::setw(20) << "Zodis:" << " | " << std::setw(10) << "Kiekis:" << " | " << "Paminetas :" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    std::map<std::string, Zodis>::iterator it;
    it = zodziaiMap.begin();
    for (int i = 0; i < zodziaiMap.size(); i++) {
        if (it->second.kiekis != 1) {
            cout << std::setw(20) << it->first << " | " << std::setw(10) << it->second.kiekis << " | ";
            for (int l = 0; l < it->second.kiekis; l++) {
                cout << it->second.eilutes[l];
                if (l + 1 != it->second.kiekis) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        it++;
    }
}

int main() {
    std::map<string, Zodis> zodziaiMap;
    nuskaitymas("tekstas2.txt", zodziaiMap);
    output(zodziaiMap);
}